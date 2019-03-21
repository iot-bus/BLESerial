/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
   Has a characteristic of: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E - used for receiving data with "WRITE" 
   Has a characteristic of: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E - used to send data with  "NOTIFY"

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   In this example rxValue is the data received (only accessible inside that function).
   And txValue is the data to be sent, in this example just a byte incremented every second. 
*/

#include "BLESerial.h"
#include <arduino.h>

#include <iostream>
#include <queue>

using namespace std;

char message[] = "Hello";
queue < char* > messageQueue;

BLESerial bleSerial;

// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h> // the OBD2 library depends on the CAN library
#include <OBD2.h>

// array of PID's to print values of
const int PIDS[] = {
  CALCULATED_ENGINE_LOAD,
  ENGINE_COOLANT_TEMPERATURE,
  ENGINE_RPM,
  VEHICLE_SPEED,
  AIR_INTAKE_TEMPERATURE,
  MAF_AIR_FLOW_RATE,
  THROTTLE_POSITION,
  RUN_TIME_SINCE_ENGINE_START,
  FUEL_TANK_LEVEL_INPUT,
  ABSOLULTE_BAROMETRIC_PRESSURE,
  ABSOLUTE_LOAD_VALUE,
  RELATIVE_THROTTLE_POSITION
};

const int NUM_PIDS = sizeof(PIDS) / sizeof(PIDS[0]);

void printPID(int pid) {
  // print PID name
  bleSerial.print(OBD2.pidName(pid));
  bleSerial.print(F(" = "));

  // read the PID value
  float pidValue = OBD2.pidRead(pid);

  if (isnan(pidValue)) {
   bleSerial.print("error");
  } else {
    // print value with units
    bleSerial.print(pidValue);
    bleSerial.print(F(" "));
    bleSerial.print(OBD2.pidUnits(pid));
  }

  bleSerial.println();
}



void setup() {
  Serial.begin(115200);
  Serial.println("All output being sent to Bluetooth UART");
  bleSerial.begin("IoT-Bus OBDII");
  while (!bleSerial.connected());
  delay(1000);
  bleSerial.println("Starting");

  bleSerial.println(F("OBD2 Key Stats"));

  // while (true) {
  //    bleSerial.print(F("Attempting to connect to OBD2 CAN bus ... "));

  //   if (!OBD2.begin()) {
  //      bleSerial.println(F("failed!"));

  //     delay(1000);
  //   } else {
  //      bleSerial.println(F("success"));
  //     break;
  //   }
  // }

   bleSerial.println();
}

void loop() {
  // loop through all the PID's in the array
  // 
  for (int i = 0; i < NUM_PIDS; i++) {
    int pid = PIDS[i];

    printPID(pid);
  }
   bleSerial.println();

  delay(1000);
}

