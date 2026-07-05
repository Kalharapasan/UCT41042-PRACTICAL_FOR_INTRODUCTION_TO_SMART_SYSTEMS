#include <Arduino.h>

// Define the pins
const int SWITCH_PIN = 5; 
const int LED_PIN    = 2; // Internal LED

void setup() {
  Serial.begin(115200);

  // Set the switch pin as input with internal pull-up
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  
  // Set the onboard LED as output
  pinMode(LED_PIN, OUTPUT);

  Serial.println("System Initialized. Flip the switch!");
}

void loop() {
  // Read the current position of the switch
  int switchState = digitalRead(SWITCH_PIN);

  if (switchState == LOW) {
    // Switch is closed (connected to GND)
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Status: ON");
  } else {
    // Switch is open (HIGH due to pull-up)
    digitalWrite(LED_PIN, LOW);
    Serial.println("Status: OFF");
  }

  // Small delay to prevent flooding the Serial Monitor
  delay(200);
}