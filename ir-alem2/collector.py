import paho.mqtt.client as mqtt
import json
import csv
import time
import joblib  # For loading pre-trained model (from scikit-learn)

# MQTT Config (match Ubidots/Gateway)
MQTT_BROKER = "industrial.api.ubidots.com"
MQTT_PORT = 1883
MQTT_TOKEN = "YourUbidotsToken"  # Username is token, no password
DEVICE_LABEL = "/v1.6/devices/farmtech"  # Subscribe topic
ALERT_TOPIC = "/v1.6/devices/farmtech/alerts"  # Publish alerts back

# CSV File for Data Collection
CSV_FILE = 'sensor_data.csv'

# Load Pre-Trained Model (integration: after training in Jupyter, dump as 'classifier.pkl')
try:
    model = joblib.load('classifier.pkl')  # Assume you train and save in Jupyter
except FileNotFoundError:
    model = None  # Fallback if no model yet
    print("No model found - collection only (no inference)")

# Health Thresholds for Auto-Labeling (for training data; adjust based on farm research)
def get_label(temp, hum, moisture):
    if 20 <= temp <= 30 and 50 <= hum <= 70 and moisture > 60:
        return "Healthy"
    return "Unhealthy"

# MQTT Callbacks
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe(DEVICE_LABEL)

def on_message(client, userdata, msg):
    try:
        data = json.loads(msg.payload.decode())
        temp = data['temperature']
        hum = data['humidity']
        moisture = data['moisture']
        print(f"Received: Temp={temp}°C, Hum={hum}%, Moisture={moisture}%")

        # Auto-label for CSV (for ML training)
        label = get_label(temp, hum, moisture)

        # Save to CSV (integration: Builds dataset for Jupyter)
        with open(CSV_FILE, 'a', newline='') as f:
            writer = csv.writer(f)
            writer.writerow([temp, hum, moisture, label])

        # Real-Time Inference (if model loaded)
        if model:
            pred = model.predict([[temp, hum, moisture]])[0]  # Assume 1=Healthy, 0=Unhealthy
            pred_label = "1" if pred == 1 else "0"
            print(f"Predicted: {'Healthy' if pred == 1 else 'Unhealthy'}")
            
            # Publish Alert Back to Gateway (closes feedback loop)
            client.publish(ALERT_TOPIC, pred_label)

    except Exception as e:
        print(f"Error processing message: {e}")

# Setup Client
client = mqtt.Client()
client.username_pw_set(MQTT_TOKEN)  # Auth with token
client.on_connect = on_connect
client.on_message = on_message

# Connect and Run
client.connect(MQTT_BROKER, MQTT_PORT, 60)
client.loop_forever()  # Blocking loop (run in background if needed)