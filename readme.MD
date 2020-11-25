 # ESP32 BLE Serial library
 This library makes it simple to send and received data that would normally go to or be sent by
 the serial monitor. The interface is very similar so most usage is identical.

## Features

 - [x] Connect the ESP32 to [P5](https://editor.p5js.org/lemio/sketches/qKGGxBG4C)
 - [x] Connect the ESP32 to ["Bluefruit le Connect" App](https://learn.adafruit.com/bluefruit-le-connect)

## Installation
- (Make sure you can use the ESP32 with the Arduino IDE. [Instructions can be found here.](https://github.com/espressif/arduino-esp32#installation-instructions))
- Download the current repository, by clicking code in the right top, and download ZIP.
- In the Arduino IDE go to "Sketch" -> "Include Library" -> "Add .ZIP Library..." and select the file you just downloaded.
- Select an ESP32 board in "Tools" -> "Board"
- You can now go to "File" -> "Examples" -> "BLESerial" and select any of the examples to get started.

## Example

``` C++
#include "BLESerial.h"
BLESerial bleSerial;

void setup() {  
  Serial.begin(115200);
  bleSerial.begin("BLE-UART");
}

void loop() {
  //If we're connected
  if (bleSerial.connected()){  
    //Send the analog value through BLE/Serial
    bleSerial.println(analogRead(A0));
    //Send the analog value through USB/Serial
    Serial.println(analogRead(A0));
    //Wait for 0.1 second
    delay(100);
  }
}
```

 In this example we don't redefine bleSerial as Serial as we want to use both the bluetooth serial and the regular serial monitor. 

 There is a connected() method that enables you to find out whether a bluetooth central manager is connected.

 You will need an Ios or Android app on your phone that will connect to the Nordic BLE Serial UART service
 and use its associated characteristics.  

To interact with this the ESP32 there are several options:

1. Adafruit ["Bluefruit le Connect" App](https://learn.adafruit.com/bluefruit-le-connect), this lets you plot the values, see the messages, send messages and more...
2. If you want to create your own application useing P5 you can use [p5.ble.js](https://github.com/ITPNYU/p5.ble.js/tree/master/examples/BluefruitLE), we made [an example for plotting the values](https://editor.p5js.org/lemio/sketches/qKGGxBG4C).
3. Basic-chat which is a Bluetooth Low Energy App for iOS using Swift originally written by Adafruit. 
 This fork is updated for Swift 4 and to easily interface with BLESerial library for esp32 on github at: 
 https://github.com/iot-bus/basic-chat

 ## Credits

 BLESerial was written by Ian Archbell of oddWires. It is based on the BLE implementation
 originally created by Neil Kolban and included in the Espressif esp32 distribution.