#include "DefaultStage.h"

DefaultStage::DefaultStage()
:Stage("DefaultStage")
{
    //Everything in this constructor is carried out when an instance of the DefaultStage class is created.
}

void DefaultStage::Run()
{
    while(!ShouldEndStage) //Loop is redundant but used for clarity
    {
        if(limitSwitch.isPressed())
        {
            Serial.println("Limit Switch Pressed");

            ShouldEndStage = true; //Ends the loop in Stage::Start() to return to the MainMenu
        }

    }
}