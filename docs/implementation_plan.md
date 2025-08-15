### Overall Project Strategy and Architecture

To elevate this to a senior-level execution, we'll design a fully integrated, scalable "FarmTech IoT-ML System" that simulates real-time crop monitoring for a medium-sized farm. The system will collect environmental data (temperature, humidity, soil moisture) using your ESP32 and new sensors, mimicking the `crop_yield.csv` dataset variables (e.g., soil moisture as a proxy for precipitation, temperature and humidity directly). This data will feed into ML models for yield prediction (mandatory) and plant health classification (Ir Além 2), with IoT communication via Wi-Fi and MQTT for data publishing (Ir Além 1). We'll use C++ with the Arduino framework for ESP32 programming, as it's more performant and closer to bare-metal than MicroPython, allowing for optimized sensor reading, error handling, and potential future expansions like OTA updates. Since you're using VS Code, we'll leverage the PlatformIO extension for seamless development, building, and uploading—it's professional-grade, supports debugging, and integrates Git.

#### Key Design Principles (Educational Notes):
- **Senior-Level Practices**: Modular code (separate headers for sensors, network, etc.), error handling (e.g., retries on Wi-Fi connect), data validation (filter noisy sensor readings), and efficiency (low power modes if time allows). We'll use libraries like PubSubClient for MQTT and DHT for sensors—install via PlatformIO.
- **Integration**: ESP32 collects data → Publishes to MQTT broker (Ubidots for free dashboard/storage) → Python script on your PC subscribes, saves to CSV → Feeds into Jupyter for ML. For real-time classification, the Python script runs inference and could send alerts back (e.g., via MQTT to trigger ESP32 LED/buzzer).
- **Farm Alignment**: Sensors chosen to match dataset: DHT22 for "Temperature at 2m (ºC)" and "Relative Humidity at 2m (%)"; Soil moisture for "Precipitation (mm/day)" proxy (moist soil implies recent rain/good conditions). Assume corn crop; healthy if temp 20-30ºC, humidity 50-70%, moisture >60%.
- **Tools/Tech Stack**:
  - ESP32: C++ with Arduino core (via PlatformIO in VS Code).
  - Sensors: DHT22 (digital, pin for data), Capacitive soil moisture (analog pin, 3.3V power).
  - Wiring: Protoboard from kit; use resistors if needed (e.g., pull-up for DHT22).
  - Communication: Wi-Fi + MQTT (Ubidots—easy, no local server setup).
  - ML: Python/Jupyter with scikit-learn (regression/clustering) and optional TensorFlow for advanced classification if you want to stretch.
  - Cloud: AWS estimation (no actual deploy).
  - GitHub: One repo, public, structured folders. Use branches for development (e.g., `feature/esp-iot`), merge to main.
  - Videos: Use OBS Studio for recording; script narration for professionalism.
- **Extra Components**: Your new sensors are perfect—no more needed. Use kit LEDs for health alerts (green=healthy), buzzer for warnings, buttons for manual reads.
- **Learning Focus**: Each step includes "Why?" explanations, common pitfalls, and debugging tips. Leverage AI (e.g., GitHub Copilot in VS Code) for code snippets, but I'll provide skeletons.
- **Timeline Suggestion**: 1-2 days per section; total 10-14 days. Test incrementally (e.g., sensor read before network).

#### High-Level System Architecture
1. **IoT Layer (ESP32 in C++)**: Sensors → ESP32 processes (average readings to reduce noise) → Wi-Fi connect → MQTT publish to Ubidots.
2. **Data Layer**: Ubidots stores/viz data; Python MQTT subscriber saves to CSV (local "DB").
3. **ML Layer**:
   - Mandatory: Offline analysis on provided dataset.
   - Ir Além 2: Train classifier on collected CSV; real-time inference via Python script.
4. **Output**: Ubidots dashboard, Jupyter reports, alerts (LED/buzzer via reverse MQTT).
5. **Cloud Hypothetical**: AWS for ML API hosting estimation.

