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

    FirstStage firstStage;
    firstStage.Start();
    Serial.print("First Stage Ended. Current Points: ");
    points = firstStage.getCurrentPoints();
    Serial.println(points);

    SecondStage secondStage(firstStage.shouldNotReturnToDefaultStage());
    secondStage.Start();
    Serial.print("Second Stage Ended. Current Points: ");
    points = secondStage.getCurrentPoints();
    Serial.println(points);
}