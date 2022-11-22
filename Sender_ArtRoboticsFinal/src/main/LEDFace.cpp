#include "LEDFace.h"

LEDFace::LEDFace()
:Device("LEDFace", LED_FACE_INPUT_PIN),
inputPort(LED_FACE_INPUT_PIN),
outputPort(LED_FACE_OUTPUT_PIN)
{
    
}

