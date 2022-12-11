#ifndef Stage_h
#define Stage_h

#include <Arduino.h>
#include "Devices.h"
#include "Timer.h"
#include "LEDFace.h"
#include <LiquidCrystal.h>
#include "MP3.h"

#define MILLISECONDS_WITHOUT_INPUT_BEFORE_RETURN_TO_DEFAULT_STAGE 15000
#define MILLISECONDS_WITHOUT_INPUT_BEFORE_WARNING 5000

//Write this comment later
class Stage
{
    protected:
    bool ShouldEndStage = false; //Used to determine whether to return to the MainMenu
    bool shouldReturnToDefaultStage = false;
    bool warningHasBeenGiven = false;
    unsigned long timeAtLastSwitchPress = 0;

    String name;
    int points; //points will be decided for each stage
    int finishStagePoints; //points needed to end the stage--determined for each stage 

    public:

    Stage(String name_val, int initial_points, int final_points, bool should_start = true); 
    //Stage is given a name for debugging purposes.
    //bool should_start = true uses a default parameter--so it will default to true if the value of the parameter is not specified

    Button limitSwitch;

    LiquidCrystal lcd;

    Timer timer;

    //Starts the Stage and runs it until ShouldEndStage becomes true.
    void Start();
    
    //Used in each Stage for handling the outputs/responses to the inputs
    //(virtual void means that every class derived from the Stage class will have the Run() function,
    //but that function will be different for every derived class.)
    virtual void RunOutputs() = 0;

    String Name();

    int getCurrentPoints();
    bool shouldNotReturnToDefaultStage();

    //checks for a limit switch press, updates points accordingly, and sets ShouldEndStage to true if finishStagePoints is met
    void checkForLimitSwitchPress();
    void checkIfRanOutOfTime();
    void initialize();
};

#endif