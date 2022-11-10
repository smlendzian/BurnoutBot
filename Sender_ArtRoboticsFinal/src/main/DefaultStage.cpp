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
        //Check whether the limit switch was not pressed before but is pressed now.
        if(!limitSwitch.ButtonWasPressed() && limitSwitch.ButtonIsPressed())
        //Checks the previous reading variable, and then does a new reading
        //(changing that variable, so the order of this if statement is important)
        {
            Serial.print(limitSwitch.Name());
            Serial.println(" WasPressed");
            ShouldEndStage = true; //Ends the loop in Stage::Start() to return to the MainMenu
        }
    }
}
