
1. **Set Up Git and Software (30-45 min)**: Initialize repo, install VS Code/PlatformIO, test ESP32 connection.
2. **Wire Sensor Node (45-60 min)**: Connect DHT22, soil moisture sensor, LED, and buzzer to ESP32 #1.
3. **Code and Test Sensor Node (1.5-2 hours)**: Write/upload C++ code to read sensors and print to Serial Monitor.
4. **Initial Data Check and Debug (30-45 min)**: Verify readings, calibrate, and push to GitHub.

This keeps you hands-on, learning embedded systems basics, and progressing toward IoT/ML integration. Let’s go!

---

### Phase 1: Set Up Git and Software Environment (30-45 minutes)
**Goal**: Get your PC ready for coding, connect to GitHub, and ensure ESP32 communicates with VS Code/PlatformIO.

**Educational Notes**:
- **Git**: A version control system to track code changes and share on GitHub. Think of it as a "save history" for your project.
- **PlatformIO**: A plugin for VS Code that compiles C++ for ESP32, manages libraries (like DHT22 drivers), and uploads code via USB.
- **Theory**: ESP32 is a microcontroller—a tiny computer with CPU, memory, and pins to interface with sensors. It runs your code in a loop, reading inputs (sensors) and sending outputs (e.g., Serial data).

