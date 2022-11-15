#ifndef FirstStage_h
#define FirstStage_h

#include "Stage.h"

class FirstStage : public Stage
{
    public:

    FirstStage();

    //Keeps checking whether the limit switch is pressed, increases points appropriately
    //Ends when points = 10
    virtual void Run();
};

#endif