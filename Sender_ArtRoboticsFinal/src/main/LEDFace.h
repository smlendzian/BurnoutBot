#ifndef LEDFace_h
#define LEDFace_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Devices.h"

//A LEDFace is a type of Device that contains and controls the NeoPixels in the Face
class LEDFace : public Device
{
    private:
    int inputPort, outputPort;

    public:

    LEDFace();

};



#endif
