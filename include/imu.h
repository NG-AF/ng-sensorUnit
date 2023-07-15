/************************************************************************
                                                                        Source
Code Form License Notice
                                                -------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

If it is not possible or desirable to put the notice in a particular
file, then You may include the notice in a location (such as a LICENSE
file in a relevant directory) where a recipient would be likely to look
for such a notice.
*************************************************************************/

//* EXTERNAL LIBRARIES
#include <Arduino.h>
#include <Deneyap_6EksenAtaletselOlcumBirimi.h>

class IMUVals {
public:
  float gX, gY, gZ; // Create variables for Gyro Values
  float aX, aY, aZ; // Create variables for Accel Values

  void readValues(LSM6DSM IMU) { // Read IMU Values
    //? Read Gyro Values
    gX = IMU.readFloatGyroX();
    gY = IMU.readFloatGyroY();
    gZ = IMU.readFloatGyroZ();

    //? Read Accel Values
    aX = IMU.readFloatAccelX();
    aY = IMU.readFloatAccelY();
    aZ = IMU.readFloatAccelZ();
  }

  void sendValuesToPlotter() { // Print values to plotter
    Serial.println(">Gyro X:" + String(gX));
    Serial.println(">Gyro Y:" + String(gY));
    Serial.println(">Gyro Z:" + String(gZ));
    Serial.println(">Accel X:" + String(aX));
    Serial.println(">Accel Y:" + String(aY));
    Serial.println(">Accel Z:" + String(aZ));
  }
};
