#include <Arduino.h>
#include <Keypad.h>

// Define the number of rows and columns on your keypad
const byte ROWS = 4; 
const byte COLS = 4; 

// Define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect the ESP32 GPIO pins to the row pins of the keypad
byte rowPins[ROWS] = {19, 18, 5, 17}; 

// Connect the ESP32 GPIO pins to the column pins of the keypad
byte colPins[COLS] = {16, 4, 2, 15}; 

// Initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  Serial.println("Keypad  Test");
}
  
void loop() {
  // Check if a key is pressed
  char customKey = customKeypad.getKey();
  
  // If a key was pressed, print it to the Serial Monitor
  if (customKey) {
    Serial.print("Key Pressed: ");
    Serial.println(customKey);
  }
}