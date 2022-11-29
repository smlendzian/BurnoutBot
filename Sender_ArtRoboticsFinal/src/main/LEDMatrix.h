#ifndef LEDMatrix_h
#define LEDMatrix_h

#include <Arduino.h>
#include "Devices.h"
#include <FastLED.h>

#define NUM_LEDS_WIDTH 16
#define NUM_LEDS_HEIGHT 16
#define NUM_LEDS NUM_LEDS_WIDTH * NUM_LEDS_HEIGHT

//LEDMatrix fills the FastLED CRBG led array based on given 2D coordinate information
//The LEDMatrix is a Singleton class, which ensures there is only one object of this class
class LEDMatrix : public Device
{
    private:
    int inputPort;
    CRGB leds[NUM_LEDS];
    Potentiometer potentiometer;

    static LEDMatrix* gInstance;

    int convertToLEDIndex(int x, int y);

    LEDMatrix();

    public:

    static LEDMatrix& instance();

    void setBrightnessBasedOnPotVal(); 
    void setPixelColor(int x, int y, CRGB::HTMLColorCode color); //(0, 0) is in the bottom left corner
    void show(); 
};


#endif
