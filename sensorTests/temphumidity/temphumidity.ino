#include <DHT.h>

#define DHTPIN 22       // Digital pin connected to the DHT11
#define DHTTYPE DHT11   // Change to DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(5000); // Wait 5 seconds for sensor to initialize
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Error reading from DHT11 sensor!");
  } else {
    Serial.print("Humidity: "); Serial.print(humidity); Serial.print(" %\t");
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
  }

  delay(2000); // Read every 2 seconds
}

