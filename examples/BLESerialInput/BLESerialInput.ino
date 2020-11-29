/*

 BLESerial was written by Ian Archbell of oddWires. It is based on the BLE implementation
 originally created by Neil Kolban and included in the Espressif esp32 distribution.
 This library makes it simple to send and received data that would normally go to or be sent by
 the serial monitor. The interface is very similar so most usage is identical.

 To use:

  1. Create an instance of BLESerial 
  2. Make sure you call begin()   

 In this example we don't redefine bleSerial as Serial as we want to use both the bluetooth serial and the regular serial monitor. 

 There is a connected() method that enables you to find out whether a bluetooth central manager is connected.

 You will need an Ios or Android app on your phone that will connect to the Nordic BLE Serial UART service
 and use its associated characteristics.   

We suggest using basic-chat which is a Bluetooth Low Energy App for iOS using Swift originally written by Adafruit. 
This fork is updated for Swift 4 and to easily interface with BLESerial library for esp32 on github at: 
https://github.com/iot-bus/basic-chat

*/

#include "BLESerial.h"
#include <arduino.h>

BLESerial bleSerial;

#define LEDPin 5

void setup() {  
  Serial.begin(115200);
  bleSerial.begin("IoT-Bus Bluetooth Serial"); 
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
}

void loop() {
  if (bleSerial.connected()){  
    digitalWrite(LEDPin, LOW);  
    // Read input
    if(bleSerial.available())
    {
      Serial.println("*********");
      while(bleSerial.available())
      {
        Serial.write(bleSerial.read());
      }
      Serial.println("*********");
    }  
  }
  else{
    digitalWrite(LEDPin, HIGH);
  }
}

