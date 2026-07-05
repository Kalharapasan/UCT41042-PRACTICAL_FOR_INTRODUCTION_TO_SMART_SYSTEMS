#include <Arduino.h>

#define LDR_ANALOG_PIN  34
#define LDR_DIGITAL_PIN 13

void setup() {
  Serial.begin(115200);
  pinMode(LDR_DIGITAL_PIN, INPUT);
}

void loop() {
  int analogVal = analogRead(LDR_ANALOG_PIN);
  int digitalVal = digitalRead(LDR_DIGITAL_PIN);

  Serial.print("Analog Value: ");
  Serial.print(analogVal); // 0 (Bright) to 4095 (Dark) usually

  if (digitalVal == HIGH) {
    Serial.println(" | Status: DARK (Threshold Reached)");
  } else {
    Serial.println(" | Status: BRIGHT");
  }

  delay(500);
}