/************************************************************************
                    Source Code Form License Notice
            -------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

If it is not possible or desirable to put the notice in a particular
file, then You may include the notice in a location (such as a LICENSE
file in a relevant directory) where a recipient would be likely to look
for such a notice.
*************************************************************************/

//* LOCAL LIBRARIES
#include "bmp.h"
#include "imu.h"

//* EXTERNAL LIBRARIES
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <Deneyap_6EksenAtaletselOlcumBirimi.h>
#include <SPI.h>

//* GLOBAL VARIABLES
LSM6DSM IMU; // Create IMU object
IMUVals imu;

Adafruit_BMP085 BMP; // Create BMP object
BMPVals bmp;

//* FUNCTIONS
void setup() {
  Serial.begin(115200); // Start serial communication
  Serial.println("Serial started");

  while (IMU.begin() != IMU_SUCCESS) { // Check if IMU is connected
    Serial.println("IMU connection failed");
    delay(500);
  }

  while (BMP.begin() != true) { // Check if BMP is connected
    Serial.println("BMP connection failed");
    delay(500);
  }
}

void loop() {
  imu.readValues(IMU);
  imu.sendValuesToPlotter();

  bmp.readValues(BMP);
  bmp.sendValuesToPlotter();
}