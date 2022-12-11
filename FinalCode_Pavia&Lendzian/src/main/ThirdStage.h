#ifndef ThirdStage_h
#define ThirdStage_h

#include "Stage.h"

class ThirdStage : public Stage
{
    SadLEDFace ledFace;
    public:

    ThirdStage(bool should_start);

    virtual void RunOutputs();
};

#endif