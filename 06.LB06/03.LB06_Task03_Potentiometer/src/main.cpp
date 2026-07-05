#include <Arduino.h>
// Define the analog pin connected to the potentiometer middle pin
const int POT_PIN = 34; // GPIO 34 is an analog input pin (ADC1_CH6)

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  Serial.println("Potentiometer Test");
  // Analog pins do not strictly require pinMode(), 
  // but it's good practice to set it as INPUT.
  pinMode(POT_PIN, INPUT);
}

void loop() {
  // Read the analog value (0 to 4095)
  int potValue = analogRead(POT_PIN);
  
  // Print the value to the Serial Monitor
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
  
  // Wait 100 milliseconds so the monitor doesn't scroll too fast
  delay(100);
}