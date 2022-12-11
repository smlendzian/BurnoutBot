#ifndef LEDFace_h
#define LEDFace_h

#include <Arduino.h>
#include "LEDMatrix.h"
#include <vector>
#include "Timer.h"

class LEDFaceObject
{
    protected:
    int xCoordinate, yCoordinate; //coordinate of the bottom left corner of the object
    //a vector of vectors is used because the size of a vector can be changed (unlike an array)
    std::vector<std::vector<CRGB::HTMLColorCode>> pixels; //inner vector is x, outer vector is y   

    public:
    
    LEDFaceObject(int x_val, int y_val);

    void draw() const;
    //const for a method tells the client that you will not change any data members of the class
};

class LEDFaceMovingObject : public LEDFaceObject
{
    int xCoordinateFinal, yCoordinateFinal, xCoordinateInitial, yCoordinateInitial;
    unsigned long millisecondsForMovement, timeSpawned;
    float pixelsPerMillisecondX, pixelsPerMillisecondY;
    Timer timer;
    public:
    LEDFaceMovingObject(int x_val, int y_val, int x_val_final, int y_val_final, unsigned long milliseconds_for_movement);
    void move();
};

class Nose : public LEDFaceObject
{
    public:
    Nose();
};

class EyesOpenWithNose : public LEDFaceObject
{
    public:
    EyesOpenWithNose();   
};

class EyesClosedWithNose : public LEDFaceObject
{
    public:
    EyesClosedWithNose(); 
};

class NeutralMouth : public LEDFaceObject
{
    public:
    NeutralMouth();
};

class HappyMouth : public LEDFaceObject
{
    public:
    HappyMouth();
};

class SadMouth : public LEDFaceObject
{
    public:
    SadMouth();
};

class CryingMouth : public LEDFaceObject
{
    public:
    CryingMouth();
};

class Tear : public LEDFaceMovingObject
{
    public:
    Tear();
};

class TearTwo : public LEDFaceMovingObject
{
    public:
    TearTwo();
};

class LEDFace
{
    protected:
    Timer timer;

    public:

    LEDFace();
    virtual void draw() = 0;
};

class NonCryingLEDFace : public LEDFace
{
    protected:
    EyesOpenWithNose openEye;
    EyesClosedWithNose closedEye;
    unsigned long timeLastClosedEyes;
    void drawEyes();

    public:
    NonCryingLEDFace();
    virtual void draw() = 0;
};

class NeutralLEDFace : public NonCryingLEDFace
{
    NeutralMouth mouth;
    public:
    NeutralLEDFace();
    virtual void draw();
};

class HappyLEDFace : public NonCryingLEDFace
{
    HappyMouth mouth;
    public:
    HappyLEDFace();
    virtual void draw();
};

class SadLEDFace : public NonCryingLEDFace
{
    SadMouth mouth;
    public:
    SadLEDFace();
    virtual void draw();
};

class CryingLEDFace : public LEDFace
{
    protected:
    EyesClosedWithNose eyes;
    CryingMouth mouth;
    Tear tear;
    TearTwo otherTear;

    public:
    CryingLEDFace();
    virtual void draw();
};

#endif
