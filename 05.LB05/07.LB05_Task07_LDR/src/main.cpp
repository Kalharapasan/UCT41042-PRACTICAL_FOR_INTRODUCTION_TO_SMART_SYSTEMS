#include <Arduino.h>
const int ldrPin = 34;

void setup() {
  Serial.begin(115200);
  Serial.println("\nPhotoresistor (LDR) Light Sensor ");
}

void loop() {

  int lightValue = analogRead(ldrPin);

  Serial.print("Light Intensity: ");
  Serial.println(lightValue);

  delay(1000);
}