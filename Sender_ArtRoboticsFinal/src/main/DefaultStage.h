#ifndef DefaultStage_h
#define DefaultStage_h

#include "Stage.h"

//DefaultStage is the type of Stage that contains the initial states of the game
class DefaultStage : public Stage
{
    public:

    DefaultStage();

    virtual void RunOutputs();
};

#endif