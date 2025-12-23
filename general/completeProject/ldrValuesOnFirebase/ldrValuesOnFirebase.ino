/***************************************************************
 * Project: LDR Sensor to Firebase using ESP32
 * Author : Joshua Wambua (example)
 * Date   : 2025-11-03
 ***************************************************************/

#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Insert your Firebase project credentials
#define WIFI_SSID "mdayz"
#define WIFI_PASSWORD "1234554321"

#define API_KEY "AIzaSyAv9jIBDr3S7ZWJvQJgceRyatSryIzl0EI"
#define DATABASE_URL "https://esp32ldr-32196-default-rtdb.firebaseio.com/"  // Replace with your database URL

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int ldrPin = 34;  // ADC1_6 on ESP32
int ldrValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ldrPin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected!");

  // Firebase configuration
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Anonymous sign-in (no email/password)
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase connected!");
  } else {
    Serial.printf("Firebase signup failed: %s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  ldrValue = analogRead(ldrPin);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (Firebase.RTDB.setInt(&fbdo, "/ldr/value", ldrValue)) {
    Serial.println("Value pushed to Firebase successfully!");
  } else {
    Serial.println(fbdo.errorReason());
  }

  delay(2000);  // send every 2 seconds
}
