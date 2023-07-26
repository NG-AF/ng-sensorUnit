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

//* EXTERNAL LIBRARIES
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <WiFi.h>

//* LOCAL LIBRARIES
#include "HKD_IMU.h"
//! #include "bmp.h"

//* GLOBAL VARIABLES
IMU imu;

//! Adafruit_BMP085 BMP; // Create BMP object
//! BMPVals bmp;

const char *ssid = "NGTelemetryNetwork";   // WiFi SSID
const char *password = "99733940"; // WiFi Password

//* FUNCTIONS
void initWifi() {
  WiFi.mode(WIFI_STA);        // Set WiFi mode to station
  WiFi.begin(ssid, password); // Connect to WiFi

  Serial.println("Connecting to WiFi....");

  while (WiFi.status() != WL_CONNECTED) { // Check if WiFi is connected
    Serial.println("WiFi connection failed");
    delay(500);
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("RSSI: " + String(WiFi.RSSI()) + " dBm");

  delay(3000);
}

void setup() {
  Serial.begin(115200); // Start serial communication
  Serial.println("Serial started");

  imu.startIMU(2000); // Start IMU

  //! BMP code
  /* while (BMP.begin() != true) { // Check if BMP is connected
    Serial.println("BMP connection failed");
    delay(500);
  } */

  initWifi();
}

void loop() {
  HTTPClient http;
  http.begin("http://192.168.1.100:3001/api"); //! Don't forget to change IP
  // addres when changing WiFi
  http.addHeader("Content-Type", "application/json");

  imu.readValues();
  imu.plotValuesToThePlotter();
  //! bmp.readValues(BMP);
  //! bmp.sendValuesToPlotter();

  //? Create JSON payload
  String payload =
      "{\"gyro\":{\"x\":" + String(imu.telemetryData.gyroPRY[0]) +
      ",\"y\":" + String(imu.telemetryData.gyroPRY[1]) + ",\"z\":" + String(imu.telemetryData.gyroPRY[2]) +
      "},\"accel\":{\"x\":" + String(imu.telemetryData.accelG[0]) +
      ",\"y\":" + String(imu.telemetryData.accelG[1]) + ",\"z\":" + String(imu.telemetryData.accelG[2]) +
      "} ,\"angle\":{\"roll\":" + String(imu.telemetryData.anglePRY[1]) +
      ",\"pitch\":" + String(imu.telemetryData.anglePRY[0]) +
      ",\"yaw\":" + String(imu.telemetryData.anglePRY[2]) + "}}";

  //? Debug code
  // Serial.println(payload);

  //? Send payload to server
  http.POST(payload);
  delay(10);
}