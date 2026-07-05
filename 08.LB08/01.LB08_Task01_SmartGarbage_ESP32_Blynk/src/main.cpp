#define BLYNK_TEMPLATE_ID "TMPL68tp3Uqbx"
#define BLYNK_TEMPLATE_NAME "LB08 Task01"
#define BLYNK_AUTH_TOKEN "b-eGWP8gtiJazDjQcrCp76L1V6DfQGWF"

#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <HX711.h>
#include <LiquidCrystal_I2C.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define DT_PIN 18
#define SCK_PIN 19

#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27

HX711 scale;
LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

void sendData()
{
  // Example weight for simulation
  float weight = scale.get_units();

  String status = "";

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Weight:");
  lcd.print(weight);
  lcd.print("kg");

  // LOW LEVEL
  if(weight < 2)
  {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);

    status = "LOW";
  }

  // MEDIUM LEVEL
  else if(weight >= 2 && weight <= 5)
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    status = "MEDIUM";
  }

  // FULL LEVEL
  else if(weight > 5 && weight <= 7)
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    status = "FULL";
  }

  // OVERWEIGHT
  else
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);

    digitalWrite(RED_LED, HIGH);
    delay(300);
    digitalWrite(RED_LED, LOW);
    delay(300);

    status = "OVERWEIGHT";
  }

  lcd.setCursor(0,1);
  lcd.print(status);

  Blynk.virtualWrite(V0, weight);
  Blynk.virtualWrite(V1, status);
}

void setup()
{
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  lcd.init();
  lcd.backlight();

  scale.begin(DT_PIN, SCK_PIN);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendData);
}

void loop()
{
  Blynk.run();
  timer.run();
}