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
  const float g = 9.80665; // Gravitational acceleration [m/s^2]

  float *gyroPRY = new float[3];      // Gyro values
  float *gyroErrorPRY = new float[3]; // Gyro error values
  float *accel = new float[3];        // Acceleration values

  void calibrateGyro(LSM6DSM IMU) {

    Serial.println("Gyro calibration will start please don't touch the plane");
    delay(1500);
    Serial.println("Gyro calibration started");

    int gyroCalibrationIteration;

    for (int i = 0; i < 3; i++) { // Set gyro error values to 0
      gyroErrorPRY[i] = 0;
    }

    for (gyroCalibrationIteration = 0; gyroCalibrationIteration < 2000;
         gyroCalibrationIteration++) {
      float *allAxesFloatData = new float[7]; // All axes float values
      IMU.readAllAxesFloatData(allAxesFloatData);
      for (int i = 0; i < 3;
           i++) { // Assign values to their corresponding variables
        gyroErrorPRY[i] += allAxesFloatData[i];
      }
      delete[] allAxesFloatData; // Free the memory of allAxes
      delay(1);
    }

    for (int i = 0; i < 3; i++) { // Calculate average gyro error values
      gyroErrorPRY[i] /= gyroCalibrationIteration;
    }

    Serial.println("Gyro calibration finished");
  }

  void readValues(LSM6DSM IMU) {
    float *allAxesFloatData = new float[7]; // All axes float values
    IMU.readAllAxesFloatData(allAxesFloatData);
    for (int i = 0; i < 3;
         i++) { // Assign values to their corresponding variables
      gyroPRY[i] = ((allAxesFloatData[i] - //! Primitive error filtering
          gyroErrorPRY[i]) > 0.25 || (allAxesFloatData[i] - //TODO: Change this filtering with a kalman filter
          gyroErrorPRY[i]) < -0.25) ? allAxesFloatData[i] - gyroErrorPRY[i] : 0;
      accel[i] = allAxesFloatData[i + 3] * g; // Multiply accel values with g
    }
    delete[] allAxesFloatData; // Free the memory of allAxes
  }

  void plotValuesToThePlotter(LSM6DSM IMU) { // Plot values to the plotter
    Serial.println(">Gyro Pitch [°/s]: " + String(gyroPRY[0]));
    Serial.println(">Gyro Roll [°/s]: " + String(gyroPRY[1]));
    Serial.println(">Gyro Yaw [°/s]: " + String(gyroPRY[2]));
    Serial.println(">Accel X [m/s^2]: " + String(accel[0]));
    Serial.println(">Accel Y [m/s^2]: " + String(accel[1]));
    Serial.println(">Accel Z [m/s^2]: " + String(accel[2]));
  }
};
