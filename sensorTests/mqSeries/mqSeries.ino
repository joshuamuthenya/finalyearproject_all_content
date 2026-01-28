/*
  Author: Joshua Wambua
  Date: 02/11/2025
  Description:
  Modular program for MQ2 and MQ5 gas sensors with LED control via push button.
  Demonstrates use of functions, parameters, and clean structure.
*/

// --- Pin Assignments ---
const int MQ2_PIN = 15;
const int MQ5_PIN = 2;
const int LED_PIN = 4;
const int BUTTON_PIN = 23;

// --- Function Declarations ---
int readSensor(int sensorPin);
void displayReadings(int coValue, int lpgValue);
void controlLED(int buttonPin, int ledPin);
void systemStatus();

// --- Setup Function ---
void setup() {
  Serial.begin(115200);
  pinMode(MQ2_PIN, INPUT);
  pinMode(MQ5_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // active LOW
  pinMode(LED_PIN, OUTPUT);

  Serial.println("=== System Initialized ===");
  delay(1000);
}

// --- Loop Function ---
void loop() {
  systemStatus(); // Display header info

  // 1️⃣ Read sensor data
  int coValue = readSensor(MQ2_PIN);
  int lpgValue = readSensor(MQ5_PIN);

  // 2️⃣ Display data
  displayReadings(coValue, lpgValue);

  // 3️⃣ Control LED with button
  controlLED(BUTTON_PIN, LED_PIN);

  delay(1000);
}

// --- Function Definitions ---

// Reads an analog value from a given pin
int readSensor(int sensorPin) {
  int value = analogRead(sensorPin);
  return value;
}

// Displays gas readings on the serial monitor
void displayReadings(int coValue, int lpgValue) {
  Serial.print("CO Sensor Value: ");
  Serial.println(coValue);
  Serial.print("LPG Sensor Value: ");
  Serial.println(lpgValue);
  Serial.println("---------------------------");
}

// Reads a button and turns an LED on/off accordingly
void controlLED(int buttonPin, int ledPin) {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) { // Button pressed
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
  }
}

// Prints system status info or banner
void systemStatus() {
  Serial.println("\n===== SYSTEM RUNNING =====");
}
