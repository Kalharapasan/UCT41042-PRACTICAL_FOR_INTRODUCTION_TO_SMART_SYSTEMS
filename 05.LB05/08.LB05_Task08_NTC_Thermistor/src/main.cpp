#include <Arduino.h>
const int thermistorPin = 34;

void setup() {
  Serial.begin(115200);
  Serial.println("\nAnalog Temperature Sensor (NTC Thermistor) ");
}

void loop() {

  int value = analogRead(thermistorPin);

  // Convert analog value to temperature
  float temperature = map(value, 0, 1023, -20, 100);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000);
}