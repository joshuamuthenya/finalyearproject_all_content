# IoT Air Quality Monitoring System

## Overview
This project implements an **IoT-based air quality monitoring system** using an ESP32 microcontroller and various sensors. The system measures **air quality, temperature, and humidity**, providing **visual and audible alerts** when unsafe levels are detected. Optional Wi-Fi connectivity allows **remote monitoring** and cloud data logging.

**Key Features:**
- Measures **particulate matter (PM2.5 and PM10)** using the NOVA PM sensor.
- Detects **harmful and combustible gases** with MQ-series sensors (e.g., MQ-135, MQ-7).
- Monitors **temperature and humidity** with DHT11 sensor.
- Provides **LED and buzzer alerts** for hazardous air quality.
- Powered by a **12V battery with step-down voltage regulators** for ESP32 and sensors.
- Optional **Wi-Fi connectivity** for remote monitoring or IoT applications.

---

## Hardware Components
| Component           | Specification / Value              |
|--------------------|----------------------------------|
| ESP32               | Dev kit, 3.3V logic               |
| MQ-Series Sensors   | MQ-135 / MQ-7, 5V supply          |
| NOVA PM Sensor      | SDS011, PM2.5/PM10, 5V            |
| DHT11               | Temperature & Humidity, 5V        |
| Battery             | 12V Li-ion or Lead-acid, 2–5Ah    |
| Voltage Regulator   | Buck converter 12V → 5V/3.3V      |
| LEDs                | 5mm, Red/Green/Blue, 220Ω         |
| Buzzer              | 5V Active Piezo                    |
| Push Buttons        | Standard tactile                   |
| Resistors           | 10kΩ, 4.7kΩ, 1kΩ, 220Ω            |
| Capacitors          | 100µF, 10µF, 0.1µF                 |
| Breadboard / Stripboard | For prototyping and assembly   |
| Jumper Wires        | 20 cm male-to-male                  |
| Enclosure           | ABS plastic project box            |

---

## Software Requirements
- **Arduino IDE** (latest version)  
- ESP32 board package installed via Arduino Board Manager  
- Required libraries:
  - `DHT.h` for DHT11 sensor  
  - `SoftwareSerial.h` for NOVA PM sensor  
  - Optional: `WiFi.h` and `HTTPClient.h` for IoT/cloud features  

---

## Installation

### Hardware Setup
1. Connect ESP32 to sensors according to the wiring diagram (`docs/wiring.pdf`).  
2. Use a **buck/step-down converter** to supply 5V/3.3V from the 12V battery to the ESP32 and sensors.  
3. Connect LEDs, buzzer, and push buttons according to the circuit diagram.

### Software Setup
1. Open `main.ino` in Arduino IDE.  
2. Select **ESP32 Dev Kit** as the target board.  
3. Install the required libraries listed above.  
4. Modify Wi-Fi credentials in `main.ino` if using remote monitoring.  
5. Upload the code to the ESP32.

---

## Usage
- Power on the system via 12V battery or DC adapter.  
- The system continuously monitors **air quality, temperature, and humidity**.  
- LEDs indicate air quality:  
  - **Green** – Safe  
  - **Yellow** – Moderate  
  - **Red** – Hazardous  
- The buzzer alerts when air quality exceeds safe limits.  
- Optional: Connect ESP32 to Wi-Fi for **remote monitoring or cloud logging**.

---





