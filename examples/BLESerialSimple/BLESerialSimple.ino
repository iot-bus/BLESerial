/*

 BLESerial was written by Ian Archbell of oddWires. It is based on the BLE implementation
 originally created by Neil Kolban and included in the Espressif esp32 distribution.
 This library makes it simple to send and received data that would normally go to or be sent by
 the serial monitor. The interface is very similar so most usage is identical.

 To use:

  1. Create an instance of BLESerial
  2. Define it as Serial (not necessary as you can use it directly as your named instance 
     but makes it easy to add to existing programs)
  3. Make sure you call begin()   

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

char message[] = "A message";

#define Serial bleSerial

#define LEDPin 5

void setup() {  
  Serial.begin("IoT-Bus Bluetooth Serial"); 
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
}

void loop() {
  if (Serial.connected()){ 

    digitalWrite(LEDPin, HIGH);
    // some output
    Serial.println("Output being sent to Bluetooth");
    Serial.println("Starting");

    for(int i=0; i<strlen(message);i++){
      Serial.write(message[i]);
    }
    Serial.println();

    Serial.println(F("Another message"));

    Serial.println();
  }
  else{
    digitalWrite(LEDPin, LOW);
  }

}

