#include "FourthStage.h"

FourthStage::FourthStage(bool should_start)
:Stage("FourthStage", 20, INT_MAX, should_start),
pumpMotor("PumpMotor", PUMP_MOTOR_PIN),
pointsWhenMotorLastRan(20)
{
    //Everything in this constructor is carried out when an instance of the DefaultStage class is created.
}

void FourthStage::RunOutputs()
{
    ledFace.draw();

    if ((points - pointsWhenMotorLastRan == 5) && !pumpMotor.motorIsRunning())
    {
        pumpMotor.startMotor();
        pointsWhenMotorLastRan = points;
    }

    if (pumpMotor.motorIsRunning())
    {
        pumpMotor.stopMotorIfEnoughTimeHasPassed(500);
        if (!pumpMotor.motorIsRunning())
        {
            initialize(); //resets devices as needed because of complications (probably power use) from using the motor
        }
    }
}
