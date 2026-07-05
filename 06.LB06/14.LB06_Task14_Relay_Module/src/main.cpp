#include <Arduino.h>
const int RELAY_PIN = 5; // You can use GPIO 25, 26, 27, etc.

void setup() {
  // Configure the relay pin as an OUTPUT
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Relay Module Test");
  // Optional: Set initial state to OFF. 
  // For Active-Low relays, HIGH = OFF. For Active-High relays, LOW = OFF.
  digitalWrite(RELAY_PIN, LOW); 
}

void loop() {
  // Turn the relay ON
  digitalWrite(RELAY_PIN, HIGH); 
  delay(2000); // Wait for 2 seconds

  // Turn the relay OFF
  digitalWrite(RELAY_PIN, LOW); 
  delay(2000); // Wait for 2 seconds
}