#define BLYNK_TEMPLATE_ID "TMPL6Sc1JV5Xb"
#define BLYNK_TEMPLATE_NAME "Intrusion Detection System"
#define BLYNK_AUTH_TOKEN "rXIb-8A1eqDXVzU7wYKu-1nfId4IGYfI"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <MFRC522.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define PIR_PIN 13
#define BUZZER 14
#define DOOR_RELAY 27

#define SS_PIN 5
#define RST_PIN 22

MFRC522 rfid(SS_PIN, RST_PIN);

bool intrusion = false;
unsigned long intrusionTime = 0;

void setup()
{
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(DOOR_RELAY, OUTPUT);

  SPI.begin();
  rfid.PCD_Init();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("System Ready");
}

void loop()
{
  Blynk.run();

  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH && intrusion == false)
  {
    intrusion = true;
    intrusionTime = millis();

    digitalWrite(BUZZER, HIGH);

    Serial.println("Intrusion Alert!");

    Blynk.virtualWrite(V0, 255);
  }

  if (intrusion == true)
  {
    if (rfid.PICC_IsNewCardPresent() &&
        rfid.PICC_ReadCardSerial())
    {
      String uid = "";

      for (byte i = 0; i < rfid.uid.size; i++)
      {
        uid += String(rfid.uid.uidByte[i], HEX);
      }

      Serial.print("Card UID: ");
      Serial.println(uid);

      // Replace with your RFID UID
      if (uid == "1234")
      {
        digitalWrite(DOOR_RELAY, HIGH);

        Blynk.virtualWrite(V1, "Access Granted");

        Serial.println("Access Granted");

        digitalWrite(BUZZER, LOW);

        intrusion = false;

        delay(5000);

        digitalWrite(DOOR_RELAY, LOW);
      }
    }

    if (millis() - intrusionTime > 10000)
    {
      Blynk.virtualWrite(V1, "Access Denied");

      Serial.println("Access Denied");

      digitalWrite(BUZZER, LOW);

      Blynk.virtualWrite(V0, 0);

      intrusion = false;
    }
  }
}