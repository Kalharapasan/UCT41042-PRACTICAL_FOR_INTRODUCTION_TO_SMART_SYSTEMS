#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define SUPABASE_URL "https://mnyjdwffbiqwiznupecp.supabase.co"
#define SUPABASE_API_KEY "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Im1ueWpkd2ZmYmlxd2l6bnVwZWNwIiwicm9sZSI6ImFub24iLCJpYXQiOjE3ODIyODE3MDQsImV4cCI6MjA5Nzg1NzcwNH0.ioUkA_sK996QbTqYOcRmir0Pvr_kxnHpHDoh9BwJd20"

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LDR_PIN 34
#define RED_PIN 19
#define GREEN_PIN 18
#define BLUE_PIN 17
#define STREET_LED_PIN 5

unsigned long lastSend = 0;
const unsigned long interval = 5000;

bool blinkState = false;

void connectWiFi();
void setRGB(bool r, bool g, bool b);
void sendDataToSupabase(int intentensity, String status, String ledState);

void setup()
{
  Serial.begin(115200);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(STREET_LED_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.print("SMART STREET");
  lcd.setCursor(0, 1);
  lcd.print("LIGHT SYSTEM");
  delay(2000);
  lcd.clear();

  connectWiFi();
}

void loop()
{
  int ldrValue = analogRead(LDR_PIN);

  int intensity = map(ldrValue, 0, 4095, 0, 100);
  intensity = constrain(intensity, 0, 100);

  String status = "OFF";
  String ledState = "UNKNOWN";

  if (intensity > 70)
  {
    setRGB(false, true, false);
    digitalWrite(STREET_LED_PIN, LOW);
    ledState = "Green";
  }
  else if (intensity >= 30)
  {
    setRGB(false, false, true);
    digitalWrite(STREET_LED_PIN, LOW);
    ledState = "BLUE";
  }
  else if (intensity >= 15)
  {
    setRGB(true, false, false);
    digitalWrite(STREET_LED_PIN, HIGH);
    ledState = "RED";
    status = "ON";
  }
  else
  {
    blinkState =! blinkState;
    setRGB(blinkState, false, false);
    digitalWrite(STREET_LED_PIN, HIGH);
    status = "ON";
    ledState = "RED_BLINK";
  }

  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(intensity);
  lcd.print("%  ");

  lcd.setCursor(0, 1);
  lcd.print("Street: ");
  lcd.print(status);
  lcd.print(" ");

  if (millis() - lastSend >= interval)
  {
    lastSend = millis();
    sendDataToSupabase(intensity, status, ledState);
  }
}

void connectWiFi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWIFI CONNECTED");
}

void setRGB(bool r, bool g, bool b)
{
  digitalWrite(RED_PIN, r);
  digitalWrite(GREEN_PIN, g);
  digitalWrite(BLUE_PIN, b);
}

void sendDataToSupabase(int intensity, String status, String ledState)
{
  if (WiFi.status() != WL_CONNECTED)
    return;

  HTTPClient http;
  String url = String(SUPABASE_URL) + "/rest/v1/street_light_logs";

  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("apikey", SUPABASE_API_KEY);
  http.addHeader("Authorization", "Bearer " + String(SUPABASE_API_KEY));
  http.addHeader("Prefer", "return=minimal");

  JsonDocument doc;
  doc["intensity"] = intensity;
  doc["status"] = status;
  doc["ledState"] = ledState;

  String payload;
  serializeJson(doc, payload);

  http.setTimeout(15000);
  int httpResponseCode = http.POST(payload);

  Serial.print("Supabase Response: ");
  Serial.println(httpResponseCode);

  http.end();
}
