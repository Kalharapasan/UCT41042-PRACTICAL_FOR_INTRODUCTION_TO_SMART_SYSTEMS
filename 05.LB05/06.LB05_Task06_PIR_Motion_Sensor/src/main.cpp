#include <Arduino.h>
const int pirPin = 5;

void setup()
{
  Serial.begin(115200);
  Serial.println("\nPIR Motion Sensor (Passive Infrared) ");
  pinMode(pirPin, INPUT);
}

void loop()
{

  int motion = digitalRead(pirPin);

  if (motion == HIGH)
  {
    Serial.println("Motion Detected");
  }
  else
  {
    Serial.println("No Motion");
  }

  delay(1000);
}