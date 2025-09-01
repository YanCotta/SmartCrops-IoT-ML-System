#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Pins for Feedback
#define LED_PIN 2    // Green LED for "Healthy" alert
#define BUZZER_PIN 5 // Buzzer for "Unhealthy" alert (from kit)

// Wi-Fi and MQTT Config (replace placeholders)
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* mqtt_server = "industrial.api.ubidots.com";
const char* mqtt_token = UBIDOTS_TOKEN;  // From Ubidots account
const char* device_label = "/v1.6/devices/farmtech";  // Publish topic
const char* alert_topic = "/v1.6/devices/farmtech/alerts";  // Subscribe for ML alerts

// Structured Data (must match Sensor Node)
typedef struct {
  float temperature;
  float humidity;
  float moisture;
} SensorData;

// MQTT Client
WiFiClient espClient;
PubSubClient client(espClient);

// Wi-Fi Connection (with retry)
void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

// MQTT Reconnect (senior: exponential backoff if extended)
void reconnect_mqtt() {
  while (!client.connected()) {
    if (client.connect("GatewayClient", mqtt_token, NULL)) {
      Serial.println("MQTT connected");
      client.subscribe(alert_topic);  // Subscribe to ML alerts
    } else {
      Serial.print("MQTT connect failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

// MQTT Callback for Alerts (integration: ML → Hardware actuation)
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.print("Alert received: ");
  Serial.println(msg);

  if (msg == "1") {  // Healthy (from ML pred)
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);  // No buzz
  } else {  // Unhealthy
    digitalWrite(LED_PIN, LOW);
    tone(BUZZER_PIN, 1000, 500);  // Buzz for 500ms
  }
}

// ESP-NOW Receive Callback (processes incoming data)
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  if (len != sizeof(SensorData)) {
    Serial.println("Invalid data size");
    return;
  }
  SensorData data;
  memcpy(&data, incomingData, sizeof(data));

  Serial.printf("Received: Temp=%.2f°C, Hum=%.2f%%, Moisture=%.2f%%\n", data.temperature, data.humidity, data.moisture);

  // Forward to MQTT (integration: Bridge to cloud/Python)
  if (!client.connected()) {
    reconnect_mqtt();
  }
  String payload = String("{\"temperature\":" + String(data.temperature) + ", \"humidity\":" + String(data.humidity) + ", \"moisture\":" + String(data.moisture) + "}");
  client.publish(device_label, payload.c_str());

  // Blink LED on receive for visual confirmation
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize Wi-Fi and ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    while (1);
  }
  esp_now_register_recv_cb(OnDataRecv);  // Register receive callback

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(mqttCallback);  // Set alert callback
}

void loop() {
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop();  // Handle MQTT subscriptions
  delay(100);    // Light loop to avoid blocking
}