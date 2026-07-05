#include <Arduino.h>
#include <ESP32Servo.h>

// Create a servo object
Servo myServo;

// Define the GPIO pin connected to the servo signal wire
const int SERVO_PIN = 18; 

void setup() {
  // Allow allocation of all timers for servo PWM control
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  Serial.begin(115200);
  Serial.println("Servo Motor");
  
  // Set the PWM frequency for a standard servo (50Hz)
  myServo.setPeriodHertz(50);    
  
  // Attach the servo object to the pin
  myServo.attach(SERVO_PIN, 500, 2400); // Pulse width range in microseconds
}

void loop() {
  // Move to 0 degrees
  myServo.write(0);
  delay(1000); // Wait 1 second for the motor to reach the position

  // Move to 90 degrees
  myServo.write(90);
  delay(1000);

  // Move to 180 degrees
  myServo.write(180);
  delay(1000);
}