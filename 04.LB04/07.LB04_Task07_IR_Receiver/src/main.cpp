#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// 1. Define the GPIO pin connected to the IR sensor
const uint16_t kRecvPin = 4;

// 2. Establish the IR receiver object
IRrecv irrecv(kRecvPin);
decode_results results;

void setup() {
  Serial.begin(115200);
  
  // 3. Start the receiver
  irrecv.enableIRIn(); 
  Serial.print("IR Receiver ready on GPIO ");
  Serial.println(kRecvPin);
}

void loop() {
  // 4. Check if a signal was received
  if (irrecv.decode(&results)) {
    // Print the protocol (NEC, Sony, etc.) and the Hex code
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    
    // Resume listening for the next signal
    irrecv.resume(); 
  }
  delay(100);
}