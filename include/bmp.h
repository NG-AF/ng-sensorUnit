#include <Arduino.h>
#include <Adafruit_BMP085.h>

#define seaLevelPressure_hPa 1013.25

class BMPVals
{
public:
    float airPressure, altitude, calcAltitude;

    void readValues(Adafruit_BMP085 bmp) {
        airPressure = bmp.readPressure();
        altitude = bmp.readAltitude(seaLevelPressure_hPa);
        calcAltitude = bmp.readAltitude();
    }
    
    void sendValuesToPlotter() {
        Serial.println(">Air Pressure:" + String(airPressure));
        Serial.println(">Altitude:" + String(altitude));
        Serial.println(">Calculated Altitude:" + String(calcAltitude));
    }
};