**Steps**:
1. **Initialize Local Git Repository (5-10 min)**:
   - Open VS Code. Create a folder `FarmTech-IoT-ML-System` on your PC (e.g., Desktop).
   - In VS Code: File > Open Folder > Select this folder.
   - Open Terminal (Ctrl+`) and run:
     ```bash
     git init
     git remote add origin https://github.com/YourUsername/FarmTech-IoT-ML-System.git
     ```
     Replace `YourUsername` with your GitHub username.
   - Create initial files:
     - `README.md`: Paste the description and tags from before.
     - Folders: `/entrega1`, `/ir-alem1/sensor-node`, `/ir-alem1/gateway-node`, `/ir-alem2`.
     - Run:
       ```bash
       git add .
       git commit -m "Initial commit with repo structure and README"
       git push -u origin main
       ```
   - **Why?**: Sets up version control; folders organize deliverables (Entrega 1 notebook, Ir Além codes). **Pitfall**: If push fails, ensure you’re logged into GitHub CLI (`git config --global user.email "your@email.com"`).

2. **Install VS Code and PlatformIO (10-15 min)**:
   - Download VS Code from code.visualstudio.com if not already installed. Run installer.
   - In VS Code: Extensions (Ctrl+Shift+X) > Search “PlatformIO IDE” > Install. Restart VS Code.
   - **Theory**: PlatformIO automates building/uploading code and managing libraries, unlike manual Arduino IDE setups.

3. **Install ESP32 USB Driver (5-10 min)**:
   - Plug Sensor Node ESP32 (label it #1) into a USB port (use micro-USB cable from kit or similar).
   - Windows: If not recognized (check Device Manager: Win+R, `devmgmt.msc`), download CP210x driver from silabs.com/developers/usb-to-uart-bridge-vcp-drivers. Install and replug ESP32.
   - Mac/Linux: Usually auto-detected (check `lsusb` or `dmesg | grep usb` in terminal).
   - **Why?**: Drivers enable serial communication between PC and ESP32 for code upload and debugging.

4. **Test ESP32 Connection (5-10 min)**:
   - In VS Code: Ctrl+Shift+P > “PlatformIO: Serial Monitor” > Select port (e.g., COM3 on Windows, /dev/ttyUSB0 on Linux/Mac) > Set baud to 115200.
   - If port appears, connection works. If not, try another USB cable/port or reinstall driver.
   - **Debug**: If no ports show, unplug/replug ESP32, restart VS Code.

**Progress Check**: GitHub repo initialized, VS Code/PlatformIO ready, ESP32 detected. Commit: `git commit -m "Setup dev environment"`.

---

### Phase 2: Wire the Sensor Node (ESP32 #1) on Protoboard (45-60 minutes)
**Goal**: Physically connect DHT22, soil moisture sensor, LED, and buzzer to ESP32 #1 for data collection.

**Educational Notes**:
- **Protoboard**: A grid of holes where rows (horizontal, 5 holes) connect electrically for signals, and rails (vertical, red/blue) distribute power/GND. Think of it as a temporary circuit board.
- **ESP32 Pins**: Labeled (e.g., 3V3, GND, GPIOXX). 3.3V powers sensors; GND completes circuits; GPIO pins read/write signals (digital: 0/1; analog: 0-4095).
- **Sensors**: Convert physical properties (heat, moisture) to electrical signals. DHT22 uses digital pulses; soil sensor outputs analog voltage.
- **Safety**: Unplug USB when wiring to avoid shorts. Static can damage ESP32—touch metal first.

**Steps**:
1. **Prepare Workspace (5 min)**:
   - Clear a non-conductive surface (wooden table). Unbox kit and sensors.
   - Identify components:
     - **ESP32 NodeMCU**: Small board with USB, ~30 pins. Role: Brain for reading sensors, running code.
     - **DHT22**: White/blue module, 3-4 pins (VCC, GND, Data, NC). Role: Measures temp/humidity for crop dataset.
     - **Soil Moisture Sensor (Capacitive)**: Long probe with board, 3 pins (VCC, GND, A0). Role: Proxy for precipitation via soil wetness.
     - **LED (Green)**: Tiny bulb, long leg (anode/+), short leg (cathode/-). Role: Visual feedback (e.g., data sent).
     - **Buzzer**: Small cylinder, + and - pins. Role: Alerts for unhealthy crops.
     - **Jumpers**: Colored wires (use red for 3.3V, black for GND, others for signals).
     - **Resistors**: Use 470 ohm for LED, 10k for DHT22 pull-up if needed.
     - **Protoboard**: 760-point grid (rows for signals, red/blue rails for power).

2. **Mount ESP32 on Protoboard (5-10 min)**:
   - Insert ESP32 across protoboard’s center divide (pins straddle gap, USB port outward for access). Push gently until secure.
   - **Theory**: Rows connect 5 holes; center gap isolates sides. ESP32 pins (e.g., GPIO4) link to sensors.

3. **Set Up Power Rails (5-10 min)**:
   - Jumper ESP32’s 3V3 pin (top-right, labeled) to red rail (+).
   - Jumper any GND pin (multiple, e.g., next to 3V3) to blue rail (-).
   - **Theory**: 3.3V powers sensors; GND is the 0V reference. Rails distribute to all components.
   - **Debug**: Tug wires to ensure tight fit.

4. **Wire DHT22 Sensor (10-15 min)**:
   - VCC to red rail (3.3V).
   - GND to blue rail.
   - Data to ESP32 GPIO4 (count pins: GPIO4 is ~7th from left on right side). Use a colored jumper (e.g., blue).
   - Optional: Connect 10k resistor between Data and VCC (stabilizes signal if readings are erratic).
   - **Theory**: DHT22 sends digital data (temp/humidity as binary pulses). GPIO4 is digital-capable.
   - **Role**: Matches dataset’s “Temperature at 2m” and “Relative Humidity at 2m” for ML.

5. **Wire Soil Moisture Sensor (10-15 min)**:
   - VCC to red rail.
   - GND to blue rail.
   - A0 to ESP32 GPIO34 (analog pin, ~12th pin on left side).
   - **Theory**: Outputs 0-3.3V based on soil water (wet=lower voltage). ESP32’s ADC converts to 0-4095.
   - **Role**: Proxy for “Precipitation” (wet soil implies good water conditions).

6. **Wire Feedback Components (10-15 min)**:
   - LED: Long leg to 470 ohm resistor, resistor to GPIO2, short leg to blue rail.
   - Buzzer: + to GPIO5, - to blue rail.
   - **Theory**: LED lights with ~2V forward voltage; resistor limits current (Ohm’s Law: V=IR). Buzzer vibrates for sound with pulses.
   - **Role**: LED blinks on data send; buzzer beeps for ML alerts (Ir Além 2).

7. **Visual Check (5 min)**:
   - Ensure no crossed wires. Use phone camera for close-up. Example layout: ESP32 center, sensors on one side, LED/buzzer on other.
   - **Debug**: If loose, push pins firmly. If unsure, trace each wire to pin/rail.

**Progress Check**: Sensor Node wired, ready for coding. Unplug USB for safety.

---

### Phase 3: Code and Test Sensor Node (1.5-2 hours)
**Goal**: Write/upload C++ code to read sensors and print to Serial Monitor, verifying hardware works.

**Educational Notes**:
- **C++/Arduino**: Code runs in `setup()` (runs once) and `loop()` (repeats). We use libraries for sensors (DHT) and ESP32 functions.
- **Serial Monitor**: Outputs debug text (e.g., sensor values) to PC via USB.
- **Theory**: ESP32’s GPIO pins are programmable—digital for DHT22 (reads pulses), analog for soil (reads voltage). This code tests hardware before ESP-NOW.

**Steps**:
1. **Create PlatformIO Project (10-15 min)**:
   - In VS Code: Ctrl+Shift+P > “PlatformIO: New Project”.
   - Name: “sensor-node”, Board: “ESP32 Dev Module”, Framework: “Arduino”. Creates folder in your repo at `/ir-alem1/sensor-node`.
   - **Why?**: PlatformIO manages dependencies and uploads.

2. **Install Libraries (5-10 min)**:
   - In VS Code: PIO Home > Libraries > Search “DHT sensor library by Adafruit” > Add to Project (installs for sensor-node).
   - **Theory**: Libraries provide pre-written functions (e.g., `dht.readTemperature()` simplifies reading pulses).

3. **Write Test Code (15-20 min)**:
   - Open `/ir-alem1/sensor-node/src/main.ino`. Paste this test code (simplified from final version to verify wiring):
     ```cpp
     #include <Arduino.h>
     #include <DHT.h>

     #define DHTPIN 4          // DHT22 data pin
     #define DHTTYPE DHT22     // Sensor type
     DHT dht(DHTPIN, DHTTYPE);
     #define SOIL_PIN 34       // Soil moisture analog pin
     #define LED_PIN 2         // LED for status
     #define BUZZER_PIN 5      // Buzzer for alerts

     void setup() {
       Serial.begin(115200);  // Start Serial for debugging
       pinMode(LED_PIN, OUTPUT);
       pinMode(BUZZER_PIN, OUTPUT);
       dht.begin();  // Initialize DHT22
     }

     void loop() {
       // Read sensors
       float temp = dht.readTemperature();  // Celsius
       float hum = dht.readHumidity();      // %
       int soil_raw = analogRead(SOIL_PIN); // 0-4095
       float soil = map(soil_raw, 4095, 1000, 0, 100);  // Map to 0-100% (calibrate later)

       // Validate data
       if (isnan(temp) || isnan(hum)) {
         Serial.println("DHT22 reading failed!");
         digitalWrite(LED_PIN, HIGH);  // Blink on error
         delay(100);
         digitalWrite(LED_PIN, LOW);
       } else {
         Serial.printf("Temp: %.2f°C, Humidity: %.2f%%, Soil Moisture: %.2f%%\n", temp, hum, soil);
         digitalWrite(LED_PIN, HIGH);  // Blink on success
         delay(100);
         digitalWrite(LED_PIN, LOW);
       }

       // Test buzzer
       tone(BUZZER_PIN, 1000, 200);  // Short beep every loop

       delay(2000);  // Read every 2s for testing
     }
     ```
   - **Theory**: Reads sensors, prints to Serial, blinks LED, beeps buzzer. `map()` converts soil’s 0-4095 to 0-100% (inverted: dry=high, wet=low).

4. **Upload and Test Code (20-30 min)**:
   - Plug Sensor Node into USB.
   - In VS Code: Bottom toolbar > Build (hammer icon). Fix errors (e.g., missing library).
   - Upload (arrow icon): Select port if prompted.
   - Open Serial Monitor (plug icon, 115200 baud). Expect output like:
     ```
     Temp: 25.50°C, Humidity: 60.20%, Soil Moisture: 10.00%
     ```
   - Vary conditions: Breathe on DHT22 (humidity up), wet soil sensor (moisture up). LED should blink, buzzer beep every 2s.
   - **Debug**: No output? Check port, baud, or re-upload driver. Bad readings? Check wiring (loose pins common).

5. **Calibrate Sensors (15-20 min)**:
   - **Soil Sensor**: Dry probe (air) = ~0% (raw ~4095). Dip in water = ~100% (raw ~1000). Adjust `map()` in code if needed (test values with Serial).
   - **DHT22**: Compare temp to phone weather app (e.g., ~25°C indoors). If off by >2°C, check resistor or pin.
   - Note values in a text file for GitHub docs.

**Progress Check**: Sensor Node reads data, prints to Serial, LED/buzzer works. Save calibration notes.

---

### Phase 4: Initial Data Check and Push to GitHub (30-45 minutes)
**Goal**: Verify sensor functionality, save data, and commit to repo.

**Educational Notes**:
- **Data Validation**: Ensures sensors work before ESP-NOW/MQTT. Bad data (e.g., NaN) means wiring/code issues.
- **Git Workflow**: Commit often but push final changes before deadline. Use descriptive messages.

**Steps**:
1. **Run and Observe (10-15 min)**:
   - Keep Serial Monitor open. Run for 5-10 min, varying conditions (wet/dry soil, heat DHT22 with hand).
   - Expect: Temp 20-30°C, Humidity 40-70%, Soil 0-100% (adjust based on tests). Buzzer beeps every 2s, LED blinks.
   - **Debug**: NaN values? Check DHT wiring. Soil stuck? Verify GPIO34. No buzz? Swap buzzer pins.

2. **Create Python Collector Stub (10-15 min)**:
   - To prepare for Ir Além 2, create a basic script to log Serial data (we’ll replace with MQTT later). In `/ir-alem2/test_collector.py`:
     ```python
     import serial
     import csv
     import time

     # Adjust port (e.g., COM3, /dev/ttyUSB0)
     ser = serial.Serial('COM3', 115200, timeout=1)
     with open('sensor_data.csv', 'w', newline='') as f:
         writer = csv.writer(f)
         writer.writerow(['temperature', 'humidity', 'moisture'])
         while True:
             line = ser.readline().decode().strip()
             if 'Temp' in line:
                 parts = line.split(',')
                 temp = float(parts[0].split(':')[1].split('°C')[0])
                 hum = float(parts[1].split(':')[1].split('%')[0])
                 moist = float(parts[2].split(':')[1].split('%')[0])
                 writer.writerow([temp, hum, moist])
                 print(f"Logged: {temp}, {hum}, {moist}")
             time.sleep(1)
     ```
   - Install: `pip install pyserial` in VS Code terminal.
   - Run: `python test_collector.py`. Check `sensor_data.csv` grows.
   - **Theory**: Simulates data collection for ML training.

3. **Commit to GitHub (5-10 min)**:
   - In `/ir-alem1/sensor-node`, save `main.ino`.
   - In `/ir-alem2`, save `test_collector.py` and initial `sensor_data.csv`.
   - Run:
     ```bash
     git add .
     git commit -m "Sensor Node test code and initial data collection"
     git push origin main
     ```
   - Check GitHub: Files should appear.

**Progress Check**: Sensor Node works, data logs to CSV, repo updated. You’ve built the IoT foundation!

---

### Next Steps for Today’s 4 Hours
You’re at ~4 hours now (30 + 60 + 120 + 30 = 240 min). If you have extra time:
- **Wire Gateway Node (15-20 min)**: Repeat Phase 2 for ESP32 #2 (no sensors, just LED/buzzer on GPIO2/5).
- **Get MAC Address**: Upload this to each ESP32, note MACs for ESP-NOW:
  ```cpp
  #include <WiFi.h>
  void setup() { Serial.begin(115200); Serial.println(WiFi.macAddress()); }
  void loop() {}
  ```
- **Plan Tomorrow**: Start ESP-NOW code (replace test code with full script from earlier).

**Tips**:
- Take photos of wiring for GitHub/docs.
- If stuck, search “ESP32 DHT22 tutorial” on YouTube or ask for specific debug help.
- Commit frequently: `git commit -m "WIP: wiring done"` to track progress.
