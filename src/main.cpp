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

//! Optimization
//* Before:  RAM:   [=         ]   7.0% (used 22896 bytes from 327680 bytes)
//*          Flash: [==        ]  22.6% (used 296477 bytes from 1310720 bytes)

//* After:   RAM:   [=         ]   7.0% (used 22856 bytes from 327680 bytes)
//*          Flash: [==        ]  20.1% (used 263825 bytes from 1310720 bytes

#include <Arduino.h>
#include <Deneyap_6EksenAtaletselOlcumBirimi.h>

struct IMUVals
{
  float gX, gY, gZ; // Create variables for Gyro Values
  float aX, aY, aZ; // Create variables for Accel Values
};

LSM6DSM IMU; // Create IMU object

void sendValuesToPlotter(IMUVals imu) { // Print values to plotter
  Serial.println(">Gyro X:" + String(imu.gX));
  Serial.println(">Gyro Y:" + String(imu.gY));
  Serial.println(">Gyro Z:" + String(imu.gZ));
  Serial.println(">Accel X:" + String(imu.aX));
  Serial.println(">Accel Y:" + String(imu.aY));
  Serial.println(">Accel Z:" + String(imu.aZ));
}

void setup() {
  Serial.begin(115200);
  while (IMU.begin() != IMU_SUCCESS) {
    Serial.println("I2C bağlantısı başarısız ");
    delay(1000);
  }
}

void loop() {
  IMUVals imuv;

    //? Read Gyro Values
  imuv.gX = IMU.readFloatGyroX();
  imuv.gY = IMU.readFloatGyroY();
  imuv.gZ = IMU.readFloatGyroZ();  

    //? Read Accel Values
  imuv.aX = IMU.readFloatAccelX();
  imuv.aY = IMU.readFloatAccelY();
  imuv.aZ = IMU.readFloatAccelZ();

  sendValuesToPlotter(imuv); // Print values to plotter
}