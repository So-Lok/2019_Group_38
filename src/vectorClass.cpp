// vectorClass.cpp

#include "vectorClass.h"

vectorClass::vectorClass()
{

}

vectorClass::vectorClass(int vectorIdIn, float xCoordIn, float yCoordIn, float zCoordIn)
{
    this->vectorId = vectorIdIn;
    this->xCoord = xCoordIn;
    this->yCoord = yCoordIn;
    this->zCoord = zCoordIn;
}

vectorClass::~vectorClass(){}

// get functions

int vectorClass::getId()
{
    return this->vectorId;
}

float vectorClass::getX()
{
    return this->xCoord;

}

float vectorClass::getY()
{
    return this->yCoord;
}

float vectorClass::getZ()
{
    return this->zCoord;
}

