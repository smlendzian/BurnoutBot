#include "MainMenu.h"

MainMenu::MainMenu()
{
    
}

void MainMenu::Start()
{
    Serial.println("MainMenu Start");

    DefaultStage defaultStage;
    defaultStage.Start();
    Serial.println("Default Stage Ended");
}