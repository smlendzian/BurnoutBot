#ifndef MainMenu_h
#define MainMenu_h

#include <Arduino.h>
#include "DefaultStage.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"
#include "FourthStage.h"

//The MainMenu class is used to cycle through each of the stages
class MainMenu
{
    private:

    int points = 0;
    
    public:

    MainMenu();

    //Cycles through all the stages based on inputs
    void Start();
};

#endif