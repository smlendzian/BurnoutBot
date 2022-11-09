#include <Arduino.h>
#include "MainMenu.h"

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial Monitor Started");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  Serial.println("Main Started");

  //Create an instance of the MainMenu class
  MainMenu menu;
  Serial.println("MainMenuCreated");

  //Start the MainMenu
  menu.Start();
}
