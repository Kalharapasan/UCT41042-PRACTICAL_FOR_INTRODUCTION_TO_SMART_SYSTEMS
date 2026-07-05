#include <Arduino.h>
const int LED_PIN = 5; // GPIO 5 is also the built-in blue LED on most ESP32 boards

void setup() {
  // Configure the LED pin as an OUTPUT
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Turn the LED ON (HIGH voltage level)
  digitalWrite(LED_PIN, HIGH);
  delay(1000); // Wait for 1 second (1000 milliseconds)

  // Turn the LED OFF (LOW voltage level)
  digitalWrite(LED_PIN, LOW);
  delay(1000); // Wait for 1 second
}