Diagram: Use Draw.io (free) or Wokwi.com (simulate circuit: ESP32 + DHT22 on GPIO4, soil on GPIO34, LED on GPIO2). Export PNG, include in GitHub.

GitHub Repo Structure:
- README.md: Intro, architecture diagram, links to notebooks/videos, AWS section with tables/screenshots.
- `/entrega1`: `YourName_RM_pbl_fase5.ipynb`.
- `/ir-alem1`: `main.ino`, `sensors.h`, circuit_diagram.png, video_link.md.
- `/ir-alem2`: `ml_classifier.ipynb`, `realtime_inference.py`, diagram.png, video_link.md.
- Use `.gitignore` for builds.

Commit strategy: Frequent small commits during dev; final push before deadline, no post-deadline commits.

Now, refined step-by-step plans.

### Step-by-Step Plan for Entrega 1: ML on Crop Yield Dataset

**Goal**: Professional EDA, unsupervised clustering for trends/outliers, 5 supervised regression models with metrics/comparisons. Use best practices: data preprocessing, cross-validation, hyperparam tuning.

1. **Environment Setup (1-2 hours)**:
   - Install Anaconda (for Jupyter, libs). Launch VS Code, but use Jupyter via browser or VS Code extension.
   - Create GitHub repo: `git init`, add remote, create `main` branch.
   - Download `crop_yield.csv`, place in `/entrega1`.
   - Notebook: Name as specified. Install libs if needed: `pip install pandas numpy scikit-learn matplotlib seaborn`.
   - Why? Anaconda manages envs professionally; Git branches prevent messy history.

2. **Exploratory Data Analysis (EDA) (3-4 hours)**:
   - Import: `import pandas as pd; import numpy as np; import matplotlib.pyplot as plt; import seaborn as sns`.
   - Load: `df = pd.read_csv('crop_yield.csv')`.
   - Markdown Section: "# Exploratory Data Analysis\nFamiliarizing with dataset structure and distributions."
   - Code: `df.head(10)`, `df.describe()`, `df.info()`, check nulls `df.isnull().sum()`.
   - Handle issues: If categoricals (e.g., 'Crop'), encode `pd.get_dummies(df['Crop'])`.
   - Visuals: Histograms `sns.histplot(df['Yield'], kde=True)`, pairplot `sns.pairplot(df)`, correlation heatmap `sns.heatmap(df.corr(), annot=True)`.
   - Outliers: Boxplots `sns.boxplot(x='Crop', y='Yield', data=df)`.
   - Text: Discuss: "Yield skews right, indicating few high-yield outliers. Temp positively correlates (r=0.XX) with yield, suggesting warmer conditions boost productivity. Limitations: Dataset may lack seasonal variance."
   - Pitfall: Overplotting—use `plt.tight_layout()`. Debug: If errors, check column names case-sensitive.

3. **Clustering for Trends/Outliers (2-3 hours)**:
   - Why? Unsupervised to discover patterns (e.g., high-yield clusters in optimal humidity).
   - Prep: `from sklearn.preprocessing import StandardScaler; scaler = StandardScaler(); X_scaled = scaler.fit_transform(df.drop(['Yield', 'Crop'], axis=1))` (or encode 'Crop').
   - Elbow Method: `from sklearn.cluster import KMeans; inertias = []; for k in range(1,11): kmeans = KMeans(n_clusters=k); kmeans.fit(X_scaled); inertias.append(kmeans.inertia_); plt.plot(range(1,11), inertias)`.
   - Fit: Choose k=3-4, `kmeans = KMeans(n_clusters=3); df['Cluster'] = kmeans.fit_predict(X_scaled)`.
   - Visualize: `plt.scatter(df['Temperature'], df['Yield'], c=df['Cluster'])`.
   - Outliers: `from sklearn.ensemble import IsolationForest; iso = IsolationForest(); df['Outlier'] = iso.fit_predict(X_scaled);` ( -1 = outlier).
   - Text: "Clusters: Cluster 0 (high yield, moderate temp/humidity); outliers in extreme precip (>XX mm). Trends: Productivity peaks in balanced conditions."
   - Educational: Clustering assumes spherical groups; if not, try DBSCAN.

