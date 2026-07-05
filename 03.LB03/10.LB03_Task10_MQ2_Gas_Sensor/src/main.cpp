#include <Arduino.h>

#define MQ2_ANALOG_PIN 34
#define MQ2_DIGITAL_PIN 13

void setup() {
  Serial.begin(115200);
  pinMode(MQ2_DIGITAL_PIN, INPUT);
  
  Serial.println("MQ2 Sensor Warming Up...");
  // It takes a moment for the internal heater to stabilize
  delay(20000); 
}

void loop() {
  int analogValue = analogRead(MQ2_ANALOG_PIN);
  int digitalValue = digitalRead(MQ2_DIGITAL_PIN);

  Serial.print("Gas Level (Analog): ");
  Serial.print(analogValue);

  // Lower values usually mean clean air; higher values mean gas detected
  if (digitalValue == LOW) { // MQ series often use Active-Low for Digital Out
    Serial.println(" | [ ALERT: Gas/Smoke Detected! ]");
  } else {
    Serial.println(" | [ Air Status: Normal ]");
  }

  delay(1000);
}