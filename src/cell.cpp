//cell.cpp


#include "cell.h"


// constructor
cell::cell(){}

// override constructor
// tetrahedron
cell::cell(int cellIdToSet, char typeOfCell, int matIdToSet,
     int vId1, int vId2, int vId3, int vId4)
{
    this->cellId = cellIdToSet;
    this->type = typeOfCell;
    this->matId = matIdToSet;

    vectorIdList.push_back(vId1); vectorIdList.push_back(vId2);
    vectorIdList.push_back(vId3); vectorIdList.push_back(vId4);

}

// hexahedron
cell::cell(int cellIdToSet, char typeOfCell, int matIdToSet,
     int vId1, int vId2, int vId3, int vId4,
     int vId5, int vId6, int vId7, int vId8)
{
    this->cellId = cellIdToSet;
    this->type = typeOfCell;
    this->matId = matIdToSet;

    vectorIdList.push_back(vId1); vectorIdList.push_back(vId2);
    vectorIdList.push_back(vId3); vectorIdList.push_back(vId4);
    vectorIdList.push_back(vId5); vectorIdList.push_back(vId6);
    vectorIdList.push_back(vId7); vectorIdList.push_back(vId8);




}

// pyramid
cell::cell(int cellIdToSet, char typeOfCell, int matIdToSet,
     int vId1, int vId2, int vId3, int vId4,
     int vId5)
{

    this->cellId = cellIdToSet;
    this->type = typeOfCell;
    this->matId = matIdToSet;

    vectorIdList.push_back(vId1); vectorIdList.push_back(vId2);
    vectorIdList.push_back(vId3); vectorIdList.push_back(vId4);
    vectorIdList.push_back(vId5);

}


// destructor
cell::~cell() {}

/* Get functions */

char cell::getType()
{
    return this->type;
}

int cell::getMatId()
{
    return this->matId;
}

int cell::getCellId()
{
    return this->cellId;
}
/* Set Functions */

void cell::setType(char newType)
{
    this->type = newType;
}

void cell::setMatId(int newId)
{
    this->matId = newId;
}

void cell::setCellId(int newId)
{
    this->cellId = newId;
}


/* Calculation Functions */

/* Inherited cells will have their own calcVolume function definition */

// Base volume calculation, to be left blank
float cell::calcVolume()
{
    // if inheritance fails


}
