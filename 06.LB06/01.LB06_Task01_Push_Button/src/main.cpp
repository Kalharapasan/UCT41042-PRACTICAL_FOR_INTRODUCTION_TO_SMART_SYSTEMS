#include <Arduino.h>
const int BUTTON_PIN = 5; // You can use GPIO 4, 5, 18, etc.

// Variable to store the last known state of the button
int lastButtonState = HIGH; 

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  Serial.println("Push Button Test");
  
  // Configure the button pin as an INPUT with internal pull-up resistor
  // This keeps the pin HIGH when the button is NOT pressed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Read the current state of the button
  int currentButtonState = digitalRead(BUTTON_PIN);

  // Check if the state has changed
  if (currentButtonState != lastButtonState) {
    
    // If the state went from HIGH to LOW, the button was pressed
    if (currentButtonState == LOW) {
      Serial.println("Button Pressed");
    } 
    // If the state went from LOW to HIGH, the button was released
    else {
      Serial.println("Button Released");
    }
    
    // Save the current state for the next loop iteration
    lastButtonState = currentButtonState;
    
    // Small delay to debounce (prevent mechanical flicker)
    delay(50);
  }
}