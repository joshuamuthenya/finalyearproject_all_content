#include <HardwareSerial.h>

HardwareSerial sdsSerial(2); // Use UART2
#define SDS_RX 16  // Connect SDS011 TX → ESP32 RX2
#define SDS_TX 17  // Optional, not used if only reading

uint8_t buffer[10];

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Initializing SDS011/SDS198 sensor...");
  sdsSerial.begin(9600, SERIAL_8N1, SDS_RX, SDS_TX);
  Serial.println("Warming up for 30s...");
  delay(30000); // Warm-up time
  Serial.println("Sensor ready!");
}

void loop() {
  // Wait until at least 10 bytes are available
  while (sdsSerial.available() >= 10) {
    // Peek first byte to find header
    if (sdsSerial.peek() == 0xAA) {
      buffer[0] = sdsSerial.read();
      if (sdsSerial.read() == 0xC0) { // Command byte check
        // Read remaining 8 bytes
        for (int i = 2; i < 10; i++) {
          while (!sdsSerial.available());
          buffer[i] = sdsSerial.read();
        }

        // Checksum validation
        uint8_t checksum = 0;
        for (int i = 2; i <= 7; i++) checksum += buffer[i];
        checksum = checksum % 256;
        if (checksum != buffer[8]) {
          Serial.println("Checksum error, skipping frame");
          return;
        }

        // Parse PM2.5 and PM10
        uint16_t pm2_5 = buffer[2] + (buffer[3] << 8);
        uint16_t pm10  = buffer[4] + (buffer[5] << 8);

        // Print PM values
        Serial.print("PM2.5: "); Serial.print(pm2_5); Serial.print(" μg/m³\t");
        Serial.print("PM10: "); Serial.print(pm10); Serial.println(" μg/m³");

        // ------------------ Air Quality Interpretation ------------------
        Serial.print("Air Quality: ");
        if (pm2_5 <= 12) Serial.println("✅ Excellent");
        else if (pm2_5 <= 35) Serial.println("⚠ Moderate");
        else if (pm2_5 <= 55) Serial.println("⚠ Unhealthy for sensitive groups");
        else if (pm2_5 <= 150) Serial.println("❌ Unhealthy");
        else Serial.println("❌❌ Hazardous");

        Serial.println("-----------------------------------");
      }
    } else {
      sdsSerial.read(); // discard invalid byte
    }
  }

  delay(2000); // Wait 2 seconds before reading next frame
}


