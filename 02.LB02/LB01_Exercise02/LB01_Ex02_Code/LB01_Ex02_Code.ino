#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

// ─── Configuration ────────────────────────────────────────────────
const char* WIFI_SSID     = "Kalara-WiFi";  // Replace with your Wi-Fi SSID
const char* WIFI_PASSWORD = "Pasa2001#";   // Replace with your Wi-Fi password

const char* FIRMWARE_VERSION = "2.0.0";        // ← Version bumped
const char* HOSTNAME         = "ESP32-OTA-v2"; // ← Hostname updated

const int LED_PIN = 2;

// V2 Blink pattern: fast triple-flash then pause
const int FLASH_ON    = 100;   // 100ms on
const int FLASH_OFF   = 100;   // 100ms between flashes
const int PAUSE_TIME  = 800;   // 800ms pause after triple-flash

// ─── Function Prototypes ──────────────────────────────────────────
void printBanner();
void connectToWiFi();
void setupOTA();
void blinkLEDv2();

// ─── Setup ────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(LED_PIN, OUTPUT);

  printBanner();
  connectToWiFi();
  setupOTA();

  // ── V2 Success Message ────────────────────────────────────────
  Serial.println("─────────────────────────────────────────────");
  Serial.println("🎉 OTA Update Successful – Now Running v2!");
  Serial.println("   New features in this version:");
  Serial.println("   • Triple-flash LED blink pattern");
  Serial.println("   • Improved OTA progress display");
  Serial.println("   • Version tracking in Serial output");
  Serial.println("─────────────────────────────────────────────");
}

// ─── Loop ─────────────────────────────────────────────────────────
void loop() {
  ArduinoOTA.handle();   // Must be called in every loop iteration

  blinkLEDv2();          // V2: fast triple-flash pattern
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

  // ── OTA Event: Start ──────────────────────────────────────────
  ArduinoOTA.onStart([]() {
    String type = (ArduinoOTA.getCommand() == U_FLASH) ? "Sketch" : "Filesystem";
    Serial.println("\n🚀 OTA Update Started!");
    Serial.printf("   Update type: %s\n", type.c_str());
    Serial.printf("   Current version: %s → New version incoming...\n", FIRMWARE_VERSION);
    digitalWrite(LED_PIN, LOW);
  });

  // ── OTA Event: End ────────────────────────────────────────────
  ArduinoOTA.onEnd([]() {
    Serial.println("\n✅ OTA Transfer Complete!");
    Serial.println("   Validating firmware...");
    Serial.println("   Rebooting into new firmware now...");
    Serial.println("─────────────────────────────────────────────");
  });

  // ── OTA Event: Progress ───────────────────────────────────────
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    unsigned int percent   = (progress / (total / 100));
    unsigned int received  = progress / 1024;
    unsigned int totalKB   = total    / 1024;

    Serial.printf("\r⬆️  Uploading: [");
    int bars = percent / 5;
    for (int i = 0; i < 20; i++) {
      Serial.print(i < bars ? "█" : "░");
    }
    Serial.printf("] %3u%% (%u / %u KB)", percent, received, totalKB);
  });

  // ── OTA Event: Error ──────────────────────────────────────────
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("\n❌ OTA Error [%u]: ", error);
    switch (error) {
      case OTA_AUTH_ERROR:    Serial.println("Authentication Failed – Check password"); break;
      case OTA_BEGIN_ERROR:   Serial.println("Begin Failed – Not enough space?");        break;
      case OTA_CONNECT_ERROR: Serial.println("Connect Failed – Network issue?");         break;
      case OTA_RECEIVE_ERROR: Serial.println("Receive Failed – Upload interrupted");     break;
      case OTA_END_ERROR:     Serial.println("End Failed – Validation error");           break;
      default:                Serial.println("Unknown Error");                            break;
    }
    Serial.println("   ⚠️  Device remains on current firmware.");
  });

  ArduinoOTA.begin();

  Serial.println("\n📥 OTA Service Started");
  Serial.printf("   Hostname  : %s\n", HOSTNAME);
  Serial.printf("   OTA Port  : 3232 (default)\n");
}

// ─── LED Blink — V2 Pattern (Triple-flash then pause) ─────────────
void blinkLEDv2() {
  static unsigned long lastAction = 0;
  static int step = 0;

  unsigned long now = millis();

  // Step sequence: ON, OFF, ON, OFF, ON, PAUSE (repeat)
  //   0: flash 1 ON   → FLASH_ON
  //   1: flash 1 OFF  → FLASH_OFF
  //   2: flash 2 ON   → FLASH_ON
  //   3: flash 2 OFF  → FLASH_OFF
  //   4: flash 3 ON   → FLASH_ON
  //   5: pause (LED off) → PAUSE_TIME

  const int delays[] = {
    FLASH_ON, FLASH_OFF,
    FLASH_ON, FLASH_OFF,
    FLASH_ON, PAUSE_TIME
  };
  const bool states[] = {
    HIGH, LOW,
    HIGH, LOW,
    HIGH, LOW
  };

  if (now - lastAction >= (unsigned long)delays[step]) {
    lastAction = now;
    digitalWrite(LED_PIN, states[step]);
    step = (step + 1) % 6;
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