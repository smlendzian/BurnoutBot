#include "FirstStage.h"

FirstStage::FirstStage()
:Stage("FirstStage", 1, 10)
{
    //Everything in this constructor is carried out when an instance of the DefaultStage class is created.
}

void FirstStage::RunOutputs()
{
    ledFace.draw();
}
