/*
 * This Arduino code prints the sensor readings to
 * the serial which can be logged using PuTTY or other programs
 */

#include "HX711.h"

const int SENSOR_COUNT = 6;
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN[SENSOR_COUNT] = {3, 4, 5, 6, 7, 8}; //
const int LOADCELL_SCK_PIN = 2;                                 //

HX711 scale[6]; // 6 load cells are used

void setup()
{
    Serial.begin(9600);

    for (int i = 0; i < SENSOR_COUNT; i++)
    {
        scale[i].begin(LOADCELL_DOUT_PIN[i], LOADCELL_SCK_PIN);
        scale[i].set_scale(2280.f); // this value is obtained by calibrating the scale with known weights; see the README for details
        scale[i].tare();            // reset the scale to 0
    }
}

void loop()
{
    Serial.print(millis());

    for (int i = 0; i < SENSOR_COUNT; i++)
    {
        Serial.print(",");
        Serial.print(scale[i].get_units(), 1);
    }

    Serial.println("");
}