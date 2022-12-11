#ifndef Devices_h
#define Devices_h

#include <Arduino.h>
#include "Timer.h"

#define LIMIT_SWITCH_PIN 12
#define LED_MATRIX_INPUT_PIN 5
#define LED_MATRIX_POT_PIN 34
#define SPEAKER_POT_PIN 14
#define mp3TXPort 25
#define mp3RXPort 26
#define PUMP_MOTOR_PIN 32

const int LCDrs = 19, LCDen = 23, LCDd4 = 18, LCDd5 = 17, LCDd6 = 16, LCDd7 = 15; //LCD pins

//Class definition of a Device:
class Device
{
    //Protected means that only this class or classes derived from it can use these.
    protected:
    int port; //Address of the port in the microcontroller
    String name; //Name used for logging/debugging

    //Public means any other class can use these.
    public:
    //Creates a Device with the specified port number and the name given to it.
    //(The name is to be used when writing to the Serial Monitor for debugging.)
    //The variables here must have different names than the ones that belong to the class.
    Device(String name_val, int port_num = 0);

    String Name(); //This function returns the name of the Device for debugging purposes.
};

//A DigitalSensor is derived from the Device class.
//This means that a DigitialSensor is a type of Device.
//A DigitalSensor is a type of Device that can read digital input and can be connected to the microcontroller.
class DigitalSensor : public Device
{
    protected:
    long previous_reading = 0;

    public:
    //Creates a DigitalSensor.
    DigitalSensor(String name_val, int port_num);

    //Reads the input of the DigitalSensor
    long ReadInput();
};

//A Button is a type of DigitalSensor with PRESSED (LOW) and RELEASED (HIGH) states
//(Can be used with buttons, limit switches, etc.)
class Button : public DigitalSensor
{
    protected:
    enum ButtonStateEnum
    {
        PRESSED = 0,
        RELEASED = 1
    };

    public:
    Button(String name_val, int port_num, long initial_state_val = RELEASED);
    //initial_state_val will normally not be specified (default parameter), 
    //but should fill with PRESSED if the initial state is PRESSED

    bool RequestedButtonStateIsTrue(int state); //Used to account for debouncing.
    bool ButtonIsPressed();
    bool ButtonIsReleased();

    //Use to check whether the button was previously pressed when
    //whether the button changed state from pressed to released/released to pressed must be determined.
    bool ButtonWasPressed();
    
    void WaitForButtonState(int state); //Used to account for debouncing.
    void WaitForButtonPressed();
    void WaitForButtonReleased();
    void WaitForButtonClick(); //A "Click" is both a press and a release.
};

class AnalogSensor : public Device
{
    protected:
    int port_location;
    long previous_reading = 0;
    
    public:
    AnalogSensor(String name_val, int port_num);

    long ReadInput();
};

class Potentiometer : public AnalogSensor
{
    int output_lowest_value, output_highest_value;
    
    public:
    Potentiometer(String name_val, int port_num, int output_lowest_val, int output_highest_val);
    int ReadPotentiometerAndConvertToOutputValues();
};

class DCMotor : public Device
{
    Timer timer;
    unsigned long timeMotorStarted;
    bool motor_is_running;
    
    public:

    DCMotor(String name_val, int port_num);

    void startMotor();
    void stopMotorIfEnoughTimeHasPassed(unsigned long millisecondsMotorShouldRun);
    bool motorIsRunning();
};

#endif
