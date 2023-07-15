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

#include <Arduino.h>
#include <Deneyap_6EksenAtaletselOlcumBirimi.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include "imu.h"
#include "bmp.h"

LSM6DSM IMU; // Create IMU object
IMUVals imu;

Adafruit_BMP085 BMP; // Create BMP object
BMPVals bmp;

void setup()
{
  Serial.begin(115200);
  while (IMU.begin() != IMU_SUCCESS)
  {
    Serial.println("IMU connection failed");
    delay(500);
  }

  while (BMP.begin() != true)
  {
    Serial.println("BMP connection failed");
    delay(500);
  }
}

void loop()
{
  imu.readValues(IMU);
  imu.sendValuesToPlotter();

  bmp.readValues(BMP);
  bmp.sendValuesToPlotter();
}