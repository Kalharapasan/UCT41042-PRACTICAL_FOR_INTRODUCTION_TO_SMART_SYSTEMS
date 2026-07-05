#include <Arduino.h>

// Define pins
#define CLK_PIN 18
#define DT_PIN  19
#define SW_PIN  5

int counter = 0;
int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;

void setup() {
  Serial.begin(115200);

  // Setup pins
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK_PIN);
}

void loop() {
  // 1. Read Rotation
  currentStateCLK = digitalRead(CLK_PIN);

  // If CLK has changed, a pulse occurred
  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {
    // If the DT state is different from the CLK state, 
    // the encoder is rotating CCW
    if (digitalRead(DT_PIN) != currentStateCLK) {
      counter--;
    } else {
      // Encoder is rotating CW
      counter++;
    }
    Serial.print("Direction: ");
    Serial.print(digitalRead(DT_PIN) != currentStateCLK ? "CCW" : "CW");
    Serial.print(" | Count: ");
    Serial.println(counter);
  }
  lastStateCLK = currentStateCLK;

  // 2. Read Button Press
  int btnState = digitalRead(SW_PIN);
  if (btnState == LOW) {
    // Basic debouncing
    if (millis() - lastButtonPress > 50) {
      Serial.println("Button Pressed!");
    }
    lastButtonPress = millis();
  }
  
  // No delay here! We need high-speed polling for the encoder.
}