#include <Arduino.h>
#include <ESP32Servo.h>

// 1. Create a servo object
Servo myServo;

// 2. Define the GPIO pin
const int servoPin = 18;

void setup() {
  Serial.begin(115200);
  
  // 3. Attach the servo to the pin
  // Standard servos use a pulse width of 500us to 2400us
  myServo.attach(servoPin, 500, 2400); 
}

void loop() {
  // Move from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos += 1) {
    myServo.write(pos);
    delay(15); // Wait for the servo to reach the position
  }

  delay(1000);

  // Move from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos -= 1) {
    myServo.write(pos);
    delay(15);
  }

  delay(1000);
}