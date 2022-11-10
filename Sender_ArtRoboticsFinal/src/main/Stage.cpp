#include "Stage.h"

Stage::Stage(String name_val)
:name(name_val),
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
