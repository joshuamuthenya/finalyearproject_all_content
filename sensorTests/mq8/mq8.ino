/*
 * MQ-8 Hydrogen Gas Sensor Test
 * Connections:
 * - VCC → 5V
 * - GND → GND
 * - A0  → GPIO33 (ADC1_CH5)
 */

const int MQ8_PIN = 33;
const float RLOAD = 10.0;
const float RZERO_MQ8 = 20.0; // Adjust based on calibration

void setup() {
  Serial.begin(115200);
  Serial.println("===================================");
  Serial.println("MQ-8 Hydrogen Sensor Validation Test");
  Serial.println("===================================");
  
  Serial.println("Warming up sensor (2 minutes)...");
  for (int i = 120; i > 0; i--) {
    if (i % 10 == 0) {
      Serial.print("Warm-up: ");
      Serial.print(i);
      Serial.println(" seconds remaining");
    }
    delay(1000);
  }
  Serial.println("Sensor ready!");
}

void loop() {
  // Take 10 readings for stability
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(MQ8_PIN);
    delay(10);
  }
  int rawValue = sum / 10;
  
  float voltage = rawValue * (3.3 / 4095.0);
  float rs = ((3.3 * RLOAD) / voltage) - RLOAD;
  float ratio = rs / RZERO_MQ8;
  
  Serial.println("MQ-8 Hydrogen Sensor Test:");
  Serial.print("Avg Raw ADC: "); Serial.println(rawValue);
  Serial.print("Voltage: "); Serial.print(voltage, 3); Serial.println(" V");
  Serial.print("RS/R0 Ratio: "); Serial.println(ratio, 3);
  
  // Hydrogen detection
  if (ratio < 0.3) {
    Serial.println("⚠️  HIGH HYDROGEN CONCENTRATION - DANGER!");
  } else if (ratio < 0.8) {
    Serial.println("⚠️  Hydrogen detected - Caution");
  } else if (ratio < 1.5) {
    Serial.println("✅ Normal - No hydrogen detected");
  } else {
    Serial.println("📊 Sensor in clean air");
  }
  
  Serial.println("-----------------------------------");
  delay(3000);
}