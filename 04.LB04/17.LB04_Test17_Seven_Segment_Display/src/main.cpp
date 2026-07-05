#include <Arduino.h>
// Define pins for segments a, b, c, d, e, f, g
const int segments[7] = {13, 12, 14, 27, 26, 25, 33};

// Binary map for numbers 0-9 (a, b, c, d, e, f, g)
const byte digitMap[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void displayDigit(int num);

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i <= 9; i++) {
    displayDigit(i);
    delay(1000);
  }
}

void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    // Check the bit for each segment
    int bit = bitRead(digitMap[num], i);
    digitalWrite(segments[i], bit ? LOW : HIGH); 
  }
}