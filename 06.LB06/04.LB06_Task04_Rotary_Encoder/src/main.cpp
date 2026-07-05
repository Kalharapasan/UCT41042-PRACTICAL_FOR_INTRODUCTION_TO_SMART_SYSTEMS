#include <Arduino.h>
// Define the encoder pins
const int CLK_PIN = 18; // Clock pin
const int DT_PIN = 19;  // Data pin

int counter = 0;       // Stores the step count
int lastClkState;      // Stores the previous state of the CLK pin

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  Serial.println("Rotary Encoder (KY-040) Test");
  // Set encoder pins as inputs
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  
  // Read the initial state of the CLK pin
  lastClkState = digitalRead(CLK_PIN);
}

void loop() {
  // Read the current state of the CLK pin
  int currentClkState = digitalRead(CLK_PIN);
  
  // Check if the knob has been turned (CLK state changed)
  if (currentClkState != lastClkState) {
    
    // If the CLK state changed, we check the DT state to find the direction
    // If CLK state is different from DT state, it's rotating Clockwise
    if (digitalRead(DT_PIN) != currentClkState) {
      counter++;
      Serial.print("Direction: Clockwise | ");
    } 
    // Otherwise, it's rotating Counter-Clockwise
    else {
      counter--;
      Serial.print("Direction: Counter-Clockwise | ");
    }
    
    // Print the current step count
    Serial.print("Position: ");
    Serial.println(counter);
  }
  
  // Save the current CLK state for the next loop
  lastClkState = currentClkState;
}