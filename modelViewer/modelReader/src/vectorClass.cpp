
// vectorClass.cpp
=======
/**
* @file vectorClass.cpp
* @brief definitions of all functions declared in vectorClass.cpp
*/


#include "vectorClass.h"

#include <math.h>

// constructor
vectorClass::vectorClass(){}
// override constructor
vectorClass::vectorClass(int vectorIdIn, float xCoordIn, float yCoordIn, float zCoordIn)
{
    this->vectorId = vectorIdIn;
    this->xCoord = xCoordIn;
    this->yCoord = yCoordIn;
    this->zCoord = zCoordIn;
}
// destructor
vectorClass::~vectorClass(){}

/* Get Functions */

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



/* Set Functions */

void vectorClass::setId(int IdToSet)
{
    this->vectorId = IdToSet;
}

void vectorClass::setX(float newX)
{
    this->xCoord = newX;
}

void vectorClass::setY(float newY)
{
    this->yCoord = newY;
}

void vectorClass::setZ(float newZ)
{
    this->zCoord = newZ;
}

void vectorClass::setAll(int IdToSet, float newX, float newY, float newZ)
{
    this->vectorId = IdToSet;
    this->xCoord = newX;
    this->yCoord = newY;
    this->zCoord = newZ;
}

// Dot/Scalar product
float vectorClass::scalarProduct(vectorClass& vec1, vectorClass& vec2)
{
    float result;

    result = ( ( vec1.getX() * vec2.getX() ) +
               ( vec1.getY() * vec2.getY() ) +
               ( vec1.getZ() * vec2.getZ() ) );

    return result;

}

// Cross/Vector Product
vectorClass vectorClass::vectorProduct(vectorClass& vec1, vectorClass& vec2)
{
    vectorClass result;

    result.setX( ( vec1.getY() * vec2.getZ() ) - ( vec2.getY() * vec1.getZ() ) );
    result.setY( ( vec1.getZ() * vec2.getX() ) - ( vec2.getZ() * vec1.getX() ) );
    result.setZ( ( vec1.getX() * vec2.getY() ) - ( vec2.getX() * vec1.getY() ) );

    return result;

}

//adding vector
vectorClass vectorClass::operator+(const vectorClass& vec2)
{
	vectorClass result; //create a vectorClass function to store the result

	result.setX(this->xCoord + vec2.xCoord); //calculate and set to the x coordinate
	result.setY(this->yCoord + vec2.yCoord); //calculate and set to the y coordinate
	result.setZ(this->zCoord + vec2.zCoord); //calculate and set to the z coordinate

	return result; //return the result in the require format
}

//subtracting vector
vectorClass vectorClass::operator-(const vectorClass& vec2)
{
	vectorClass result; //create a vectorClass function to store the result

	result.setX(this->xCoord - vec2.xCoord); //calculate and set to the x coordinate
	result.setY(this->yCoord - vec2.yCoord); //calculate and set to the y coordinate
	result.setZ(this->zCoord - vec2.zCoord); //calculate and set to the z coordinate

	return result; //return the result in the require format
}
// equal
vectorClass& vectorClass::operator=(const vectorClass &vec2)
{
    vectorId = vec2.vectorId;
    xCoord = vec2.xCoord;
    yCoord = vec2.yCoord;
    zCoord = vec2.zCoord;
    //result.setAll(vec2.getId(), vec2.getX(), vec2.getY(), vec2.getZ());

    return *this;
}

float vectorClass::magnitude()
{
	return sqrt((xCoord * xCoord) + (yCoord * yCoord) + (zCoord * zCoord)); //return the magnitude
}
