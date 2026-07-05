#include <Arduino.h>
// Define the pins
const int BUTTON_PIN = 5;  // GIOP5 connected to button
const int LED_PIN    = 2;  // Onboard LED

// variable for storing the pushbutton status 
int buttonState = 0;

void setup() {
  Serial.begin(115200);  
  
  // Initialize the pushbutton pin as an input with internal pull-up
  // This means the pin is HIGH by default and LOW when pressed
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read the state of the pushbutton value
  buttonState = digitalRead(BUTTON_PIN);

  // Check if the pushbutton is pressed.
  // If it is, the buttonState is LOW (because of INPUT_PULLUP)
  if (buttonState == LOW) {
    digitalWrite(LED_PIN, HIGH); // Turn LED on
    Serial.println("Button Pressed!");
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn LED off
  }
}