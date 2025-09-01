#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h>

// Sensor Pins and Config
#define DHTPIN 4          // DHT22 data pin
#define DHTTYPE DHT22     // DHT22 sensor type
DHT dht(DHTPIN, DHTTYPE);
#define SOIL_PIN 34       // Soil moisture analog pin
#define LED_PIN 2         // LED for send status

// Gateway MAC Address (replace with your Gateway ESP32's MAC from WiFi.macAddress())
uint8_t gatewayMac[] = {0x8C, 0x4F, 0x00, 0x27, 0xB3, 0xF0};  // Example: Use hex bytes

// Structured Data for ESP-NOW (ensures type safety and easy parsing)
typedef struct {
  float temperature;
  float humidity;
  float moisture;
} SensorData;

// Callback for ESP-NOW send status (integration: visual feedback for debugging)
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  digitalWrite(LED_PIN, status == ESP_NOW_SEND_SUCCESS ? HIGH : LOW);  // LED high on success
  Serial.print("ESP-NOW Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
  delay(200);  // Brief blink
  digitalWrite(LED_PIN, LOW);
}

void setup() {
  Serial.begin(115200);  // For debugging via Serial Monitor
  pinMode(LED_PIN, OUTPUT);
  dht.begin();  // Initialize DHT22

  // Initialize Wi-Fi in STA mode (required for ESP-NOW, but no connection needed)
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    while (1);  // Halt on failure (senior practice: fail fast)
  }

  // Register send callback
  esp_now_register_send_cb(OnDataSent);

  // Add Gateway as peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, gatewayMac, 6);
  peerInfo.channel = 0;  // Auto-select channel
  peerInfo.encrypt = false;  // No encryption (add if needed for security)
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    while (1);
  }
}

void loop() {
  // Read sensors
  float temp = dht.readTemperature();  // Celsius
  float hum = dht.readHumidity();      // %
  int soil_raw = analogRead(SOIL_PIN); // 0-4095 (calibrate: dry ~4095, wet ~1000)
  float soil = map(soil_raw, 4095, 1000, 0, 100);  // Map to 0-100% (invert for moisture; adjust based on tests)

  // Data validation (integration: prevent bad data from propagating to ML)
  if (isnan(temp) || isnan(hum) || soil < 0 || soil > 100) {
    Serial.println("Sensor reading error - skipping send");
    delay(1000);  // Retry sooner
    return;
  }

  // Package data
  SensorData data = {temp, hum, soil};

  // Send via ESP-NOW (low-power, direct peer-to-peer)
  esp_err_t result = esp_now_send(gatewayMac, (uint8_t *)&data, sizeof(data));
  if (result != ESP_OK) {
    Serial.println("ESP-NOW send error");
  }

  delay(10000);  // 10s interval (adjust for farm needs; low for testing)
}