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

class IMUVals {
public:
	float gX, gY, gZ; // Create variables for Gyro Values
	float aX, aY, aZ; // Create variables for Accel Values

	void readValues();
};


void sendValuesToPlotter(IMUVals imu)
{ // Print values to plotter
	Serial.println(">Gyro X:" + String(imu.gX));
	Serial.println(">Gyro Y:" + String(imu.gY));
	Serial.println(">Gyro Z:" + String(imu.gZ));
	Serial.println(">Accel X:" + String(imu.aX));
	Serial.println(">Accel Y:" + String(imu.aY));
	Serial.println(">Accel Z:" + String(imu.aZ));
}