#include <Arduino.h>
#include <WiFi.h>
#include <ESPSupabase.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

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

Supabase supabase;

unsigned long lastSend = 0;
const unsigned long interval = 5000;

bool blinkState = false;

void connectWiFi();
void setRGB(bool r, bool g, bool b);
void syncTime();
int sendToSupabase(String jsonStr);

void setup()
{
  Serial.begin(115200);
  Serial.println("\n=== SMART STREET LIGHT SYSTEM STARTED ===");

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

  // Sync time before any HTTPS/TLS calls
  syncTime();

  // Initialize Supabase
  supabase.begin(SUPABASE_URL, SUPABASE_API_KEY);
}

void loop()
{
  int ldrValue = analogRead(LDR_PIN);
  int intensity = map(ldrValue, 0, 4095, 0, 100);
  intensity = constrain(intensity, 0, 100);

  String status = "OFF";
  String ledState = "UNKNOWN";

  if (intensity > 70) {
    setRGB(false, true, false);
    digitalWrite(STREET_LED_PIN, LOW);
    ledState = "Green";
  } 
  else if (intensity >= 30) {
    setRGB(false, false, true);
    digitalWrite(STREET_LED_PIN, LOW);
    ledState = "BLUE";
  } 
  else if (intensity >= 15) {
    setRGB(true, false, false);
    digitalWrite(STREET_LED_PIN, HIGH);
    ledState = "RED";
    status = "ON";
  } 
  else {
    blinkState = !blinkState;
    setRGB(blinkState, false, false);
    digitalWrite(STREET_LED_PIN, HIGH);
    status = "ON";
    ledState = "RED_BLINK";
  }

  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(intensity);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  lcd.print("Street: ");
  lcd.print(status);
  lcd.print("   ");

  if (millis() - lastSend >= interval) {
    lastSend = millis();

    // Build JSON payload
    JsonDocument doc;
    doc["intensity"] = intensity;
    doc["status"] = status;
    doc["ledState"] = ledState;

    String jsonStr;
    serializeJson(doc, jsonStr);

    int responseCode = sendToSupabase(jsonStr);
    Serial.print("Supabase Response Code: ");
    Serial.println(responseCode);
  }
}

int sendToSupabase(String jsonStr) {
  int responseCode = -1;
  const int maxAttempts = 3;

  for (int attempt = 1; attempt <= maxAttempts; attempt++) {
    responseCode = supabase.insert("street_light_logs", jsonStr, false);

    if (responseCode > 0) {
      // (HTTP 2xx/etc) — stop retrying
      break;
    }

    Serial.print("Insert attempt ");
    Serial.print(attempt);
    Serial.print(" failed (code ");
    Serial.print(responseCode);
    Serial.println("), retrying...");
    delay(1000);
  }

  return responseCode;
}

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi CONNECTED!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void syncTime() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Syncing time");
  time_t now = time(nullptr);
  while (now < 1700000000) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("\nTime synced: " + String(now));
}

void setRGB(bool r, bool g, bool b) {
  digitalWrite(RED_PIN, r);
  digitalWrite(GREEN_PIN, g);
  digitalWrite(BLUE_PIN, b);
}