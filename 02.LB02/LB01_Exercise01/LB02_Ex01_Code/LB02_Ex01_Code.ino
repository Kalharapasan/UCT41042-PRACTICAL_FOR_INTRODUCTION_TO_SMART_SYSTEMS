#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

// ─── Configuration ────────────────────────────────────────────────
const char* WIFI_SSID     = "Kalara-WiFi";       // Replace with your Wi-Fi SSID
const char* WIFI_PASSWORD = "Pasa2001#";   // Replace with your Wi-Fi password

const char* FIRMWARE_VERSION = "1.0.0";
const char* HOSTNAME         = "ESP32-OTA-v1";

const int LED_PIN       = 2;      // Built-in LED / GPIO 2 via 220Ω resistor
const int BLINK_DELAY   = 1000;   // 1 second blink interval (V1 pattern)

void printBanner();
void connectToWiFi();
void setupOTA();
void blinkLED();

// ─── Setup ────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(LED_PIN, OUTPUT);

  printBanner();
  connectToWiFi();
  setupOTA();

  Serial.println("✅ System ready. Waiting for OTA updates...");
  Serial.println("─────────────────────────────────────────────");
}

// ─── Loop ─────────────────────────────────────────────────────────
void loop() {
  ArduinoOTA.handle();   // Must be called in every loop iteration
  blinkLED();            // V1: slow blink (1 second on/off)
}

// ─── Wi-Fi Connection ─────────────────────────────────────────────
void connectToWiFi() {
  Serial.printf("\n📡 Connecting to Wi-Fi: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;
    if (attempts > 40) {
      Serial.println("\n❌ Wi-Fi connection failed! Restarting...");
      ESP.restart();
    }
  }

  Serial.println("\n✅ Wi-Fi Connected!");
  Serial.printf("   SSID      : %s\n", WiFi.SSID().c_str());
  Serial.printf("   IP Address: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("   Signal    : %d dBm\n", WiFi.RSSI());
}

// ─── OTA Configuration ────────────────────────────────────────────
void setupOTA() {
  ArduinoOTA.setHostname(HOSTNAME);
  // Optional: set a password for OTA security
  // ArduinoOTA.setPassword("admin");

  // ── OTA Event: Start ──────────────────────────────────────────
  ArduinoOTA.onStart([]() {
    String type = (ArduinoOTA.getCommand() == U_FLASH) ? "Sketch" : "Filesystem";
    Serial.println("\n🚀 OTA Update Started!");
    Serial.printf("   Update type: %s\n", type.c_str());
    digitalWrite(LED_PIN, LOW); // LED off during update
  });

  // ── OTA Event: End ────────────────────────────────────────────
  ArduinoOTA.onEnd([]() {
    Serial.println("\n✅ OTA Update Complete! Rebooting...");
    Serial.println("─────────────────────────────────────────────");
  });

  // ── OTA Event: Progress ───────────────────────────────────────
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    unsigned int percent = (progress / (total / 100));
    Serial.printf("\r⬆️  Uploading: [");
    int bars = percent / 5;                        // 20 bars total
    for (int i = 0; i < 20; i++) {
      Serial.print(i < bars ? "█" : "░");
    }
    Serial.printf("] %3u%%", percent);
  });

  // ── OTA Event: Error ──────────────────────────────────────────
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("\n❌ OTA Error [%u]: ", error);
    switch (error) {
      case OTA_AUTH_ERROR:    Serial.println("Authentication Failed"); break;
      case OTA_BEGIN_ERROR:   Serial.println("Begin Failed");          break;
      case OTA_CONNECT_ERROR: Serial.println("Connect Failed");        break;
      case OTA_RECEIVE_ERROR: Serial.println("Receive Failed");        break;
      case OTA_END_ERROR:     Serial.println("End Failed");            break;
      default:                Serial.println("Unknown Error");         break;
    }
  });

  ArduinoOTA.begin();

  Serial.println("\n📥 OTA Service Started");
  Serial.printf("   Hostname  : %s\n", HOSTNAME);
  Serial.printf("   OTA Port  : 3232 (default)\n");
}

// ─── LED Blink — V1 Pattern (Slow: 1s on / 1s off) ───────────────
void blinkLED() {
  static unsigned long lastToggle = 0;
  static bool ledState = false;

  if (millis() - lastToggle >= BLINK_DELAY) {
    lastToggle = millis();
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}

// ─── Banner ───────────────────────────────────────────────────────
void printBanner() {
  Serial.println("─────────────────────────────────────────────");
  Serial.println("   ESP32 OTA Firmware Update Demo");
  Serial.printf("   Firmware Version : %s\n", FIRMWARE_VERSION);
  Serial.printf("   Compiled         : %s %s\n", __DATE__, __TIME__);
  Serial.println("─────────────────────────────────────────────");
}