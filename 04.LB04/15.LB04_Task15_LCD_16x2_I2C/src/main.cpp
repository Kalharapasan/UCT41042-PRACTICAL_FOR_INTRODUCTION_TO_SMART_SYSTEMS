#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 1. Set the LCD address to 0x27 for a 16 chars and 2 line display
// If 0x27 doesn't work, try 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // 2. Initialize the LCD
  lcd.init();
  
  // Turn on the blacklight
  lcd.backlight();
  
  // Print a message
  lcd.setCursor(0, 0);
  lcd.print("I2C LCD Ready!");
  
  lcd.setCursor(0, 1);
  lcd.print("ESP32 Booting...");
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Scanning...");
  
  // Example: Displaying a value
  int sensorValue = analogRead(34); 
  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.print(sensorValue);
  lcd.print("    "); // Clear trailing digits
  
  delay(500);
}