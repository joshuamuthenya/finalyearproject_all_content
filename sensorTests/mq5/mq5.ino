/*
 * MQ-5 LPG/Natural Gas Sensor Test
 * Connections:
 * - VCC → 5V
 * - GND → GND
 * - A0  → GPIO35 (ADC1_CH7)
 */

const int MQ5_PIN = 35;      // Analog pin for MQ-5
const float RLOAD = 10.0;    // Load resistance in kΩ
const float RZERO_MQ5 = 6.5; // Calibration resistance in clean air

void setup() {
  Serial.begin(115200);
  Serial.println("===================================");
  Serial.println("MQ-5 Gas Sensor Validation Test");
  Serial.println("===================================");
  Serial.println("Sensor warm-up: 60 seconds");
  
  for (int i = 60; i > 0; i--) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nWarm-up complete!");
}

void loop() {
  int rawValue = analogRead(MQ5_PIN);
  float voltage = rawValue * (3.3 / 4095.0);
  
  float rs = ((3.3 * RLOAD) / voltage) - RLOAD;
  float ratio = rs / RZERO_MQ5;
  
  Serial.println("MQ-5 Sensor Test:");
  Serial.print("Raw ADC: "); Serial.println(rawValue);
  Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
  Serial.print("RS/R0 Ratio: "); Serial.println(ratio, 2);
  
  // LPG/Natural gas indication
  if (ratio < 0.7) {
    Serial.println("⚠️  HIGH LPG/Natural Gas Detected!");
  } else if (ratio < 1.3) {
    Serial.println("✅ Normal - No LPG detected");
  } else {
    Serial.println("📊 Sensor in clean air");
  }
  
  Serial.println("-----------------------------------");
  delay(2000);
}