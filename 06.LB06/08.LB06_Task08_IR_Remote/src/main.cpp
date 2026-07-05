#include <Arduino.h>
#define IR_RECEIVE_PIN 4 
#include <IRremote.hpp>

void setup() {
  Serial.begin(115200);
  Serial.println("IR Remote Test");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("HEX Code: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX); 
    IrReceiver.resume(); 
  }
}