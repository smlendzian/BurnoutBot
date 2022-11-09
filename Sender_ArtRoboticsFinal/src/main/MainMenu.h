#ifndef MainMenu_h
#define MainMenu_h

#include <Arduino.h>
#include "DefaultStage.h"

//The MainMenu class is used to cycle through each of the stages
class MainMenu
{
    public:

    MainMenu();

    //Cycles through all the stages based on inputs
    void Start();
};

#endif