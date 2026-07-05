#include <Arduino.h>

// ADC1_CH6 is GPIO 34
const int POT_PIN = 34; 

void setup() {
  Serial.begin(115200);
  
  // Configure ADC resolution (optional, default is 12-bit)
  analogReadResolution(12); 
  
  Serial.println("Potentiometer Read Initialized...");
}

void loop() {
  // Read the analog value (0 - 4095)
  int rawValue = analogRead(POT_PIN);
  
  // Convert the raw value to a voltage (0 - 3.3V)
  float voltage = (rawValue * 3.3) / 4095.0;

  // Print the results
  Serial.print("Raw Value: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.println("V");

  // Small delay for readability
  delay(250);
}