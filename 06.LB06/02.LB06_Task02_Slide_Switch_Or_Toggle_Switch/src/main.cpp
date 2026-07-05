#include <Arduino.h>
const int SWITCH_PIN = 5; // You can use GPIO 4, 5, 18, etc.

// Variable to store the last known state of the switch
int lastSwitchState = -1;

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);

  Serial.println("Slide Switch / Toggle Switch  Test");

  // Configure the switch pin as an INPUT with internal pull-up resistor
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
  // Read the current state of the switch
  int currentSwitchState = digitalRead(SWITCH_PIN);

  // Check if the switch has been flipped to a new position
  if (currentSwitchState != lastSwitchState) {

    // If the pin is LOW, the switch closed the circuit to GND (ON)
    if (currentSwitchState == LOW) {
      Serial.println("Switch: ON");
    }
    // If the pin is HIGH, the switch opened the circuit (OFF)
    else {
      Serial.println("Switch: OFF");
    }

    // Save the current state for the next loop iteration
    lastSwitchState = currentSwitchState;

    // Small delay to prevent reading contact bounce while flipping
    delay(50);
  }
}