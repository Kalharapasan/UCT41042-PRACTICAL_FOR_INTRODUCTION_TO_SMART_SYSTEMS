#include <Arduino.h>
// Define the LED pin
const int ledPin = 5; 

void setup() {
  // Initialize the digital pin as an output
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("LED Blink Test Started");
}

void loop() {
  // Turn the LED on (HIGH is the voltage level)
  digitalWrite(ledPin, HIGH);
  Serial.println("LED ON");
  delay(1000); // Wait for a second

  // Turn the LED off by making the voltage LOW
  digitalWrite(ledPin, LOW);
  Serial.println("LED OFF");
  delay(1000); // Wait for a second
}