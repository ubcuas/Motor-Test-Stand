/*
 * The code for UAS thrust test stand
 * Author: Charles Surianto
 */

#include <Arduino.h>
#include <Servo.h>

// #define DEBUGGING // uncomment to enable debugging

// constants
const int PWM_PIN = 11;                             //
const int NUM_CELLS = 6;                            //
const int ZERO_PIN = 12;                            // zero button pin, internally pulled up (active low)
const int CLOCK_PIN = 2;                            // common clock pin for all cells
const int DOUT_PIN[NUM_CELLS] = {3, 4, 5, 6, 7, 8}; // DOUT pins of each cell
const double SCALE_NEWTON[NUM_CELLS] = {
    // newton per readings (subject to change)
    4.63e-5, // cell 1
    4.52e-5, // cell 2
    4.77e-5, // cell 3
    4.64e-5, // cell 4
    4.64e-5, // cell 5
    4.75e-5  // cell 6
};

// global variables
unsigned long Time;            // holds current time in (ms)
unsigned long StartTime = 0;   // holds zero time
char SerialOutBuffer[300];     //
char ValueBuffer[20];          //
char SerialInBuffer[10];       //
long Readings[NUM_CELLS];      //
long Offsets[NUM_CELLS] = {0}; //
bool Run = 0;                  //

// prototypes
void zeroAll();
void read(long *);
void calibrate(int = 20);
bool areReady();

Servo MotorControl;

void setup()
{
    Serial.begin(115200);
    // Serial.println("Starting up...");

    MotorControl.attach(11, 500, 2500);
    MotorControl.writeMicroseconds(1000);

    pinMode(CLOCK_PIN, OUTPUT);
    digitalWrite(CLOCK_PIN, 0);

    pinMode(ZERO_PIN, INPUT_PULLUP);

    for (int i = 0; i < NUM_CELLS; i++)
        pinMode(DOUT_PIN[i], INPUT);

    zeroAll();

    // Serial.println("All set.");
    // Serial.println(" Time (ms), Cell 1 (N), Cell 2 (N), Cell 3 (N), Cell 4 (N), Cell 5 (N), Cell 6 (N)");
    // StartTime = millis();
}

void loop()
{
    if (Run)
    {
        Time = millis();
        if (areReady())
        {
            read(Readings);
            sprintf(SerialOutBuffer, "%ld", Time - StartTime);
            for (int i = 0; i < NUM_CELLS; i++)
            {
                dtostrf((double)(Readings[i] - Offsets[i]) * SCALE_NEWTON[i], 0, 2, ValueBuffer);
                strcat(SerialOutBuffer, ",");
                strcat(SerialOutBuffer, ValueBuffer);
            }
            Serial.println(SerialOutBuffer);
        }
    }
    else
    {
        delay(1);
    }

    if (Serial.available())
    {
        SerialInBuffer[0] = 0;

        int i;
        for (i = 0; Serial.available(); i++)
            SerialInBuffer[i] = Serial.read();
        SerialInBuffer[i] = 0;

        char command = SerialInBuffer[0];
        switch (command)
        {
        case 'C':
            zeroAll();
            break;
        case 'R':
            Run = 1;
            break;
        case 'S':
            Run = 0;
            break;
        case 'P':
            int value;
            sscanf(SerialInBuffer + 1, "%d", &value);
            if (value >= 500 && value <= 2500)
                MotorControl.writeMicroseconds(value);
#ifdef DEBUGGING
            Serial.println(value);
#endif
            break;
        default:
            break;
        }
    }
}

void zeroAll()
{
    // Serial.println("Zeroing all...");
    calibrate();
    // Serial.println("Done.");
    // Serial.println("\n Time (ms), Cell 1 (N), Cell 2 (N), Cell 3 (N), Cell 4 (N), Cell 5 (N), Cell 6 (N)");
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