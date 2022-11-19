#include "Timer.h"

Timer::Timer()
{
    timeAtStartOfStage = millis();
}

unsigned long Timer::getTimeSinceStartOfStageInMilliseconds()
{
    return millis() - timeAtStartOfStage;
}

void Timer::printTimeSinceStartOfStageToSerial()
{
    Serial.print("Time Since Start Of Stage: ");
    Serial.print(getTimeSinceStartOfStageInMilliseconds());
    Serial.println(" milliseconds");
}