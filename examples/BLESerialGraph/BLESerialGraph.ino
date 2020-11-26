/*

 BLESerial was written by Ian Archbell of oddWires. It is based on the BLE implementation
 originally created by Neil Kolban and included in the Espressif esp32 distribution.
 This library makes it simple to send and received data that would normally go to or be sent by
 the serial monitor. The interface is very similar so most usage is identical.

 To use:

  1. Create an instance of BLESerial 
  2. Make sure you call begin()   

 In this example we use BLESerial to use in a similair way as the "graph" example in the IDE. 
 You could use this P5 sketch to plot the data from the Arduino (if using chrome)
 https://editor.p5js.org/lemio/sketches/qKGGxBG4C
 Or use the Adafruit "Bluefruit Connect" App. 

*/

#include "BLESerial.h"
BLESerial bleSerial;

void setup() {  
  Serial.begin(115200);
  bleSerial.begin("BLE-UART");
}

void loop() {
  //If we're connected
  if (bleSerial.connected()){  
    //Send the analog value
    bleSerial.println(analogRead(A0));
    Serial.println(analogRead(A0));
    //Wait for 0.1 second
    delay(100);
  }
}
