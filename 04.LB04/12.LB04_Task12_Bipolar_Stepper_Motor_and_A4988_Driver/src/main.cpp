#include <Arduino.h>
#include <AccelStepper.h>

// 1. Define the pins
const int stepPin = 32;
const int dirPin = 19;

// 2. Define the motor interface type (1 means a driver like A4988)
#define motorInterfaceType 1

// 3. Create the stepper object
AccelStepper stepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  Serial.begin(115200);
  
  // 4. Set maximum speed and acceleration
  stepper.setMaxSpeed(1000);     // Steps per second
  stepper.setAcceleration(500);  // Steps per second squared
  
  Serial.println("Stepper Test Initialized...");
}

void loop() {
  // Move to a position (e.g., 200 steps is usually one full rotation)
  Serial.println("Moving to 400...");
  stepper.moveTo(400); 
  stepper.runToPosition(); // Blocking call: waits until finished
  
  delay(1000);
  
  // Move back to start
  Serial.println("Moving back to 0...");
  stepper.moveTo(0);
  stepper.runToPosition();
  
  delay(1000);
}