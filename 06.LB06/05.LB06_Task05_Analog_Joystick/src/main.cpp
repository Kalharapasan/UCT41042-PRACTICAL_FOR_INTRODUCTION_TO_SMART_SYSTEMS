#include <Arduino.h>
// Define the joystick pins
const int X_PIN = 34;  // Analog pin for X-axis
const int Y_PIN = 35;  // Analog pin for Y-axis
const int SW_PIN = 5; // Digital pin for the push-button

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  Serial.println("Analog Joystick Test");
  // Configure axis pins as inputs
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  
  // Configure the switch pin with internal pull-up resistor
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {
  // Read the analog values (0 to 4095)
  int xValue = analogRead(X_PIN);
  int yValue = analogRead(Y_PIN);
  
  // Read the digital button state (LOW = Pressed, HIGH = Released)
  int buttonState = digitalRead(SW_PIN);
  
  // Print the data to the Serial Monitor
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Button: ");
  
  if (buttonState == LOW) {
    Serial.println("PRESSED");
  } else {
    Serial.println("RELEASED");
  }
  
  // Wait 150 milliseconds so the text is readable
  delay(150);
}