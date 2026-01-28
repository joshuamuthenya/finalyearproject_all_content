/*
 * MQ-2 Gas Sensor Test
 * Connections:
 * - VCC → 5V
 * - GND → GND
 * - A0  → GPIO34 (ADC1_CH6)
 * - D0  → Not connected for analog test
 */

const int MQ2_PIN = 34;      // Analog pin for MQ-2
const float RLOAD = 10.0;    // Load resistance in kΩ
const float RZERO_MQ2 = 9.83; // Calibration resistance in clean air

void setup() {
  Serial.begin(115200);
  Serial.println("===================================");
  Serial.println("MQ-2 Gas Sensor Validation Test");
  Serial.println("===================================");
  delay(2000); // Allow sensor to warm up
}

void loop() {
  int rawValue = analogRead(MQ2_PIN);
  float voltage = rawValue * (3.3 / 4095.0); // ESP32 ADC is 0-3.3V
  
  // Calculate sensor resistance
  float rs = ((3.3 * RLOAD) / voltage) - RLOAD;
  
  // Calculate gas concentration (simplified ratio)
  float ratio = rs / RZERO_MQ2;
  
  Serial.println("MQ-2 Sensor Test:");
  Serial.print("Raw ADC: "); Serial.println(rawValue);
  Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
  Serial.print("Sensor Resistance: "); Serial.print(rs); Serial.println(" kΩ");
  Serial.print("RS/R0 Ratio: "); Serial.println(ratio);
  
  // Basic gas detection indication
  if (ratio < 0.8) {
    Serial.println("High Gas Concentration Detected!");
  } else if (ratio < 1.2) {
    Serial.println(" Normal Air Quality");
  } else {
    Serial.println("Sensor may need calibration");
  }
  
  Serial.println("-----------------------------------");
  delay(3000);
}