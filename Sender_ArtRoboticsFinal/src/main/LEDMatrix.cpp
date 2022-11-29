#include "LEDMatrix.h"

LEDMatrix* LEDMatrix::gInstance = nullptr;

LEDMatrix::LEDMatrix()
:Device("LEDMatrix", LED_MATRIX_INPUT_PIN),
potentiometer("LEDMatrixPotentiometer", LED_MATRIX_POT_PIN, 0, 255)
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        leds[i] = CRGB::Black;
    }
    FastLED.addLeds<WS2811, LED_MATRIX_INPUT_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    setBrightnessBasedOnPotVal();
}

LEDMatrix& LEDMatrix::instance()
{
    if (gInstance == nullptr)
    {
        gInstance = new LEDMatrix();
    }

    return *gInstance;
}

int LEDMatrix::convertToLEDIndex(int x, int y)
{
    int index;
    if (x % 2 == 0) //checks if x is even
    {
        index = NUM_LEDS_HEIGHT * (x + 1) - y - 1;
    }
    else
    {
        index = NUM_LEDS_HEIGHT * x + y;
    }
    return index;
}

void LEDMatrix::setPixelColor(int x, int y, CRGB::HTMLColorCode color)
{
    if ((x >= 0 && x < NUM_LEDS_WIDTH) && (y >= 0 && y < NUM_LEDS_HEIGHT))
    {
        leds[convertToLEDIndex(x, y)] = color;
    }   
    /*Serial.print("x: ");
    Serial.print(x);
    Serial.print(", y: ");
    Serial.print(y);
    Serial.print(", color: ");
    Serial.println(color);
    Serial.print("LEDIndex: ");
    Serial.println(convertToLEDIndex(x, y));*/
}

void LEDMatrix::setBrightnessBasedOnPotVal()
{
    FastLED.setBrightness(potentiometer.ReadPotentiometerAndConvertToOutputValues());
}

void LEDMatrix::show()
{
    //Serial.println("LEDMatrix show() called");
    setBrightnessBasedOnPotVal();
    FastLED.show();
    //Serial.println("LEDMatrix show() finished");
}