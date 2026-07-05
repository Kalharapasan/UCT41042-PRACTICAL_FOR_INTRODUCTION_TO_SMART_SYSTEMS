#include <Arduino.h>
// Define the GPIO pin connected to the buzzer
const int BUZZER_PIN = 5; // You can use GPIO 12, 13, 14, etc.

void setup() {
  // Configure the buzzer pin as an OUTPUT
  Serial.begin(115200);
  Serial.println("Buzzer Test");
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // --- Generate the Beep Sound ---
  // tone(pin, frequency, duration) 
  // 2000Hz frequency creates a standard crisp beep
  tone(BUZZER_PIN, 2000, 200); 
  
  // Wait for 1 second before the next beep
  // Note: tone() doesn't pause the code, so we use delay()
  delay(1000); 
}