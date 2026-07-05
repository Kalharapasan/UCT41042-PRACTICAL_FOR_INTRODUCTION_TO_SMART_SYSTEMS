#define BLYNK_TEMPLATE_ID "TMPL6OqEkyz2y"
#define BLYNK_TEMPLATE_NAME "Labwork Temperature Automation"
#define BLYNK_AUTH_TOKEN "NtNK7WAVPcYsKf64rBWY533rMJ9cnwSC"
#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <ESP32Servo.h> // Fixed: Standard Servo.h doesn't work on ESP32, changed to ESP32Servo
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define SERVO_PIN 18
#define VPIN_TEMP V1
#define VPIN_HUM V2
#define VPIN_SERVO V3

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;
BlynkTimer timer;

// Added tracker to replace bad delay(2000) in loop
unsigned long lastTime = 0; 

BLYNK_WRITE(VPIN_SERVO)
{
  int buttonState = param.asInt();

  if (buttonState == 1)
  {
    myservo.write(90);
  }
  else
  {
    myservo.write(0);
  }
}

void sendSensorData()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    Serial.println("Temperature Or Humidity Read Error !");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity, 1);
  lcd.print("%");

  Blynk.virtualWrite(VPIN_TEMP, temperature);
  Blynk.virtualWrite(VPIN_HUM, humidity);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Temperature Auotomation Task01");

  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Fixed: WiFi.begin must be called BEFORE checking status loop
  WiFi.begin(ssid, pass); 

  lcd.setCursor(0, 0);
  lcd.print("Connecting WIFI");
  Serial.print("Connecting WIFI");

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 20)
  {
    delay(500);
    lcd.print(".");
    Serial.print(".");
    attempt++;
  }

  lcd.clear();
  if (WiFi.status() == WL_CONNECTED)
  {
    lcd.setCursor(0, 0);
    lcd.println("WiFi Connected");
    Serial.println("\nWiFi Connected");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.println("WiFi Conn Failed");
    Serial.println("WiFi Connection Failed");
  }

  delay(1500);
  lcd.clear();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  dht.begin();
  
  // Fixed: ESP32 PWM timer allocation for servo stability
  ESP32PWM::allocateTimer(0);
  myservo.setPeriodHertz(50);
  
  myservo.attach(SERVO_PIN, 500, 2400);
  myservo.write(0);

  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  Serial.println("System Ready");
  delay(1000);
  lcd.clear();

  timer.setInterval(2000L, sendSensorData);
}

void loop()
{
  Blynk.run();
  timer.run();
}
