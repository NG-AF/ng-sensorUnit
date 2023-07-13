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

LSM6DSM IMU; // Create IMU object

struct IMUVals
{
  float gX, gY, gZ; // Create variables for Gyro Values
  float aX, aY, aZ; // Create variables for Accel Values
} imuv;

void sendValuesToPlotter() { // Print values to plotter
  Serial.print(">Gyro X:");
  Serial.println(imuv.gX);

  Serial.print(">Gyro Y:");
  Serial.println(imuv.gY);

  Serial.print(">Gyro Z:");
  Serial.println(imuv.gZ);

  Serial.print(">Accel X:");
  Serial.println(imuv.aX);

  Serial.print(">Accel Y:");
  Serial.println(imuv.aY);

  Serial.print(">Accel Z:");
  Serial.println(imuv.aZ);
} 

void setup() {
  Serial.begin(115200);                               // Seri haberleşme başlatıldı
    while (IMU.begin() != IMU_SUCCESS) {              // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatıldı
        Serial.println("I2C bağlantısı başarısız ");  // I2C bağlantısı başarısız olursa seri terminale yazdırma
        delay(1000);                                 
  }
}

void loop() {
  //? Read Gyro Values
  imuv.gX = IMU.readFloatGyroX();
  imuv.gY = IMU.readFloatGyroY();
  imuv.gZ = IMU.readFloatGyroZ();  
  delay(50);
  //? Read Accel Values
  imuv.aX = IMU.readFloatAccelX();
  imuv.aY = IMU.readFloatAccelY();
  imuv.aZ = IMU.readFloatAccelZ();
  delay(50);

  sendValuesToPlotter(); // Print values to plotter
}
