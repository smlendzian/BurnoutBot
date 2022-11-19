#ifndef SecondStage_h
#define SecondStage_h

#include "Stage.h"

class SecondStage : public Stage
{
    public:

    SecondStage(bool should_start);

    virtual void RunOutputs();
};

#endif