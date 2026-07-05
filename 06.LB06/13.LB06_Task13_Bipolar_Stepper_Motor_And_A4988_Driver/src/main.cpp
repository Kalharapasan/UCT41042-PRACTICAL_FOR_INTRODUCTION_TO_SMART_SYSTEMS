#include <Arduino.h>
const int STEP_PIN = 32; // GPIO 32 sends the step pulses
const int DIR_PIN  = 19; // GPIO 19 sets the rotation direction

// Define the steps per revolution for your motor 
// (Standard NEMA 17 motors usually have 200 steps per full revolution)
const int STEPS_PER_REV = 200; 

void setup() {
  // Configure control pins as outputs
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Bipolar Stepper Motor + A4988 Driver  Test");
}

void loop() {
  // 1. Rotate Clockwise
  digitalWrite(DIR_PIN, HIGH); // Set direction to HIGH (Clockwise)
  
  // Spin one full revolution
  for (int i = 0; i < STEPS_PER_REV; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000); // Speeds up or slows down the pulse rate
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);
  }
  
  delay(1000); // Pause for 1 second

  // 2. Rotate Counter-Clockwise
  digitalWrite(DIR_PIN, LOW); // Set direction to LOW (Counter-Clockwise)
  
  // Spin one full revolution back
  for (int i = 0; i < STEPS_PER_REV; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);
  }
  
  delay(1000); // Pause for 1 second
}