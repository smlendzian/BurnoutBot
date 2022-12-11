#ifndef FourthStage_h
#define FourthStage_h

#include "Stage.h"

class FourthStage : public Stage
{
    CryingLEDFace ledFace;
    DCMotor pumpMotor;
    int pointsWhenMotorLastRan;
    public:

    FourthStage(bool should_start);

    virtual void RunOutputs();
};

#endif