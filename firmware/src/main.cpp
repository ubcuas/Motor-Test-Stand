/*
 * The code for UAS thrust test stand
 * Author: Charles Surianto
 */

#include <Arduino.h>

// constants
const int NUM_CELLS = 6;                            //
const int ZERO_PIN = 12;                            // zero button pin, internally pulled up
const int CLOCK_PIN = 2;                            //
const int DOUT_PIN[NUM_CELLS] = {3, 4, 5, 6, 7, 8}; // DOUT pins of each cell
const double SCALE_NEWTON[NUM_CELLS] = {
    // newton per readings (subject to change)
    4.51e-5, // cell 1
    4.77e-5, // cell 2
    4.64e-5, // cell 3
    4.75e-5, // cell 4
    4.64e-5, // cell 5
    4.75e-5  // cell 6
};

// global variables
unsigned long Time;            // holds current time in (ms)
unsigned long StartTime = 0;   // holds zero time
char LineBuffer[300];          //
char ValueBuffer[20];          //
long Readings[NUM_CELLS];      //
long Offsets[NUM_CELLS] = {0}; //

// prototypes
void zeroAll();
void read(long *);
void calibrate(int = 20);
bool areReady();

void setup()
{
    Serial.begin(38400);
    Serial.println("Starting up...");

    pinMode(CLOCK_PIN, OUTPUT);
    digitalWrite(CLOCK_PIN, 0);
    pinMode(ZERO_PIN, INPUT_PULLUP);
    for (int i = 0; i < NUM_CELLS; i++)
        pinMode(DOUT_PIN[i], INPUT);
    calibrate();

    Serial.println("All set.");
    StartTime = millis();
}

void loop()
{
    Time = millis();
    if (areReady())
    {
        read(Readings);
        sprintf(LineBuffer, "%10ld", Time - StartTime);
        for (int i = 0; i < NUM_CELLS; i++)
        {
            dtostrf((double)(Readings[i] - Offsets[i]) * SCALE_NEWTON[i], 10, 2, ValueBuffer);
            strcat(LineBuffer, ", ");
            strcat(LineBuffer, ValueBuffer);
        }
        Serial.println(LineBuffer);
    }

    if (digitalRead(ZERO_PIN) == 0)
        zeroAll();
}

void zeroAll()
{
    Serial.println("Zeroing all...");
    calibrate();
    Serial.println("Done.");
    StartTime = millis();
}

void read(long *_readings)
{
    for (int i = 0; i < NUM_CELLS; i++)
        _readings[i] = 0;
    for (int j = 0; j < 24; j++)
    {
        digitalWrite(CLOCK_PIN, 1);
        delayMicroseconds(1);
        digitalWrite(CLOCK_PIN, 0);
        for (int i = 0; i < NUM_CELLS; i++)
        {
            _readings[i] <<= 1;
            _readings[i] += digitalRead(DOUT_PIN[i]);
        }
    }
    digitalWrite(CLOCK_PIN, 1); // gain = 128, refer to HX711 datasheet
    delayMicroseconds(1);
    digitalWrite(CLOCK_PIN, 0);

    // sign extension 24 -> 32
    for (int i = 0; i < NUM_CELLS; i++)
        if (_readings[i] & 0x800000)
            _readings[i] |= 0xFF000000;
}

void calibrate(int _count)
{
    // get sum of each
    long _sums[NUM_CELLS] = {0};
    long _readings[NUM_CELLS];
    for (int i = 0; i < _count; i++)
    {
        while (!areReady())
            delay(1);
        read(_readings);
        for (int j = 0; j < NUM_CELLS; j++)
            _sums[j] += _readings[j];
    }
    // set offset for each
    for (int i = 0; i < NUM_CELLS; i++)
        Offsets[i] = _sums[i] / _count;
}

bool areReady() // refer to HX711 datasheet
{
    for (int i = 0; i < NUM_CELLS; i++)
        if (digitalRead(DOUT_PIN[i]))
            return 0;
    return 1;
}