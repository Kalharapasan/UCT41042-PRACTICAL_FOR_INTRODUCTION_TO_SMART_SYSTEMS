#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 17;

HX711 scale;

void setup()
{
  Serial.begin(115200);
  Serial.println("HX711 Demo");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print a raw reading from the ADC

  scale.set_scale(); // Reset the scale to 1
  scale.tare();      // Reset the scale to 0

  Serial.println("After setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print a raw reading from the ADC

  Serial.println("Readings:");
}

void loop()
{
  if (scale.is_ready())
  {
    long reading = scale.read();
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  }
  else
  {
    Serial.println("HX711 not found.");
  }

  delay(1000);
}