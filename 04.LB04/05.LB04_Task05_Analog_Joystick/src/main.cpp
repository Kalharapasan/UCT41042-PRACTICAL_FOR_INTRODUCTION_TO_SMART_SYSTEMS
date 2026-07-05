#include <Arduino.h>

// Define pins
const int PIN_X = 34; 
const int PIN_Y = 35;
const int PIN_SW = 5;

void setup() {
  Serial.begin(115200);
  
  // Joystick button needs a pull-up
  pinMode(PIN_SW, INPUT_PULLUP);
  
  // Set ADC resolution to 12-bit (0-4095)
  analogReadResolution(12);
}

void loop() {
  // Read analog values
  int xValue = analogRead(PIN_X);
  int yValue = analogRead(PIN_Y);
  
  // Read button (inverted logic because of INPUT_PULLUP)
  int swValue = digitalRead(PIN_SW);

  // Print raw values
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Button: ");
  Serial.println(swValue == LOW ? "PRESSED" : "RELEASED");

  // Logic Example: Simple Direction detection
  if (xValue < 1500) Serial.println("Moving LEFT");
  else if (xValue > 2500) Serial.println("Moving RIGHT");
  
  if (yValue < 1500) Serial.println("Moving UP");
  else if (yValue > 2500) Serial.println("Moving DOWN");

  delay(200); 
}