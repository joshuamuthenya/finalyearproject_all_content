/*
 * ESP32 Self-Test and ADC Calibration
 * This tests the ESP32's ADC and general functionality
 */

void setup() {
  Serial.begin(115200);
  
  Serial.println("===================================");
  Serial.println("ESP32 Self-Test & Validation");
  Serial.println("===================================");
  
  // Test serial communication
  Serial.println("Testing Serial Communication...");
  Serial.println("If you see this message, serial is working!");
  
  delay(1000);
  
  // Test internal temperature sensor (if available)
  Serial.println("\nTesting Internal Temperature Sensor...");
  testInternalTemperature();
  
  delay(1000);
  
  // Test WiFi capabilities
  Serial.println("\nTesting WiFi Capability...");
  testWiFi();
  
  delay(1000);
  
  // Test ADC pins
  Serial.println("\nTesting ADC Pins...");
  testADC();
}

void loop() {
  // Display system info every 10 seconds
  static unsigned long lastDisplay = 0;
  if (millis() - lastDisplay > 10000) {
    lastDisplay = millis();
    
    Serial.println("\nSystem Status:");
    Serial.print("Free Heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");
    
    Serial.print("Chip ID: ");
    Serial.println(ESP.getEfuseMac(), HEX);
    
    Serial.print("CPU Frequency: ");
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println(" MHz");
    
    Serial.print("Flash Size: ");
    Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
    Serial.println(" MB");
    
    Serial.println("-----------------------------------");
  }
  
  delay(1000);
}

void testInternalTemperature() {
  // Note: Not all ESP32 variants have accessible internal temp sensor
  Serial.println("Internal temperature reading not available on all ESP32");
  Serial.println("This is normal if you see 128°C or similar");
  Serial.println("External sensors (DHT, DS18B20) are recommended");
}

void testWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("No WiFi networks found (normal if no networks nearby)");
  } else {
    Serial.print("Found ");
    Serial.print(n);
    Serial.println(" WiFi networks");
    Serial.println("WiFi radio is functional!");
  }
  WiFi.mode(WIFI_OFF);
}

void testADC() {
  int pins[] = {34, 35, 32, 33, 25, 26, 27, 14, 12, 13, 4, 0, 2, 15};
  
  Serial.println("Testing ADC pins (should not be floating):");
  
  for (int i = 0; i < sizeof(pins)/sizeof(pins[0]); i++) {
    pinMode(pins[i], INPUT);
    int value = analogRead(pins[i]);
    float voltage = value * (3.3 / 4095.0);
    
    Serial.print("GPIO");
    Serial.print(pins[i]);
    Serial.print(": ADC=");
    Serial.print(value);
    Serial.print(" (");
    Serial.print(voltage, 2);
    Serial.print("V)");
    
    // Check for floating pins
    if (voltage > 3.0 || voltage < 0.1) {
      Serial.println(" - ⚠️  May be floating!");
    } else {
      Serial.println(" - OK");
    }
    delay(10);
  }
}