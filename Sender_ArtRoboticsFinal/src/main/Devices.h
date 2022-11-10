#ifndef Devices_h
#define Devices_h

#include <Arduino.h>

#define LIMIT_SWITCH_PIN 12

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

#endif
