#define BLYNK_TEMPLATE_ID "TMPL6q3adVhDC"
#define BLYNK_TEMPLATE_NAME "Smart Parking Assistant"
#define BLYNK_AUTH_TOKEN "qewiSQH7C5NzYRaUZ18ZYXtl_wXvXZKv"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi details
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// Sensor pins
#define TRIG_PIN 5
#define ECHO_PIN 18

// RGB LED pins
#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27

// Buzzer pin
#define BUZZER 14

void setup()
{
  // Start serial monitor
  Serial.begin(115200);

  // System start message
  Serial.println("SMART PARKING ASSISTANT");
  Serial.println("System Testing Started");

  // Set sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set LED pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Set buzzer pin
  pinMode(BUZZER, OUTPUT);

  // Connect to WiFi and Blynk
  Serial.println("Connecting...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Check Blynk connection
  if (Blynk.connected())
  {
    Serial.println("Blynk Connected");
  }
  else
  {
    Serial.println("Blynk Not Connected");
  }
}

void loop()
{
  // Run Blynk
  Blynk.run();

  long duration;
  float distance;

  // Send ultrasonic signal
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Read echo signal
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance
  distance = duration * 0.034 / 2;

  // Show distance
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send distance to Blynk
  Blynk.virtualWrite(V0, distance);

  // Danger zone
  if (distance < 10){
    // Red LED ON
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);

    // Fast buzzer
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(100);

    // Update Blynk
    Blynk.virtualWrite(V1, 255);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, "DANGER");

    Serial.println("Status : DANGER");
  }

  // Caution zone
  else if (distance >= 10 && distance <= 30){
    // Yellow LED ON
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);

    // Slow buzzer
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER, LOW);
    delay(500);

    // Update Blynk
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 255);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, "CAUTION");

    Serial.println("Status : CAUTION");
  }

  // Safe zone
  else{
    // Green LED ON
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);

    // Buzzer OFF
    digitalWrite(BUZZER, LOW);

    // Update Blynk
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 255);
    Blynk.virtualWrite(V4, "SAFE");

    Serial.println("Status : SAFE");

    delay(500);
  }
}