#include "Devices.h"

//Constructor function for a Device
Device::Device(String name_val, int port_num)
:name(name_val), //Assigns the value in name_val to name (line ends with a comma) (change to 0 if RAM conservation is needed)
port(port_num) //Assigns the value in port_num to port (line does not end with a comma because it is the last assignment in the list)
{

}

//Function belonging to the Device class that returns the name of the Device.
String Device::Name()
{
    return name;
}

DigitalSensor::DigitalSensor(String name_val, int port_num)
:Device(name_val, port_num) //Assigns the values for the variables that belong to the Device class that DigitalSensor is derived from
{
    pinMode(port, INPUT_PULLUP); //Initialize the sensor as input pullup.
}

long DigitalSensor::ReadInput()
{
    long input_reading = 0;

    input_reading = digitalRead(port);

    //For debugging:
    //Prints to the Serial Monitor the value of the sensor when the sensor value changes.
    if(input_reading != previous_reading)
    {
        //Serial.print(Name());
        //Serial.print(" Port: ");
        //Serial.print(port);
        //Serial.print(F(" val: "));
        //Serial.println(input_reading);

        previous_reading = input_reading;
    }

    return input_reading;
}

Button::Button(String name_val, int port_num, long initial_state_val)
:DigitalSensor(name_val, port_num)
{
    previous_reading = initial_state_val;
}

bool Button::RequestedButtonStateIsTrue(int state)
{
    //To account for debouncing, wait until after 5 consecutive readings of the requested button state.
    for(int count = 0; count < 5; ++count)
    {
        int reading = ReadInput();

        if(reading != state)
        {
            return false;
        }

        delay(1);     
    }
    return true;
}

bool Button::ButtonIsPressed()
{
    return RequestedButtonStateIsTrue(PRESSED);
}

bool Button::ButtonIsReleased()
{
    return RequestedButtonStateIsTrue(RELEASED);
}

bool Button::ButtonWasPressed()
{
    return previous_reading == PRESSED;
}

void Button::WaitForButtonState(int state)
{
    while(!RequestedButtonStateIsTrue(state));
}

void Button::WaitForButtonPressed()
{
    while(!ButtonIsPressed());
}

void Button::WaitForButtonReleased()
{
    while(!ButtonIsReleased());
}

void Button::WaitForButtonClick()
{
    WaitForButtonPressed();
    WaitForButtonReleased();
}

AnalogSensor::AnalogSensor(String name_val, int port_num)
:Device(name_val, port_num)
{
    pinMode(port, INPUT); 
}

long AnalogSensor::ReadInput()
{
    long input_reading = analogRead(port);
    long reading_change = input_reading - previous_reading;

    //For debugging:
    //Prints to the Serial Monitor the value of the sensor when the sensor value changes a significant amount
    if(abs(reading_change) > 1000)
    {
        Serial.print(Name());
        Serial.print(F(" Port: "));
        Serial.print(port);
        Serial.print(F(" val: "));
        Serial.println(input_reading);

        previous_reading = input_reading;
    }

    return input_reading;
}

Potentiometer::Potentiometer(String name_val, int port_num, int output_lowest_val, int output_highest_val)
:AnalogSensor(name_val, port_num),
output_lowest_value(output_lowest_val),
output_highest_value(output_highest_val)
{
    
}

int Potentiometer::ReadPotentiometerAndConvertToOutputValues()
{
    long input_reading = ReadInput();

    //The potentiometer returns values between 0 and 4095 (when used with an ESP32)
    int output_value = map(input_reading, 0, 4095, output_lowest_value, output_highest_value);

    /*Serial.print("Input from ");
    Serial.print(name);
    Serial.print(": ");
    Serial.println(input_reading);
    
    Serial.print("Output from ");
    Serial.print(name);
    Serial.print(": ");
    Serial.println(output_value);*/

    return output_value;
}

DCMotor::DCMotor(String name_val, int port_num)
:Device(name_val, port_num),
motor_is_running(false)
{
    pinMode(port, OUTPUT); 
}

void DCMotor::startMotor()
{
    digitalWrite(port, HIGH);
    timeMotorStarted = timer.getTimeSinceStartOfStageInMilliseconds();
    Serial.print(name);
    Serial.println(": MotorStartedRunning");
    motor_is_running = true;
}

void DCMotor::stopMotorIfEnoughTimeHasPassed(unsigned long millisecondsMotorShouldRun)
{
    unsigned long currentTime = timer.getTimeSinceStartOfStageInMilliseconds();
    if (currentTime - timeMotorStarted > millisecondsMotorShouldRun)
    {
        digitalWrite(port, LOW);
        Serial.print(name);
        Serial.println(": MotorStoppedRunning");
        motor_is_running = false;
    }
}

bool DCMotor::motorIsRunning()
{
    return motor_is_running;
}