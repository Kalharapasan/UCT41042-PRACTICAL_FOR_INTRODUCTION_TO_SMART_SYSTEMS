#include <Arduino.h>
#include "HX711.h"

#define DT 16
#define SCK 17

HX711 scale;

void setup()
{
  Serial.begin(115200);
  Serial.println("\nHX711 Load Cell Amplifier ");
  scale.begin(DT, SCK);

  // Tare (zero the scale at startup)
  Serial.println("Taring... remove any weight");
  delay(2000);
  scale.tare();

  Serial.println("Ready");
}

void loop()
{

  // Set calibration factor (you MUST adjust this for your load cell)
  float calibration_factor = -7050;

  scale.set_scale(calibration_factor);

  float weight = scale.get_units(10); // average of 10 readings

  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" g");

  delay(500);
}