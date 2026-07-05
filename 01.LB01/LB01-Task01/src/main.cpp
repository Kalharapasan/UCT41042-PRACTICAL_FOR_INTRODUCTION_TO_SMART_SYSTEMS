#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "Wokwi-GUEST";  // FIXED
const char* password = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nConnecting to WiFi...");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); // optional but good practice
  WiFi.begin(ssid, password); // FIXED

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 50) {
    Serial.print(".");
    delay(500);  // IMPORTANT FIX
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected Successfully!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi");
  }
}

void loop() {
}