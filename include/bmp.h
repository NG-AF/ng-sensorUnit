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
#include <Adafruit_BMP085.h>
#include <SPI.h>

#define seaLevelPressure_hPa 1013.25

class BMPVals
{
public:
    float airPressure, altitude, calcAltitude;

    void readValues(Adafruit_BMP085 bmp) {
        airPressure = bmp.readPressure();
        altitude = bmp.readAltitude();
        calcAltitude = bmp.readAltitude(seaLevelPressure_hPa * 100);
    }
    
    void sendValuesToPlotter() {
        Serial.println(">Air Pressure:" + String(airPressure));
        Serial.println(">Altitude:" + String(altitude));
        Serial.println(">Calculated Altitude:" + String(calcAltitude));
    }
};