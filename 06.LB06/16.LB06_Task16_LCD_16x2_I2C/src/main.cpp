#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// (If 0x27 doesn't work, your module might use 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Serial.println("LCD 16x2 (I2C) Test");
  // Initialize the LCD connected via I2C
  lcd.init();
  // Turn on the blacklight
  lcd.backlight();
  // Print a static header on the first row
  lcd.setCursor(0, 0);
  lcd.print("Sensor Monitor");
}

void loop() {
  // Simulate reading a sensor value (e.g., generating a value between 0 and 100)
  int mockSensorValue = analogRead(34) / 41; // Scaled down for example display
  
  // Move cursor to the second row (Column 0, Row 1)
  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  
  // Print the dynamic sensor value
  lcd.print(mockSensorValue);
  
  // Clear any leftover trailing digits if the value drops (e.g., from 100 to 9)
  lcd.print("    "); 
  
  // Update every 500 milliseconds
  delay(500);
}