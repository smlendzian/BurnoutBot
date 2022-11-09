#ifndef DefaultStage_h
#define DefaultStage_h

#include "Stage.h"

//DefaultStage is the type of Stage that contains the initial states of the game
class DefaultStage : public Stage
{
    public:

    DefaultStage();

    //Keeps checking whether the limit switch is pressed and sets everything to its initial state
    virtual void Run();
};

#endif