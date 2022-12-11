#include "Stage.h"

Stage::Stage(String name_val, int initial_points, int final_points, bool should_start)
:name(name_val),
points(initial_points),
finishStagePoints(final_points),
limitSwitch("Limit Switch", LIMIT_SWITCH_PIN),
lcd(LCDrs, LCDen, LCDd4, LCDd5, LCDd6, LCDd7)
{
    lcd.begin(2, 16);
    lcd.setCursor(0, 0);
    lcd.print("Points: ");
    lcd.print(points);
    shouldReturnToDefaultStage = !should_start;
}

void Stage::Start()
{
    Serial.println(Name() + " Started");
    
    //Task continues until ShouldEndTask is changed to true.
    //Then the program will return to the MainMenu
    while(!ShouldEndStage && !shouldReturnToDefaultStage) 
    {
        //initialize();
        
        MP3::instance().AdjustVolumeAsRequested();
        MP3::instance().PlayBackgroundMusicIfIdle();
        analogRead(27); //fake pin for issue with reading multiple potentiometers with the esp32
        checkForLimitSwitchPress();
        checkIfRanOutOfTime();
        RunOutputs();
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

bool Stage::shouldNotReturnToDefaultStage()
{
    return !shouldReturnToDefaultStage;
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

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Points: ");
        lcd.print(points);

        timeAtLastSwitchPress = timer.getTimeSinceStartOfStageInMilliseconds();
        timer.printTimeSinceStartOfStageToSerial();
        warningHasBeenGiven = false;
    }

    if (points >= finishStagePoints)
    {
        ShouldEndStage = true; //Ends the loop in Stage::Start() to return to the MainMenu
    }
}

void Stage::checkIfRanOutOfTime()
{
    if (name != "DefaultStage")
    {
        unsigned long timeSinceLastSwitchPress = timer.getTimeSinceStartOfStageInMilliseconds() - timeAtLastSwitchPress;
        if (timeSinceLastSwitchPress >= MILLISECONDS_WITHOUT_INPUT_BEFORE_RETURN_TO_DEFAULT_STAGE)
        {
            Serial.print("TimeSinceLastSwitchPress(ms): ");
            Serial.println(timeSinceLastSwitchPress);
            Serial.println("Ran Out Of Time");
            shouldReturnToDefaultStage = true;
            ShouldEndStage = true;
        } 
        else if (timeSinceLastSwitchPress >= MILLISECONDS_WITHOUT_INPUT_BEFORE_WARNING)
        {
            if (!warningHasBeenGiven)
            {
                Serial.print("TimeSinceLastSwitchPress(ms): ");
                Serial.println(timeSinceLastSwitchPress);
                Serial.println("Keep Pushing Or Lose Your Points!");

                lcd.setCursor(0, 1);
                lcd.print("Keep Pushing!");

                MP3::instance().AdjustVolumeAsRequested();
                MP3::instance().Play(SPOKEN_TRACK_NUM);

                warningHasBeenGiven = true;
                //if statement to prevent sending the warning thousands of times
            }    
        }
    }
}

void Stage::initialize()
{
    lcd.begin(2, 16);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Points: ");
    lcd.print(points);
}