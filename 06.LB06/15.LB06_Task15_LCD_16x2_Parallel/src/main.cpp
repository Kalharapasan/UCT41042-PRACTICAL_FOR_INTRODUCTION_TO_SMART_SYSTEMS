#include <Arduino.h>
#include <LiquidCrystal.h>
// Initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(RS, E, D4, D5, D6, D7)
const int rs = 19, en = 18, d4 = 17, d5 = 16, d6 = 4, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(115200);
  Serial.println("LCD 16x2 (Parallel) Test");
  // Print your name on the first row (Row 0)
  lcd.setCursor(0, 0); 
  lcd.print("Kalhara");
  
  // Move cursor to the second row (Row 1) and print roll number
  lcd.setCursor(0, 1);
  lcd.print("Roll No: 12345");
}

void loop() {
  // Nothing to repeat in the loop since the text is static
}