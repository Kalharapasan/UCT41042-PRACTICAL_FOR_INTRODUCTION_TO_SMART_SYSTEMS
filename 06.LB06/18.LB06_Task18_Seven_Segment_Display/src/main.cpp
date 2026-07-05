#include <Arduino.h>
// Define segment pins according to your image table
const int segA = 13;
const int segB = 12;
const int segC = 14;
const int segD = 27;
const int segE = 26;
const int segF = 25;
const int segG = 33;
const int segDP = 32; // Decimal Point pin

// Group all segment pins into an array for easy initialization
const int segments[] = {segA, segB, segC, segD, segE, segF, segG, segDP};

// Byte patterns for digits 0-9 (Common Cathode: 1 = ON, 0 = OFF)
// Bits correspond to: {A, B, C, D, E, F, G}
const byte digitPatterns[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

// Function prototype
void displayDigit(int num);

void setup() {
  Serial.begin(115200);
  Serial.println("Seven Segment Display Test");
  // Set all segment pins as OUTPUT
  for (int i = 0; i < 8; i++) {
    pinMode(segments[i], OUTPUT);
    digitalWrite(segments[i], LOW); // Turn all segments OFF initially
  }
}

void loop() {
  // Loop through digits 0 to 9
  for (int digit = 0; digit < 10; digit++) {
    displayDigit(digit);
    delay(1000); // Wait 1 second before displaying the next number
  }
}

// Helper function to update the physical pins with a digit pattern
void displayDigit(int num) {
  for (int seg = 0; seg < 7; seg++) {
    digitalWrite(segments[seg], digitPatterns[num][seg]);
  }
  // Keep the decimal point (DP) turned off
  digitalWrite(segDP, LOW); 
}