#include <Arduino.h>
#define IR_RECEIVE_PIN 4 // Define the pin connected to the IR receiver output

// The IRremote library requires this macro definition BEFORE including the header
#define DECODE_NEC        // Optional: Saves memory by only enabling specific protocols
#include <IRremote.hpp>

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  Serial.println("IR Receiver Test");
  // Start the receiver and enable visual feedback (blinks onboard LED if applicable)
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver is ready. Point a remote and press a button!");
}

void loop() {
  // Check if a new IR signal has been received and decoded
  if (IrReceiver.decode()) {
    
    // Print the command in Hexadecimal format
    Serial.print("Protocol: ");
    Serial.print(IrReceiver.getProtocolString()); // Prints the protocol name (e.g., NEC, SONY)
    
    Serial.print(" | HEX Code: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX); // Prints the unique button HEX value
    
    // Resume receiving to prepare for the next button press
    IrReceiver.resume(); 
  }
}