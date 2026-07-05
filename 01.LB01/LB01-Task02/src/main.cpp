#include <WiFi.h>
#include <WiFiManager.h>  

WiFiManager wm;

void setup() {

  Serial.begin(115200);
  delay(10000);

  Serial.println("\n\n ESP32 WiFi Manager Starting...");
  WiFi.mode(WIFI_STA);
  bool res = wm.autoConnect("ESP32-Config-Portal");

  if(res){
    Serial.println("Succesfully connected to Wi-Fi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }else{
    Serial.println("\nFailed to connect.");
  }
  
}

void loop() {
  delay(1000);
}