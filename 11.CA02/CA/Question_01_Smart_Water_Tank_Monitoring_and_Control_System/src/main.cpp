#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define PUMP_PIN 2

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define MQTT_BROKER "192.168.116.178"
#define MQTT_PORT 1883
#define MQTT_CLIENT "esp32-water-tank"

WiFiClient espClient;
PubSubClient mqtt(espClient);

const char *TOPIC_LEVEL = "home/tank/level";
const char *TOPIC_PUMP = "home/tank/pump";
const char *TOPIC_CMD = "home/tank/pump/set";

bool manualMode = false;

void callback(char *topic, byte *payload, unsigned int length){

  String msg = "";
  for (int i = 0; i < length; i++)
    msg += (char)payload[i];
  if (String(topic) == TOPIC_CMD){
    if (msg == "ON"){
      digitalWrite(PUMP_PIN, HIGH);
      mqtt.publish(TOPIC_PUMP, "ON", true);
    }
    if (msg == "OFF"){
      digitalWrite(PUMP_PIN, LOW);
      mqtt.publish(TOPIC_PUMP, "OFF", true);
    }
  }
}

void connectWiFi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

void connectMQTT(){
  while (!mqtt.connected()){
    Serial.print("Connecting MQTT...");
    if (mqtt.connect(MQTT_CLIENT)){
      Serial.println("Connected");
      mqtt.subscribe(TOPIC_CMD);
    }else{

      delay(2000);
    }
  }
}

float getDistance(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void setup(){
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  connectWiFi();
  mqtt.setServer(MQTT_BROKER, MQTT_PORT);
  mqtt.setCallback(callback);
}

void loop(){
  if (!mqtt.connected())
    connectMQTT();
  mqtt.loop();
  static unsigned long lastPub = 0;
  if (millis() - lastPub > 2000){

    float distance = getDistance();

    float level = ((200 - distance) / 200.0) * 100;

    if (level < 0)
      level = 0;
    if (level > 100)
      level = 100;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm  ");

    Serial.print("Level: ");
    Serial.print(level);
    Serial.println("%");

    mqtt.publish(TOPIC_LEVEL,String((int)level).c_str(),true);
    if (level < 30){
      digitalWrite(PUMP_PIN, HIGH);
      mqtt.publish(TOPIC_PUMP, "Pump ON - Low Water Level",true);
    }else if (level > 80){
      digitalWrite(PUMP_PIN, LOW);
      mqtt.publish(TOPIC_PUMP,"Tank Full",true);
    }else{
      digitalWrite(PUMP_PIN, LOW);
      mqtt.publish(TOPIC_PUMP,"Normal Level",true);
    }
    lastPub = millis();
  }
}