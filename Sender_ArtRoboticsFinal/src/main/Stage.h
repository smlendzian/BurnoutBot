#ifndef Stage_h
#define Stage_h

#include <Arduino.h>
#include <ezButton.h>

#define LIMIT_SWITCH_PIN 2

//Write this comment later
class Stage
{
    protected:
    bool ShouldEndStage = false; //Used to determine whether to return to the MainMenu
    String name;
    int points; //points will be decided for each stage

    public:

    Stage(String name_val); //Stage is given a name for debugging purposes.

    ezButton limitSwitch;

    //Starts the Stage and runs it until ShouldEndStage becomes true.
    void Start();
    
    //Used in each Stage for handling checking each input and the outputs/responses to the inputs
    //(virtual void means that every class derived from the Stage class will have the Run() function,
    //but that function will be different for every derived class.)
    virtual void Run() = 0;

    String Name();

    int getCurrentPoints();
};

#endif