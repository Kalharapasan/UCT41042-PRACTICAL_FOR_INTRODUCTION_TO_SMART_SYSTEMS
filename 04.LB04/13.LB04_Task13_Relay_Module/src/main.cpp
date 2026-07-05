#include <Arduino.h>
// Define the Relay Pin
const int relayPin = 5;

void setup() {
  // Initialize the relay pin as an output
  pinMode(relayPin, OUTPUT);
  
  // Set initial state to OFF (for Active Low relays)
  digitalWrite(relayPin, HIGH); 
  
  Serial.begin(115200);
  Serial.println("Relay Test Started");
}

void loop() {
  // Turn the relay ON
  Serial.println("Relay ON - Device Running");
  digitalWrite(relayPin, LOW); 
  delay(3000); // Keep it on for 3 seconds

  // Turn the relay OFF
  Serial.println("Relay OFF - Device Stopped");
  digitalWrite(relayPin, HIGH); 
  delay(3000); // Keep it off for 3 seconds
}