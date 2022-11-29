#ifndef SecondStage_h
#define SecondStage_h

#include "Stage.h"

class SecondStage : public Stage
{
    NeutralLEDFace ledFace;
    public:

    SecondStage(bool should_start);

    virtual void RunOutputs();
};

#endif