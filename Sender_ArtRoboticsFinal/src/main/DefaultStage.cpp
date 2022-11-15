#include "DefaultStage.h"

DefaultStage::DefaultStage()
:Stage("DefaultStage", 0, 1)
{
    //Everything in this constructor is carried out when an instance of the DefaultStage class is created.
}

void DefaultStage::Run()
{
    while(!ShouldEndStage) //Loop is redundant but used for clarity
    {
        checkForLimitSwitchPress();
    }
}
