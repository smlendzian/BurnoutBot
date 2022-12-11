#ifndef FirstStage_h
#define FirstStage_h

#include "Stage.h"

class FirstStage : public Stage
{
    HappyLEDFace ledFace;
    public:

    FirstStage();

    virtual void RunOutputs();
};

#endif