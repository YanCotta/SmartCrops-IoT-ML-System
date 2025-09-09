#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// --- Configurações (Preencha suas credenciais no arquivo .env) ---
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* mqtt_token = UBIDOTS_TOKEN;

// --- Constantes da Ubidots ---
const char* mqtt_server = "industrial.api.ubidots.com";
const char* device_label = "farmtech";
const char* moisture_variable_label = "moisture";

// --- Pinos ---
#define SOIL_PIN 34 // D34 no seu ESP32

// --- Clientes de Rede ---
WiFiClient espClient;
PubSubClient client(espClient);

// --- Função para conectar ao Wi-Fi ---
void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

// --- Função para reconectar ao MQTT ---
void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32_FarmTech", mqtt_token, NULL)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// --- SETUP: Executa uma vez ---
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

// --- LOOP: Executa repetidamente ---
void loop() {
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop();

  // Lê o sensor de umidade do solo
  int soil_raw = analogRead(SOIL_PIN);
  // Mapeia o valor para uma porcentagem (0-100%). Ajuste 4095 e 1000 com base na sua calibração!
  float soil_percentage = map(soil_raw, 4095, 1000, 0, 100);

  // Garante que o valor esteja entre 0 e 100
  if (soil_percentage < 0) soil_percentage = 0;
  if (soil_percentage > 100) soil_percentage = 100;

  Serial.print("Soil Moisture: ");
  Serial.print(soil_percentage);
  Serial.println("%");

  // Cria o payload JSON para enviar para a Ubidots
  String payload = String("{\"") + moisture_variable_label + "\":" + String(soil_percentage) + "}";

  // Publica os dados
  client.publish(String("/v1.6/devices/" + String(device_label)).c_str(), payload.c_str());

  delay(10000); // Espera 10 segundos
}