#include <Arduino.h>
const int trigPin = 5;
const int echoPin = 18;

void setup()
{
  Serial.begin(9600);
  Serial.println("\nHC-SR04 (Ultrasonic Distance Sensor) ");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{

  // Send pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  int distance = duration * 0.034 / 2;

  // Print distance
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);
}