import paho.mqtt.client as mqtt
import json
import csv
import os
import time
import joblib

# MQTT Config (Ubidots Industrial)
MQTT_BROKER = "industrial.api.ubidots.com"
MQTT_PORT = 1883
# IMPORTANT: Username is your Ubidots token, password can be empty
MQTT_TOKEN = "UBITODS_TOKEN_HERE"  # Replace with your Ubidots token

# Topics
DEVICE_LABEL = "farmtech"
DEVICE_TOPIC = f"/v1.6/devices/{DEVICE_LABEL}"
ALERT_TOPIC = f"/v1.6/devices/{DEVICE_LABEL}/alerts"

# CSV File for Data Collection
CSV_FILE = "sensor_data.csv"

def load_model_once():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    candidates = [
        os.path.join(script_dir, "classifier.pkl"),
        os.path.join(os.getcwd(), "classifier.pkl"),
        os.path.join(script_dir, "..", "classifier.pkl"),
    ]
    for p in candidates:
        if os.path.exists(p):
            try:
                m = joblib.load(p)
                print(f"Loaded model from {p} — real-time predictions enabled")
                return m
            except Exception as e:
                print(f"Failed loading model from {p}: {e}")
    print("No model found — data collection only (no inference)")
    return None


# Load Pre-Trained Model (optional for real-time inference)
model = load_model_once()


def ensure_csv_header(path: str):
    header = ["temperature", "humidity", "moisture", "label"]
    if not os.path.exists(path) or os.path.getsize(path) == 0:
        with open(path, "w", newline="") as f:
            writer = csv.writer(f)
            writer.writerow(header)


# Auto-labeling for training data
def get_label(temp, hum, moisture):
    if 20 <= temp <= 30 and 50 <= hum <= 70 and moisture > 60:
        return "Healthy"
    return "Unhealthy"


def parse_payload(topic: str, payload_bytes: bytes):
    """Parse Ubidots MQTT payloads from either device-root or variable topics.
    Returns (temperature, humidity, moisture) where any missing fields are None.
    """
    try:
        payload = payload_bytes.decode("utf-8").strip()
        data = json.loads(payload)
    except Exception:
        # Not JSON — try to coerce into a number if variable/.. topics send raw
        data = payload

    temperature = None
    humidity = None
    moisture = None

    # Case 1: Publishing to device root: {"moisture": 55.2, "temperature": 24.3, ...}
    if isinstance(data, dict) and any(k in data for k in ("moisture", "temperature", "humidity")):
        temperature = data.get("temperature")
        humidity = data.get("humidity")
        moisture = data.get("moisture")
        return temperature, humidity, moisture

    # Case 2: Subscribed to variable topic like .../moisture with payload {"value": 55.2}
    last_segment = topic.rsplit("/", 1)[-1].lower() if "/" in topic else topic.lower()
    if isinstance(data, dict) and "value" in data:
        val = data.get("value")
        if last_segment.startswith("temp"):
            temperature = float(val)
        elif last_segment.startswith("hum"):
            humidity = float(val)
        elif last_segment.startswith("moist"):
            moisture = float(val)
        return temperature, humidity, moisture

    # Case 3: Raw numeric payload on variable topic
    try:
        val = float(data)
        if last_segment.startswith("temp"):
            temperature = val
        elif last_segment.startswith("hum"):
            humidity = val
        elif last_segment.startswith("moist"):
            moisture = val
        return temperature, humidity, moisture
    except Exception:
        pass

    return None, None, None


# MQTT Callbacks
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    # Subscribe to multiple patterns to cover Ubidots publish behavior
    subs = [
        (DEVICE_TOPIC, 0),            # Root device topic (when publishing JSON with multiple vars)
        (f"{DEVICE_TOPIC}/+", 0),     # Direct variable topics (e.g., /moisture)
        (f"{DEVICE_TOPIC}/#", 0),     # Any nested topics (e.g., /moisture/lv)
    ]
    for t, qos in subs:
        result, mid = client.subscribe(t, qos=qos)
        print(f"Subscribe to '{t}' -> result={result}, mid={mid}")


def on_message(client, userdata, msg):
    try:
        t0 = time.time()
        global model
        if model is None:
            # Try to find a newly created model without restarting the script
            model = load_model_once()
        temp, hum, moist = parse_payload(msg.topic, msg.payload)

        # If ESP32 currently only sends moisture, simulate temp/hum to keep pipeline moving
        if moist is not None:
            moisture = float(moist)
        else:
            moisture = 0.0

        temperature = float(temp) if temp is not None else 25.0
        humidity = float(hum) if hum is not None else 60.0

        print(
            f"Message on {msg.topic}: Temp={temperature:.1f}°C, Hum={humidity:.1f}%, Moisture={moisture:.1f}%"
        )

        # Auto-label and persist
        label = get_label(temperature, humidity, moisture)
        ensure_csv_header(CSV_FILE)
        with open(CSV_FILE, "a", newline="") as f:
            writer = csv.writer(f)
            writer.writerow([temperature, humidity, moisture, label])

        # Real-Time Inference (if model exists)
        if model is not None:
            pred = model.predict([[temperature, humidity, moisture]])[0]
            pred_label = "Healthy" if int(pred) == 1 else "Unhealthy"
            print(f"--> PREDICTION: {pred_label}  (latency {1000*(time.time()-t0):.1f} ms)")

    except Exception as e:
        print(f"Error processing message from {msg.topic}: {e}")


# Setup Client
client = mqtt.Client()  # auto-generated client_id
client.username_pw_set(MQTT_TOKEN)  # Auth with token as username
client.on_connect = on_connect
client.on_message = on_message

# Connect and run forever
client.connect(MQTT_BROKER, MQTT_PORT, keepalive=60)
client.loop_forever()