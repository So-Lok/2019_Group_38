// material.cpp

#include "material.h"

material::material(){}

// Override constructor to set all the values
material::material(int matIdToSet, int densityToSet, string colourToSet, string nameToSet)
{
    this->matId = matIdToSet;
    this->density = densityToSet;
    this->colour = colourToSet;
    this->matName = nameToSet;
}


material::~material(){}

/* Get Functions */

int material::getMatId()
{
    return this->matId;
}

int material::getDensity()
{
    return this->density;
}

string material::getColour()
{
    return this->colour;
}

string material::getMatName()
{
    return this->matName;
}


