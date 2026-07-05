#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Try PAROLA_HW instead - often fixes display corruption
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 4

const int DATA_PIN  = 23; // DIN
const int CS_PIN    = 5;  // CS
const int CLK_PIN   = 18; // CLK

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nMAX7219 LED Matrix - PAROLA_HW Test");
  
  myDisplay.begin();
  
  // Reverse all devices to fix byte order
  for (uint8_t i = 0; i < MAX_DEVICES; i++) {
    myDisplay.setFont(i, NULL);
  }
  
  myDisplay.setIntensity(10);
  myDisplay.displayClear();
  delay(500);
  
  Serial.println("Display ready!");
  myDisplay.displayText("TEST", PA_CENTER, 50, 1000, PA_PRINT, PA_PRINT);
}

void loop() {
  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  }
}