4. **5 Predictive Regression Models (4-5 hours)**:
   - Why? Compare algorithms for robustness; use CV for reliable metrics.
   - Prep: `from sklearn.model_selection import train_test_split, GridSearchCV; X = pd.get_dummies(df.drop('Yield', axis=1)); y = df['Yield']; X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)`.
   - Models (different algos):
     - Linear: `from sklearn.linear_model import LinearRegression; lr = LinearRegression(); lr.fit(X_train, y_train); y_pred = lr.predict(X_test);`.
     - Tree: `from sklearn.tree import DecisionTreeRegressor; dt = DecisionTreeRegressor();` (tune `max_depth` via GridSearchCV).
     - Forest: `from sklearn.ensemble import RandomForestRegressor; rf = RandomForestRegressor(n_estimators=100);`.
     - SVM: `from sklearn.svm import SVR; svr = SVR(kernel='rbf');`.
     - KNN: `from sklearn.neighbors import KNeighborsRegressor; knn = KNeighborsRegressor(n_neighbors=5);`.
   - Metrics: `from sklearn.metrics import mean_squared_error, r2_score; mse = mean_squared_error(y_test, y_pred); r2 = r2_score(y_test, y_pred);`.
   - Compare: Create DF `results = pd.DataFrame({'Model': ['LR', 'DT', ...], 'MSE': [...], 'R2': [...]})`.
   - Text: "RF performs best (R2=0.XX, MSE=YY); strengths: Handles non-linearity; limits: Overfits on small data, no causality inference."
   - Advanced: Use CV `cross_val_score(rf, X, y, cv=5)`.

5. **Polish and Deliverables (2 hours)**:
   - Comments: `// This scales features to prevent bias in distance-based algos.`
   - Run all, organize Markdown: Sections with bold subheads, conclusions.
   - README: "## Entrega 1\nLink to notebook: [here]. Video: [link]."
   - Video: 4-5 min, narrate: "Here I load data... See correlation... Best model is RF."
   - Commit: `git add .; git commit -m "Complete Entrega 1"; git push`.

### Step-by-Step Plan for Entrega 2: AWS Cost Estimation

**Goal**: Accurate comparison, justified choice. Costs based on latest (as of 2025): t3.micro Linux On-Demand, 730 hrs/mo, 50GB gp3.

1. **Estimate Costs (1-2 hours)**:
   - Use AWS Pricing Calculator: Add EC2 > On-Demand > Linux > t3.micro > 730 hrs.
   - Virginia (us-east-1): Instance ~$7.59/mo; gp3 50GB ~$4.00/mo (0.08/GB); Total ~$11.59.
   - Sao Paulo (sa-east-1): Instance ~$12.12/mo; gp3 ~$5.40/mo (0.108/GB); Total ~$17.52.
   - Screenshots: Capture breakdowns.
   - Why? t3.micro matches specs; gp3 for balanced storage.

2. **Comparison and Justification (1 hour)**:
   - Markdown Table in README:
     | Region       | Instance Cost/mo | Storage Cost/mo | Total/mo |
     |--------------|------------------|-----------------|----------|
     | N. Virginia | $7.59           | $4.00          | $11.59  |
     | Sao Paulo   | $12.12          | $5.40          | $17.52  |
   - Text: "Virginia is cheaper (~33% savings). However, choose Sao Paulo: Lower latency for Brazil-based sensors (faster data access), LGPD compliance restricts foreign storage for sensitive ag data. Justification: Prioritize legal/performance over cost; Virginia viable if no restrictions."
   - Educational: Consider data transfer costs (not included, as minimal for API).

3. **Deliverables (1 hour)**:
   - Add to README: "## Entrega 2\n[Table]\n[Images]\nJustification..."
   - Video: 4 min, demo calculator: "Input t3.micro... See Virginia $11.59... Choose SP for reasons."
   - Commit as above.

