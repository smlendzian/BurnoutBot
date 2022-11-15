#include "Stage.h"

Stage::Stage(String name_val, int initial_points, int final_points)
:name(name_val),
points(initial_points),
finishStagePoints(final_points),
limitSwitch("Limit Switch", LIMIT_SWITCH_PIN)
{
    
}

void Stage::Start()
{
    Serial.println(Name() + " Started");
    
    //Task continues until ShouldEndTask is changed to true.
    //Then the program will return to the MainMenu
    while(!ShouldEndStage) 
    {
        Run();
    } 
}

String Stage::Name()
{
    return name;
}

int Stage::getCurrentPoints()
{
    return points;
}

void Stage::checkForLimitSwitchPress()
{
    //Check whether the limit switch was not pressed before but is pressed now.
    //both must be called, so call outside of if statement
    bool wasPressed = limitSwitch.ButtonWasPressed();
    bool isPressed = limitSwitch.ButtonIsPressed();
    if(!wasPressed && isPressed)
    //Checks the previous reading variable, and then does a new reading
    //(changing that variable, so the order of this if statement is important)
    {
        Serial.print(limitSwitch.Name());
        Serial.println(" WasPressed");
        points++;
        Serial.print("Current Points: ");
        Serial.println(points);
    }

    if (points >= finishStagePoints)
    {
        ShouldEndStage = true; //Ends the loop in Stage::Start() to return to the MainMenu
    }
}
