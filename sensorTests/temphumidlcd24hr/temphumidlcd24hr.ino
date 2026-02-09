#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* =======================
   DHT CONFIGURATION
   ======================= */
#define DHTPIN   19        // GPIO connected to DHT11 data pin (unique, not 21/22)
#define DHTTYPE  DHT11

DHT dht(DHTPIN, DHTTYPE);

/* =======================
   I2C LCD CONFIGURATION
   ======================= */
#define I2C_SDA 21
#define I2C_SCL 22
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

/* =======================
   TIMING CONTROL
   ======================= */
const unsigned long READ_INTERVAL = 2000; // 2 seconds
unsigned long lastReadTime = 0;

void setup() {
  Serial.begin(115200);

  /* Explicitly initialize I2C with chosen pins */
  Wire.begin(I2C_SDA, I2C_SCL);

  dht.begin();

  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("DHT11 Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  delay(3000); // Sensor stabilization
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentMillis;

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature(); // Celsius

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("DHT11 read error");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sensor Error");
      lcd.setCursor(0, 1);
      lcd.print("Check Wiring");

      return;
    }

    /* ===== Serial Monitor Output ===== */
    Serial.print("Humidity: ");
    Serial.print(humidity, 1);
    Serial.print(" %  |  ");

    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(" C");

    /* ===== LCD Output ===== */
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature, 1);
    lcd.print((char)223); // Degree symbol
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Hum : ");
    lcd.print(humidity, 1);
    lcd.print(" %");
  }
}
