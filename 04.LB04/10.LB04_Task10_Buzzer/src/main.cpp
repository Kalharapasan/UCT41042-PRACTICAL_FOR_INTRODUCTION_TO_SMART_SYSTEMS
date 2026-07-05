#include <Arduino.h>
// Define the buzzer pin
const int buzzerPin = 5;

void playMelody() {
  int notes[] = {262, 294, 330, 349}; // C4, D4, E4, F4
  for (int i = 0; i < 4; i++) {
    tone(buzzerPin, notes[i]);
    delay(200);
    noTone(buzzerPin);
    delay(50);
  }
}

void setup() {
  // No special setup needed for tone()
  Serial.begin(115200);
}

void loop() {
  Serial.println("Buzzer: ON (1000Hz)");
  
  // Play a 1000Hz tone
  tone(buzzerPin, 1000); 
  delay(500); 

  Serial.println("Buzzer: OFF");
  
  // Stop the tone
  noTone(buzzerPin); 
  delay(1000); 
  
  // Simple melody test (Passive Buzzer only)
  playMelody();
}

