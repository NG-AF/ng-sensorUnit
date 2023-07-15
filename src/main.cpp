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
#include "plot.h"

LSM6DSM IMU; // Create IMU object
IMUVals imu;

void IMUVals::readValues() {
  //? Read Gyro Values
  imu.gX = IMU.readFloatGyroX();
  imu.gY = IMU.readFloatGyroY();
  imu.gZ = IMU.readFloatGyroZ();

  //? Read Accel Values
  imu.aX = IMU.readFloatAccelX();
  imu.aY = IMU.readFloatAccelY();
  imu.aZ = IMU.readFloatAccelZ();
}

void setup()
{
  Serial.begin(115200);
  while (IMU.begin() != IMU_SUCCESS)
  {
    Serial.println("I2C bağlantısı başarısız ");
    delay(1000);
  }
}

void loop()
{
  sendValuesToPlotter(imu); // Print values to plotter
}