#define BLYNK_TEMPLATE_ID "TMPL6OqEkyz2y"
#define BLYNK_TEMPLATE_NAME "Labwork Temperature Automation"
#define BLYNK_AUTH_TOKEN    "NtNK7WAVPcYsKf64rBWY533rMJ9cnwSC"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- Pin Mapping ---
#define DHTPIN 15          // DHT22 Data
#define SERVOPIN 18        // Servo Signal
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

unsigned long lastExecutionTime = 0; // Tracks the elapsed time
int blynkOverride = 0;              // Tracks Blynk button state

// Receives commands from Blynk App Switch (V3)
BLYNK_WRITE(V3) {
  blynkOverride = param.asInt();
  if (blynkOverride == 1) {
    myServo.write(180);
  } else {
    myServo.write(0);
  }
}

void setup() {
  Serial.begin(115200);

  // Start LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Connecting...");

  // Start DHT Sensor
  dht.begin();

  // Start Servo
  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50);
  myServo.attach(SERVOPIN, 500, 2400);

  // Connect to WiFi and Blynk
  Blynk.begin(auth, ssid, pass);
  
  lcd.clear();
  lcd.print("System Ready!");
  delay(1000);
}

void loop() {
  Blynk.run(); // Keeps Blynk connection alive

  // Simple millis delay: Runs this block exactly once every 2000 milliseconds (2 seconds)
  if (millis() - lastExecutionTime >= 2000) {
    lastExecutionTime = millis(); // Reset the timestamp tracker

    // 1. Read Sensor Data
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (isnan(temp) || isnan(hum)) {
      Serial.println("Error reading DHT22!");
      return; 
    }

    // 2. Send Data to Blynk Dashboard
    Blynk.virtualWrite(V1, temp);
    Blynk.virtualWrite(V2, hum);

    // 3. Update LCD Screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp, 1);
    lcd.print((char)223); // Degree character symbol
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Humid: ");
    lcd.print(hum, 1);
    lcd.print("%");

    // 4. Automatic Servo Logic (If Blynk switch is turned off)
    if (blynkOverride == 0) {
      if (temp > 30.0) {
        myServo.write(90);  // Rotate to 90 degrees if hot
      } else {
        myServo.write(0);   // Return to 0 degrees if cool
      }
    }
  }
}