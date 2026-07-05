#include <Arduino.h>
const int trigPin =5;
const int echoPin =18;

void setup() {
  Serial.begin(115200);
  Serial.println("HC-SR04 (Ultrasonic Distance Sensor)");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin,HIGH);

  float distance = duration * 0.0343 /2;

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000);

}
