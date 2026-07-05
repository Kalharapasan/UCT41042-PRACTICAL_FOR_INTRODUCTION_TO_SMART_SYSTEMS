#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define POT_PIN 34
#define LOAD1_PIN 15
#define LOAD2_PIN 18

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define MQTT_BROKER "192.168.116.178"
#define MQTT_PORT 1883
#define MQTT_CLIENT "esp32-energy-monitor"

WiFiClient espClient;
PubSubClient mqtt(espClient);

const char *TOPIC_POWER = "home/energy/power";
const char *TOPIC_LOAD1 = "home/energy/load1";
const char *TOPIC_LOAD2 = "home/energy/load2";
const char *TOPIC_ALERT = "home/energy/alert";

const char *TOPIC_LOAD1_CMD = "home/energy/load1/set";
const char *TOPIC_LOAD2_CMD = "home/energy/load2/set";

bool autoShutdown = false;

void callback(char* topic, byte* payload, unsigned int length) {
  String msg="";
  for(int i=0;i<length;i++){
    msg += (char)payload[i];
  }
  if(!autoShutdown){
    if(String(topic)==TOPIC_LOAD1_CMD){
      if(msg=="ON"){
        digitalWrite(LOAD1_PIN,HIGH);
        mqtt.publish(TOPIC_LOAD1,"ON",true);
      }else{
        digitalWrite(LOAD1_PIN,LOW);
        mqtt.publish(TOPIC_LOAD1,"OFF",true);
      }
    }

    if(String(topic)==TOPIC_LOAD2_CMD){
      if(msg=="ON"){
        digitalWrite(LOAD2_PIN,HIGH);
        mqtt.publish(TOPIC_LOAD2,"ON",true);
      }else{
        digitalWrite(LOAD2_PIN,LOW);
        mqtt.publish(TOPIC_LOAD2,"OFF",true);
      }
    }
  }
}

void connectWiFi(){
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

void connectMQTT(){
  while(!mqtt.connected()){
    Serial.print("Connecting MQTT...");
    if(mqtt.connect(MQTT_CLIENT)){
      Serial.println("Connected");
      mqtt.subscribe(TOPIC_LOAD1_CMD);
      mqtt.subscribe(TOPIC_LOAD2_CMD);
    }else{
      delay(2000);
    }
  }
}

void setup(){
  Serial.begin(115200);
  pinMode(LOAD1_PIN,OUTPUT);
  pinMode(LOAD2_PIN,OUTPUT);
  connectWiFi();
  mqtt.setServer(MQTT_BROKER,MQTT_PORT);
  mqtt.setCallback(callback);
}

void loop(){
  if(!mqtt.connected()){
    connectMQTT();
  }

  mqtt.loop();
  static unsigned long lastPub=0;
  if(millis()-lastPub > 1000){
    int rawValue = analogRead(POT_PIN);
    int powerPercent = map(rawValue,0,4095,0,100);
    Serial.print("Raw Value: ");
    Serial.print(rawValue);
    Serial.print("  Power: ");
    Serial.print(powerPercent);
    Serial.println("%");
    mqtt.publish(TOPIC_POWER,String(powerPercent).c_str(),true);

    if(powerPercent > 65){
      autoShutdown = true;
      digitalWrite(LOAD1_PIN,LOW);
      mqtt.publish(TOPIC_LOAD1,"OFF",true);
      mqtt.publish(TOPIC_ALERT,"High Power - Load 1 OFF",true);
    }else{
      autoShutdown = false;
      mqtt.publish(TOPIC_ALERT,"Normal Power Usage",true);
    }
    mqtt.publish(TOPIC_LOAD1,digitalRead(LOAD1_PIN) ? "ON":"OFF",true);
    mqtt.publish(TOPIC_LOAD2,digitalRead(LOAD2_PIN) ? "ON":"OFF",true);
    lastPub = millis();
  }
}