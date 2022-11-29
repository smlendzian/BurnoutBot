#include "LEDFace.h"

LEDFaceObject::LEDFaceObject(int x_val, int y_val)
:xCoordinate(x_val),
yCoordinate(y_val)
{
    
}

void LEDFaceObject::draw() const
{
    //Serial.println("LEDFaceObject draw() called");
    for (int y = 0; y < pixels.size(); ++y)
    {
        const std::vector<CRGB::HTMLColorCode>& row = pixels[y];
        for (int x = 0; x < row.size(); ++x)
        {
            LEDMatrix::instance().setPixelColor(x + xCoordinate, y + yCoordinate, pixels[y][x]);
        }
    }
    LEDMatrix::instance().show();
    //Serial.println("draw() finished");
}

LEDFaceMovingObject::LEDFaceMovingObject(int x_val, int y_val, int x_val_final, int y_val_final, unsigned long milliseconds_for_movement)
:LEDFaceObject(x_val, y_val),
xCoordinateFinal(x_val_final),
yCoordinateFinal(y_val_final),
millisecondsForMovement(milliseconds_for_movement),
xCoordinateInitial(x_val),
yCoordinateInitial(y_val)
{
    timeSpawned = timer.getTimeSinceStartOfStageInMilliseconds();
    pixelsPerMillisecondX = float(xCoordinateFinal - xCoordinateInitial) / millisecondsForMovement;
    pixelsPerMillisecondY = float(yCoordinateFinal - yCoordinateInitial) / millisecondsForMovement;
    Serial.print("pixelsPerMillisecondX: ");
    Serial.println(pixelsPerMillisecondX);
    Serial.print("pixelsPerMillisecondY: ");
    Serial.println(pixelsPerMillisecondY);
}

void LEDFaceMovingObject::move()
{
    draw();
    unsigned long timeSinceSpawned = timer.getTimeSinceStartOfStageInMilliseconds() - timeSpawned;
    xCoordinate = xCoordinateInitial + timeSinceSpawned * pixelsPerMillisecondX;
    yCoordinate = yCoordinateInitial + timeSinceSpawned * pixelsPerMillisecondY;
    if (xCoordinate == xCoordinateFinal && yCoordinate == yCoordinateFinal)
    {
        xCoordinate = xCoordinateInitial;
        yCoordinate = yCoordinateInitial;
        timeSpawned = timer.getTimeSinceStartOfStageInMilliseconds();
    }
}

Nose::Nose()
:LEDFaceObject(7, 7)
{
    pixels = std::vector<std::vector<CRGB::HTMLColorCode>>
    {
        {CRGB::Gray, CRGB::Gray, CRGB::Black},
        {CRGB::Black, CRGB::Black, CRGB::Gray},
        {CRGB::Black, CRGB::Gray, CRGB::Black},
        {CRGB::Gray, CRGB::Black, CRGB::Black}
    };
    Serial.println("Nose created");
}

EyesOpenWithNose::EyesOpenWithNose()
:LEDFaceObject(1, 7)
{
    pixels = std::vector<std::vector<CRGB::HTMLColorCode>>
    {
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
          CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },

        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
          CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },

        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
          CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },

        { CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White,
          CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black },

        { CRGB::White, CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::White, CRGB::Black, CRGB::Black,
          CRGB::Black, CRGB::Black, CRGB::White, CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::White },

        { CRGB::White, CRGB::Blue, CRGB::Black, CRGB::Blue, CRGB::White, CRGB::Black, CRGB::Black,
          CRGB::Black, CRGB::Black, CRGB::White, CRGB::Blue, CRGB::Black, CRGB::Blue, CRGB::White },

        { CRGB::White, CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::White, CRGB::Black, CRGB::Black,
          CRGB::Black, CRGB::Black, CRGB::White, CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::White },

        { CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black,
          CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black }
    };
}

EyesClosedWithNose::EyesClosedWithNose()
:LEDFaceObject(1, 7)
{
    pixels = std::vector<std::vector<CRGB::HTMLColorCode>>
    {
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
          CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },

        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
          CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },

        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
          CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },

        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
          CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },

        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
          CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },

        { CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black,
          CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White },

        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
          CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },

        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
          CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black }
    };
}

NeutralMouth::NeutralMouth()
:LEDFaceObject(1, 0)
{
    pixels = std::vector<std::vector<CRGB::HTMLColorCode>>
    {
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black  },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black  },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black  },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black  },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black  },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black  },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black  }
    };
}

HappyMouth::HappyMouth()
:LEDFaceObject(3, 1)
{
    pixels = std::vector<std::vector<CRGB::HTMLColorCode>>
    {
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
        { CRGB::Black, CRGB::Black, CRGB::MediumVioletRed, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black },
        { CRGB::Black, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::Black },
        { CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed }
    };
}

SadMouth::SadMouth()
:LEDFaceObject(3, 0)
{
    pixels = std::vector<std::vector<CRGB::HTMLColorCode>>
    {
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },
        { CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black },
        { CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black }
    };
}

CryingMouth::CryingMouth()
:LEDFaceObject(1, 0)
{
    pixels = std::vector<std::vector<CRGB::HTMLColorCode>>
    {
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black  },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::Black, CRGB::Black, CRGB::Black },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::MediumVioletRed, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black },
        { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black }
    };
}

Tear::Tear()
:LEDFaceMovingObject(1, 8, 1, -5, 5000)
{
    pixels = std::vector<std::vector<CRGB::HTMLColorCode>>
    {
        { CRGB::Black, CRGB::Blue, CRGB::Black },
        { CRGB::Blue, CRGB::Blue, CRGB::Blue },
        { CRGB::Blue, CRGB::Blue, CRGB::Black },
        { CRGB::Black, CRGB::Blue, CRGB::Black }
    };   
}

TearTwo::TearTwo()
:LEDFaceMovingObject(12, 8, 12, -5, 5000)
{
    pixels = std::vector<std::vector<CRGB::HTMLColorCode>>
    {
        { CRGB::Black, CRGB::Blue, CRGB::Black },
        { CRGB::Blue, CRGB::Blue, CRGB::Blue },
        { CRGB::Blue, CRGB::Blue, CRGB::Black },
        { CRGB::Black, CRGB::Blue, CRGB::Black }
    };   
}

LEDFace::LEDFace()
{
    
}

NonCryingLEDFace::NonCryingLEDFace()
{
    closedEye.draw();
    timeLastClosedEyes = timer.getTimeSinceStartOfStageInMilliseconds();
}

void NonCryingLEDFace::drawEyes()
{
    unsigned long currentTime = timer.getTimeSinceStartOfStageInMilliseconds();
    if (currentTime - timeLastClosedEyes > 4000)
    {
        closedEye.draw();
        timeLastClosedEyes = timer.getTimeSinceStartOfStageInMilliseconds();
    }
    else if (currentTime - timeLastClosedEyes > 1000)
    {
        openEye.draw();
    }
}

NeutralLEDFace::NeutralLEDFace()
{

}

void NeutralLEDFace::draw()
{
    drawEyes();
    mouth.draw();
}

HappyLEDFace::HappyLEDFace()
{

}

void HappyLEDFace::draw()
{
    drawEyes();
    mouth.draw();
}

SadLEDFace::SadLEDFace()
{

}

void SadLEDFace::draw()
{
    drawEyes();
    mouth.draw();
}

CryingLEDFace::CryingLEDFace()
{

}

void CryingLEDFace::draw()
{
    mouth.draw();
    eyes.draw();
    tear.move();
    otherTear.move();
}
