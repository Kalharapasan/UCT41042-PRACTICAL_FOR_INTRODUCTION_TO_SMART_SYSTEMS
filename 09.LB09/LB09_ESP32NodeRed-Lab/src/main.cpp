#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Wi-Fi සහ MQTT Configurations
const char* ssid = "Wokwi-GUEST"; 
const char* password = "";
const char* mqtt_server = "192.168.116.232"; 

// Pin Definitions
#define DHTPIN 23
#define DHTTYPE DHT22
#define PIR_PIN 19
#define LED_PIN 22

// MQTT Topics
#define TOPIC_TEMP "home/room/temperature"
#define TOPIC_HUMID "home/room/humidity"
#define TOPIC_MOTION "home/room/motion"
#define TOPIC_LED_SET "home/room/led/set"

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// MQTT හරහා පණිවිඩ ලැබෙන විට ක්‍රියාත්මක වන ශ්‍රිතය (Callback)
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // LED එක පාලනය කිරීම
  if (String(topic) == TOPIC_LED_SET) {
    if (message == "ON") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED turned ON");
    } else if (message == "OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED turned OFF");
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // LED Topic එක Subscribe කිරීම
      client.subscribe(TOPIC_LED_SET);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();

  if (now - lastMsg > 2000) {
    lastMsg = now;

    // DHT22 දත්ත කියවීම
    float h = dht.readHumidity();
    float t = dht.readTemperature();


    int motionDetected = digitalRead(PIR_PIN);

    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

 
    Serial.print("Temp: "); Serial.print(t);
    Serial.print(" | Humid: "); Serial.print(h);
    Serial.print(" | Motion: "); Serial.println(motionDetected ? "MOTION!" : "No Motion");


    client.publish(TOPIC_TEMP, String(t).c_str());
    client.publish(TOPIC_HUMID, String(h).c_str());
    client.publish(TOPIC_MOTION, motionDetected ? "Motion Detected" : "Clear");
  }
}