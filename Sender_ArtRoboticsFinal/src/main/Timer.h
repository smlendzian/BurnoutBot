#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

class Timer
{
    private:

    //unsigned long is recommended for variables holding time and is the data type millis() returns
    unsigned long timeAtStartOfStage;

    public:

    Timer();

    unsigned long getTimeSinceStartOfStageInMilliseconds();

    void printTimeSinceStartOfStageToSerial();
};

#endif