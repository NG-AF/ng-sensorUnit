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
//! #include "bmp.h"
#include "imu.h"

//* EXTERNAL LIBRARIES
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <Deneyap_6EksenAtaletselOlcumBirimi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <WiFi.h>

//* GLOBAL VARIABLES
LSM6DSM IMU; // Create IMU object
IMUVals imu;

//! Adafruit_BMP085 BMP; // Create BMP object
//! BMPVals bmp;

const char *ssid = "DOGAN_2.4GHz";   // WiFi SSID
const char *password = "Hakan26181"; // WiFi Password

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

  while (IMU.begin() != IMU_SUCCESS) { // Check if IMU is connected
    Serial.println("IMU connection failed");
    delay(500);
  }

  //! BMP code
  /* while (BMP.begin() != true) { // Check if BMP is connected
    Serial.println("BMP connection failed");
    delay(500);
  } */

  initWifi();
}

void loop() {
  HTTPClient http;
  http.begin("http://192.168.1.12:3001/api"); //! Don't forget to change IP addres when changing WiFi
  http.addHeader("Content-Type", "application/json");

  imu.readValues(IMU);
  imu.sendValuesToPlotter();
  //! bmp.readValues(BMP);
  //! bmp.sendValuesToPlotter();

  delay(25);

  String payload =
      "{\"gyro\":{\"x\":" + String(imu.gX) + ",\"y\":" + String(imu.gY) +
      ",\"z\":" + String(imu.gZ) + "},\"accel\":{\"x\":" + String(imu.aX) +
      ",\"y\":" + String(imu.aY) + ",\"z\":" + String(imu.aZ) + "}}";

  //? Debug code
  Serial.println(payload);

  http.POST(payload);
  delay(25);
}