/*/*
 * MQ-7 Carbon Monoxide Sensor
 * Data Collection Only (No Logic, No Alerts)
 * Suitable for Serial Monitor & Serial Plotter
 *
 * Connections:
 * VCC  -> 5V
 * GND  -> GND
 * AOUT -> GPIO32 (ADC1_CH4)
 */

const int MQ7_PIN = 32;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("MQ7_Raw,Voltage");
}

void loop() {
  int rawValue = analogRead(MQ7_PIN);
  float voltage = rawValue * (3.3 / 4095.0);

  // CSV-style output (best for plotting & logging)
  Serial.print(rawValue);
  Serial.print(",");
  Serial.println(voltage, 3);

  delay(1000); // 1 sample per second
}
