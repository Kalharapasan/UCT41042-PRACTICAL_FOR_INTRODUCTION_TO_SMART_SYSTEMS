#include <Arduino.h>
#define PIR_PIN 5

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  Serial.println("PIR Sensor Warm-up (takes ~30-60 seconds)...");
  
  // PIR sensors need a warm-up period to calibrate to the room
  delay(30000); 
  Serial.println("PIR Sensor Active!");
}

void loop() {
  int motionState = digitalRead(PIR_PIN);

  if (motionState == HIGH) {
    Serial.println("--- MOTION DETECTED! ---");
  } else {
    Serial.println("No motion.");
  }

  delay(500); // Small delay to avoid flooding the Serial Monitor
}