### Step-by-Step Plan for Ir Além 1: ESP32 IoT System (with ESP-NOW)

**Goal**: Develop a dual-ESP32 system for data collection and communication. Sensor Node collects from two sensors (DHT22 + soil moisture), sends via ESP-NOW to Gateway Node, which forwards to MQTT/Ubidots. This demonstrates Wi-Fi integration with peer-to-peer efficiency.

1. **Setup VS Code and PlatformIO for Both Nodes (1-2 hours)**:
   - Create two separate PlatformIO projects: One for "sensor-node", one for "gateway-node". (PIO Home > New Project > ESP32 Dev Module > Arduino framework.)
   - Install libraries: In each project's PIO Libraries > Search/install "DHT sensor library" (Adafruit for DHT22), "PubSubClient" (for MQTT on gateway), and ensure "esp_now.h" is available (it's in the ESP32 Arduino core—no extra install).
   - Why? Separate projects avoid confusion; PlatformIO handles dual builds. Educational: ESP-NOW requires Wi-Fi initialized but not connected, making it power-efficient.
   - Pitfall: If esp_now.h not found, update ESP32 platform in PIO (Boards Manager).

2. **Wiring the Circuits (1-2 hours)**:
   - **Sensor Node (ESP32 #1)**: DHT22 (VCC to 3.3V, GND to GND, Data to GPIO4; optional 10k pull-up resistor). Soil Moisture (VCC to 3.3V, GND to GND, Analog Out to GPIO34). Add an LED (GPIO2 with resistor) for send status.
   - **Gateway Node (ESP32 #2)**: No sensors needed; add LED (GPIO2) for receive status. (Use buzzer/LEDs from kit for alerts later.)
   - Simulate both in Wokwi: Two ESP32s; wire sensors to #1, add virtual ESP-NOW link (Wokwi supports basic simulation).
   - Get MACs: Upload this to each ESP32 separately:
     ```cpp
     #include <WiFi.h>
     void setup() { Serial.begin(115200); Serial.println(WiFi.macAddress()); }
     void loop() {}
     ```
     Note: MAC for STA mode (e.g., "24:0A:C4:XX:XX:XX"). Use gateway's MAC in sensor code.
   - Why? MACs are unique IDs for peering. Debug: Calibrate soil sensor (dry=high value ~4095, wet=low ~1000; map accordingly).

3. **Code Implementation for Sensor Node (2-3 hours)**:
   - Focus: Read sensors, structure data, send via ESP-NOW every 10s.
   - `main.ino` Skeleton:
     ```cpp
     #include <Arduino.h>
     #include <esp_now.h>
     #include <WiFi.h>
     #include <DHT.h>

     #define DHTPIN 4
     #define DHTTYPE DHT22
     DHT dht(DHTPIN, DHTTYPE);
     #define SOIL_PIN 34
     #define LED_PIN 2

     // Gateway MAC (replace with actual from step 2)
     uint8_t gatewayMac[] = {0x24, 0x0A, 0xC4, 0xXX, 0xXX, 0xXX};  // Example format

     // Data struct (floats for precision)
     typedef struct {
       float temperature;
       float humidity;
       float moisture;
     } SensorData;

     void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
       digitalWrite(LED_PIN, status == ESP_NOW_SEND_SUCCESS ? HIGH : LOW);  // LED on success
       Serial.print("Send Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
     }

     void setup() {
       Serial.begin(115200);
       pinMode(LED_PIN, OUTPUT);
       dht.begin();

       WiFi.mode(WIFI_STA);  // Required for ESP-NOW
       if (esp_now_init() != ESP_OK) {
         Serial.println("ESP-NOW Init Failed"); while(1);  // Halt on error
       }
       esp_now_register_send_cb(OnDataSent);  // Callback for send status

       // Add peer (gateway)
       esp_now_peer_info_t peerInfo = {};
       memcpy(peerInfo.peer_addr, gatewayMac, 6);
       peerInfo.channel = 0;  // Auto channel
       peerInfo.encrypt = false;  // No encryption for simplicity
       if (esp_now_add_peer(&peerInfo) != ESP_OK) {
         Serial.println("Failed to add peer"); while(1);
       }
     }

     void loop() {
       float temp = dht.readTemperature();
       float hum = dht.readHumidity();
       int soil_raw = analogRead(SOIL_PIN);
       float soil = map(soil_raw, 4095, 0, 0, 100);  // Invert: dry=0, wet=100; calibrate!

       // Error handling: Skip if NaN
       if (isnan(temp) || isnan(hum)) { Serial.println("Sensor Error"); delay(1000); return; }

       SensorData data = {temp, hum, soil};
       esp_err_t result = esp_now_send(gatewayMac, (uint8_t *)&data, sizeof(data));
       if (result != ESP_OK) { Serial.println("ESP-NOW Send Error"); }

       delay(10000);  // 10s interval
     }
     ```
   - Educational: Struct ensures typed data; callbacks handle async status (non-blocking). Pitfall: Data size <250 bytes (our struct ~12 bytes). Debug: Serial monitor for errors; test send without sensors first.

4. **Code Implementation for Gateway Node (2-3 hours)**:
   - Focus: Receive via ESP-NOW, forward to MQTT.
   - `main.ino` Skeleton:
     ```cpp
     #include <Arduino.h>
     #include <esp_now.h>
     #include <WiFi.h>
     #include <PubSubClient.h>

     #define LED_PIN 2

     const char* ssid = "YourSSID";
     const char* password = "YourPass";
     const char* mqtt_server = "industrial.api.ubidots.com";
     const char* mqtt_token = "YourUbidotsToken";
     const char* device_label = "/v1.6/devices/farmtech";

     // Same struct as sensor
     typedef struct {
       float temperature;
       float humidity;
       float moisture;
     } SensorData;

     WiFiClient espClient;
     PubSubClient client(espClient);

     void setup_wifi() {
       WiFi.begin(ssid, password);
       while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
       Serial.println("WiFi Connected");
     }

     void reconnect_mqtt() {
       while (!client.connected()) {
         if (client.connect("GatewayClient", mqtt_token, NULL)) {
           Serial.println("MQTT Connected");
         } else { delay(5000); }
       }
     }

     void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
       if (len != sizeof(SensorData)) { Serial.println("Invalid Data Size"); return; }
       SensorData data;
       memcpy(&data, incomingData, sizeof(data));

       Serial.printf("Received: Temp=%.2f, Hum=%.2f, Moisture=%.2f\n", data.temperature, data.humidity, data.moisture);
       digitalWrite(LED_PIN, HIGH); delay(100); digitalWrite(LED_PIN, LOW);  // Blink on receive

       // Forward to MQTT
       if (!client.connected()) { reconnect_mqtt(); }
       String payload = String("{\"temperature\":" + String(data.temperature) + ", \"humidity\":" + String(data.humidity) + ", \"moisture\":" + String(data.moisture) + "}");
       client.publish(device_label, payload.c_str());
     }

     void setup() {
       Serial.begin(115200);
       pinMode(LED_PIN, OUTPUT);

       WiFi.mode(WIFI_STA);
       if (esp_now_init() != ESP_OK) {
         Serial.println("ESP-NOW Init Failed"); while(1);
       }
       esp_now_register_recv_cb(OnDataRecv);  // Receive callback

       setup_wifi();
       client.setServer(mqtt_server, 1883);
     }

     void loop() {
       if (!client.connected()) { reconnect_mqtt(); }
       client.loop();  // Handle MQTT
       delay(100);  // Light loop
     }
     ```
   - Educational: No peer add needed for receive (broadcast mode); but for security, add sensor's MAC as peer. Pitfall: Ensure channels match (default auto). Debug: Test receive first with a dummy sender app.

5. **Service Setup and Testing (1-2 hours)**:
   - Ubidots: Same as before (variables for temp/hum/moisture, dashboard).
   - Test: Upload to both ESP32s (PIO Upload). Power sensor node (even battery if you have); monitor Serial on both. Data should flow: Sensor → Gateway → Ubidots.
   - Justification in GitHub: "Incorporated second ESP32 via ESP-NOW for efficient, low-power peer-to-peer data relay, simulating farm sensor networks. Sensors align to dataset (temp/hum for direct match, moisture for precip proxy)."

6. **Deliverables (1 hour)**:
   - GitHub `/ir-alem1`: Subfolders with codes, two diagrams (one per node), README section with justification/architecture.
   - Video: 4-5 min, show wiring both nodes, code uploads, Serial outputs, Ubidots updating. Narrate: "Sensor node sends via ESP-NOW... Gateway receives and publishes."

### Step-by-Step Plan for Ir Além 2: ML Classification with ESP32 (with ESP-NOW)

**Goal**: Classify plant health ("Healthy"/"Unhealthy") using real-time data from the dual-ESP32 system. Train on collected data; infer in real-time.

1. **Data Collection (1-2 hours)**:
   - Run the updated Ir Além 1 system for 1-2 hours. Vary conditions (e.g., heat DHT22, wet/dry soil sensor) to generate diverse data.
   - Use the same Python MQTT subscriber (`collector.py`) as before, but now data arrives via gateway. Add labeling:
     ```python
     # ... in on_message ...
     label = "Healthy" if 20 <= data['temperature'] <= 30 and 50 <= data['humidity'] <= 70 and data['moisture'] > 60 else "Unhealthy"
     writer.writerow([data['temperature'], data['humidity'], data['moisture'], label])
     ```
   - Collect 200+ rows in `sensor_data.csv`. Manually verify/edit labels (e.g., based on corn health thresholds from ag sources).
   - Why? ESP-NOW adds no change here; data quality improves with distributed setup.

2. **ML Model Development (3-4 hours)**:
   - Jupyter `ml_classifier.ipynb`: Same as before—load CSV, prep X/y, train LogisticRegression (or try RandomForestClassifier for non-linearity).
   - Validate: Add cross-validation `cross_val_score(model, X, y, cv=5)` for robustness.
   - Text: "Model accuracy XX%; justifies dual-ESP32: Enables scalable data from remote sensors. Limitations: Thresholds are simplified; real farms need more vars."

3. **Real-Time Inference (2 hours)**:
   - Extend `collector.py` to load trained model (pickle it from Jupyter: `import joblib; joblib.dump(model, 'classifier.pkl')`).
     ```python
     # Add to script
     import joblib
     model = joblib.load('classifier.pkl')

     # In on_message, after label (for validation)
     pred = model.predict([[data['temperature'], data['humidity'], data['moisture']]])[0]
     print(f"Predicted: {'Healthy' if pred == 1 else 'Unhealthy'}")

     # Optional alert: Publish back to MQTT "/alerts" (e.g., {"alert": pred})
     client.publish("/v1.6/devices/farmtech/alerts", str(pred))
     ```
   - On Gateway Node: Add MQTT subscribe in code:
     ```cpp
     // In setup: client.setCallback(mqttCallback);
     // Subscribe: client.subscribe("/v1.6/devices/farmtech/alerts");

     void mqttCallback(char* topic, byte* payload, unsigned int length) {
       String msg = "";
       for (int i = 0; i < length; i++) { msg += (char)payload[i]; }
       digitalWrite(LED_PIN, msg == "1" ? HIGH : LOW);  // Green LED if healthy
     }
     ```
   - Educational: Closes the loop—ML decisions actuate hardware. Pitfall: MQTT payload as string; parse carefully.

4. **Deliverables (1 hour)**:
   - GitHub `/ir-alem2`: Notebook, py scripts, updated diagram (include ESP-NOW flow to ML).
   - Video: 4-5 min, show data flow through nodes, collection, training, real-time pred/alert (e.g., "Wet sensor → Healthy → LED on").

This reformulation makes your project stand out as a complete, networked IoT-ML system. Test ESP-NOW range indoors first. If issues (e.g., no receive), check MACs/channels.