#include <Arduino.h>

#include <WiFi.h>        // Library to connect ESP32 to Wi-Fi
#include <ArduinoOTA.h> // Library to enable OTA (Over-The-Air updates)

// Wi-Fi credentials
const char* ssid ="MAC";
const char* password ="MacAP456";

// LED pin (built-in LED usually GPIO 2)
const int ledpin = 2;

void setup() {

  Serial.begin(115200); // Start serial communication
  Serial.println("\n\nOTA Version 1"); // FIX: missing semicolon added

  pinMode(ledpin, OUTPUT); // Set LED pin as output

  WiFi.mode(WIFI_STA); // Set ESP32 as Wi-Fi Station (client mode)

  WiFi.begin(ssid, password); // Start Wi-Fi connection
  Serial.print("Connecting to Wi-Fi");

  // Wait until Wi-Fi connects
  while (WiFi.waitForConnectResult() != WL_CONNECTED) { // FIX: WL_CONNECTED (uppercase)
    Serial.println("Connection Failed! Restarting...");
    delay(5000); // Wait 5 seconds
    ESP.restart(); // Restart ESP32 if connection fails
  }

  Serial.println("\nWi-Fi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Print ESP32 IP address

  // Set OTA device name
  ArduinoOTA.setHostname("Esp32-OTA-Lab");

  // OTA Start event
  ArduinoOTA.onStart([]() {
    String type = (ArduinoOTA.getCommand() == U_FLASH) ? "Sketch" : "FileSystem";
    Serial.println("\nStart Updating " + type);
  });

  // OTA Progress event
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress * 100) / total); // FIX: quotes added
  });

  // OTA End event
  ArduinoOTA.onEnd([]() {
    Serial.println("\nUpdate Success! Rebooting");
  });

  // OTA Error handling
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]", error);

    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin(); // Start OTA service

  Serial.println("====\nOTA Ready! You can now upload new version");
}

void loop() {
  ArduinoOTA.handle(); // Handle OTA requests continuously

  // Blink LED ON
  digitalWrite(ledpin, HIGH);
  delay(1000);

  // Blink LED OFF
  digitalWrite(ledpin, LOW);
  delay(1000);
}