 #include <Arduino.h>

// Define the GPIO pins for each color channel
const int RED_PIN   = 5;
const int GREEN_PIN = 18;
const int BLUE_PIN  = 19;

void setColor(int redState, int greenState, int blueState);

void setup() {
  // Set all color pins as OUTPUT
  Serial.begin(115200);
  Serial.println("RGB LED Test");
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // 1. Display RED
  setColor(HIGH, LOW, LOW);
  delay(1000);

  // 2. Display GREEN
  setColor(LOW, HIGH, LOW);
  delay(1000);

  // 3. Display BLUE
  setColor(LOW, LOW, HIGH);
  delay(1000);

  // 4. Display WHITE (Red + Green + Blue mixed together)
  setColor(HIGH, HIGH, HIGH);
  delay(1000);
}

// Helper function to easily set the pin states
void setColor(int redState, int greenState, int blueState) {
  digitalWrite(RED_PIN, redState);
  digitalWrite(GREEN_PIN, greenState);
  digitalWrite(BLUE_PIN, blueState);
}