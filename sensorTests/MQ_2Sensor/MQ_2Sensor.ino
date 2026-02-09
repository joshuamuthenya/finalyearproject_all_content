#define MQ2_PIN 32

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  delay(10000); // MQ-2 warm-up
}

void loop() {
  int raw = analogRead(MQ2_PIN);
  float voltage = raw * (3.3 / 4095.0);

  Serial.print(raw);
  Serial.print(",");
  Serial.println(voltage, 3);

  delay(1000);
}
