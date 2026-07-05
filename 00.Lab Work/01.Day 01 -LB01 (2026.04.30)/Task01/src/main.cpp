#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "Wokwi-GUST";
const char* password = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nConnecting to WiFi...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 50) {
    Serial.print(".");
    delay(200);  // give time between attempts
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected successfully!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi.");
  }
}

void loop() {
  // nothing needed here
}