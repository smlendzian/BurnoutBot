#include "ThirdStage.h"

ThirdStage::ThirdStage(bool should_start)
:Stage("ThirdStage", 15, 20, should_start)
{
    //Everything in this constructor is carried out when an instance of the DefaultStage class is created.
}

void ThirdStage::RunOutputs()
{
    ledFace.draw();
}
