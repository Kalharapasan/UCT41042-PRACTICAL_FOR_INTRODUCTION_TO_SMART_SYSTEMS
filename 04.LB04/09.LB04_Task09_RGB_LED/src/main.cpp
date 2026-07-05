#include <Arduino.h>

// Define Pins
const int redPin = 5;
const int greenPin = 18;
const int bluePin = 19;

// PWM Settings
const int freq = 5000;
const int resolution = 8; // 8-bit resolution (0-255)

// PWM Channels
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const bool commonAnode = false;

// Forward declaration
void setColor(int redValue, int greenValue, int blueValue);

void setup() {
  Serial.begin(115200);
  
  // Set pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Configure LED PWM functionalites
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);
  
  ledcAttachPin(redPin, redChannel);
  ledcAttachPin(greenPin, greenChannel);
  ledcAttachPin(bluePin, blueChannel);

  // Startup check: LED should turn white briefly.
  setColor(255, 255, 255);
  delay(1000);
  setColor(0, 0, 0);
  
  Serial.println("RGB LED initialized!");
}

void loop() {
  // Cycle through some colors
  Serial.println("RED");
  setColor(255, 0, 0);   // Red
  delay(1000);
  
  Serial.println("GREEN");
  setColor(0, 255, 0);   // Green
  delay(1000);
  
  Serial.println("BLUE");
  setColor(0, 0, 255);   // Blue
  delay(1000);
  
  Serial.println("YELLOW");
  setColor(255, 255, 0); // Yellow
  delay(1000);
  
  Serial.println("PURPLE");
  setColor(255, 0, 255); // Purple
  delay(1000);
  
  Serial.println("CYAN");
  setColor(0, 255, 255); // Cyan
  delay(1000);
  
  Serial.println("WHITE");
  setColor(255, 255, 255); // White
  delay(1000);
  
  Serial.println("OFF");
  setColor(0, 0, 0);     // Off
  delay(1000);
}

// Function to set the RGB color
void setColor(int redValue, int greenValue, int blueValue) {
  if (commonAnode) {
    redValue = 255 - redValue;
    greenValue = 255 - greenValue;
    blueValue = 255 - blueValue;
  }

  ledcWrite(redChannel, redValue);
  ledcWrite(greenChannel, greenValue);
  ledcWrite(blueChannel, blueValue);
}