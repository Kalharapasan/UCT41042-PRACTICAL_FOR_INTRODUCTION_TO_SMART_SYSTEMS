#include <WiFi.h>
#include <WiFiManager.h>

WiFiManager wm;
#define LED_PIN 2   // ESP32 onboard LED (usually GPIO 2)
bool wasConnected = false;
bool ledState = false;
unsigned long previousMillis = 0;
const unsigned long DISCONNECTED_BLINK_MS = 1000;
const unsigned long CONNECTED_BLINK_MS = 200;

void blinkLed(unsigned long intervalMs) {
  if (millis() - previousMillis >= intervalMs) {
    previousMillis = millis();
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("\n\nESP32 WiFi Manager Starting...");
  WiFi.mode(WIFI_STA);
  // Keep loop running while the portal is active so LED can blink.
  wm.setConfigPortalBlocking(false);
  // Start WiFi Manager (AP portal will open if no WiFi saved)
  wm.autoConnect("ESP32-Config-Portal");
}

void loop() {
  wm.process();
  const bool isConnected = (WiFi.status() == WL_CONNECTED);

  if (!isConnected) {
    // Not connected -> slow blink
    blinkLed(DISCONNECTED_BLINK_MS);
    wasConnected = false;
  } else {
    // Connected -> fast blink
    blinkLed(CONNECTED_BLINK_MS);

    // Print IP only when connection is first established
    if (!wasConnected) {
      Serial.println("\nWi-Fi Connected Successfully!");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      wasConnected = true;
    }
  }
}