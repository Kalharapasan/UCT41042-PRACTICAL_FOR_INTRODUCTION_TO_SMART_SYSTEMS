#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// 1. Define Hardware Type and Pins
// Use the Parola hardware preset for the Wokwi MAX7219 matrix part
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 4 // Set this to the number of 8x8 matrices you have
#define CS_PIN 5

// 2. Initialize the Parola object
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  // 3. Initialize the display
  myDisplay.begin();

  // Set intensity (0-15)
  myDisplay.setIntensity(5);
  
  // Clear the display
  myDisplay.displayClear();

  // Configure the scrolling message once in setup
  myDisplay.displayText("ESP32 IoT TEST", PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  myDisplay.displayReset();
}

void loop() {
  // 4. Keep the configured animation running
  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  }
}