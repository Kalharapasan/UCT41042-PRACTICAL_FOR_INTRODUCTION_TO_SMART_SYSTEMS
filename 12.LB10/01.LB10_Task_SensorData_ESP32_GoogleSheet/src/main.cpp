#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

String scriptURL = "https://script.google.com/macros/s/AKfycbwHEwHLWSVRaAjUB69jsKUGvT_aW2AcFX_MicxC9c9yrRh5XBHwBtY4Y-JMR38Uok4r/exec";

// DS18B20 Data Pin
#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

void setup()
{
  Serial.begin(115200);

  sensors.begin();

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
}

void loop()
{
  sensors.requestTemperatures();

  float temp = sensors.getTempCByIndex(0);

  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.println(" °C");

  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;

    String url = scriptURL + "?temp=" + String(temp);

    http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
    http.begin(client, url);

    int httpCode = http.GET();

    Serial.print("HTTP Response : ");
    Serial.println(httpCode);

    http.end();
  }

  delay(2000);
}