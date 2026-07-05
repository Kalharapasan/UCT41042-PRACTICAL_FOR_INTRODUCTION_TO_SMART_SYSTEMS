#include <Arduino.h>

#define THERMISTOR_PIN 34
#define SERIES_RESISTOR 10000    // 10k resistor
#define NOMINAL_RESISTANCE 10000 // resistance at 25 degrees C
#define NOMINAL_TEMPERATURE 25   // temp for nominal resistance
#define B_COEFFICIENT 3950       // The beta coefficient (usually 3435 or 3950)
#define ADC_MAX 4095             // ESP32 ADC resolution

void setup() {
  Serial.begin(115200);
}

void loop() {
  int adcValue = analogRead(THERMISTOR_PIN);
  
  // Calculate resistance
  float resistance;
  resistance = SERIES_RESISTOR / (ADC_MAX / (float)adcValue - 1);

  // Steinhart-Hart Equation
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;     // (R/Ro)
  steinhart = log(steinhart);                      // ln(R/Ro)
  steinhart /= B_COEFFICIENT;                      // 1/B * ln(R/Ro)
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                     // Invert
  steinhart -= 273.15;                             // convert to C

  Serial.print("Temperature: ");
  Serial.print(steinhart);
  Serial.println(" °C");

  delay(1000);
}