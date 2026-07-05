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

// --- Pin Definitions ---
#define DHTPIN 4          // DHT22 Data Pin
#define SERVOPIN 18        // Servo Signal Pin
#define DHTTYPE DHT22      // DHT 22 (AM2302)

// --- Object Initializations ---
DHT dht(DHTPIN, DHTTYPE);
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set I2C address to 0x27 for 16 chars and 2 line display
BlynkTimer timer;

// --- Network Settings for Wokwi Simulation ---
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST"; // Wokwi's built-in virtual WiFi network
char pass[] = "";            // No password for Wokwi-GUEST

// --- Global Variables ---
float temp = 0.0;
float hum = 0.0;
int blynkOverride = 0;

// Blynk Switch Widget (V3) to manually test/override Servo behavior
BLYNK_WRITE(V3) {
  blynkOverride = param.asInt();
  if (blynkOverride == 1) {
    myServo.write(180); // Move to max if switch is turned on
    Serial.println("Blynk Override: Servo moved to 180°");
  } else {
    myServo.write(0);   // Return to home
    Serial.println("Blynk Override: Servo moved to 0°");
  }
}

// --- Sensor Read and Update Task ---
void sendSensorData() {
  // Read values
  float newH = dht.readHumidity();
  float newT = dht.readTemperature();

  // Check if readings failed
  if (isnan(newH) || isnan(newT)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  temp = newT;
  hum = newH;

  // Print to Serial Monitor
  Serial.print("Temp: "); Serial.print(temp); Serial.print("°C | ");
  Serial.print("Humidity: "); Serial.print(hum); Serial.println("%");

  // Send data to Blynk Cloud
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum);

  // Update LCD Screen Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(hum, 1);
  lcd.print("%");

  // Logic: Automatically rotate servo if temperature crosses a threshold (e.g., 30°C)
  // Only triggers if Blynk override isn't explicitly forcing it.
  if (blynkOverride == 0) {
    if (temp > 30.0) {
      myServo.write(90); // Partial turn to simulate opening a vent/fan
    } else {
      myServo.write(0);  // Close position
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Temperature Auotomation Task01");

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  // Initialize DHT
  dht.begin();

  // Initialize Servo (Allowing standard pulse widths for ESP32)
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myServo.setPeriodHertz(50);    // Standard 50hz servo
  myServo.attach(SERVOPIN, 500, 2400);

  // Initialize Blynk connection
  Blynk.begin(auth, ssid, pass);

  lcd.clear();
  lcd.print("System Ready!");
  delay(1000);

  // Setup a timer to read data every 2000ms (2 seconds)
  // Crucial: Do NOT put sensor reads directly into loop() when using Blynk.
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}