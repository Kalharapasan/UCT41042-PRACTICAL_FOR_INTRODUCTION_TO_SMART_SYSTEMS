#include <Arduino.h>
#include <WiFi.h>

const char* ssid ="Wokwi-GUST";
const char* password ="";

void setup() {
  Serial.begin(115200);
  delay(1002);

  Serial.println("\n\nConnecting to WI-FI...");
  Serial.print("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid,password,6);
  int attemps =0;
  while(WiFi.status ! = WL_CONNECTED && attempts <50){

    Serial.print(".");
    attemps++;

  }

  if(WiFi.status()== WL_CONNECTED){
    Serial.println("\nConnected Suceessfully");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

  }else{
    Serial.println("\nFailed to Connect to the WIFI");
  }

}

void loop() {

}
