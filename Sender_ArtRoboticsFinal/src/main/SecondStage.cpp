#include "SecondStage.h"

SecondStage::SecondStage(bool should_start)
:Stage("SecondStage", 11, 15, should_start)
{
    //Everything in this constructor is carried out when an instance of the DefaultStage class is created.
}

void SecondStage::RunOutputs()
{
    //Serial.println("Second Stage Outputs");
}
