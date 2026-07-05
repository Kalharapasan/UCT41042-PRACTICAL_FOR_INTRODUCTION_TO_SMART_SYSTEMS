#include <Arduino.h>
#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(19, 18, 17, 16, 4, 2);

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.print("ESP32 Test...");
  
  delay(2000);
  lcd.clear();
}

void loop() {
  // Set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("System: Online");

  // Set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("Uptime: ");
  lcd.print(millis() / 1000);
  lcd.print("s");
  
  delay(1000);
}