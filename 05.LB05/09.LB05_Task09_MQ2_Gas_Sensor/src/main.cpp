#include <Arduino.h>
const int mq2Pin = 34;

void setup() {
  Serial.begin(115200);
  Serial.println("MQ2_Gas_Sensor ");
}

void loop() {

  int gasValue = analogRead(mq2Pin);

  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  delay(500);
}