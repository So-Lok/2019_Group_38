#ifndef CELL_H
#define CELL_H

#include <vector>

#include "vectorClass.h"


class cell
{
public:
    // allow model class to access vectorIdList
     friend class model;

    // constructor
    cell();

    // override constructor X3 FOR EACH TYPE
    cell(int cellIdToSet, char typeOfCell, int matIdToSet,
         int vId1, int vId2, int vId3, int vId4);

    cell(int cellIdToSet, char typeOfCell, int matIdToSet,
         int vId1, int vId2, int vId3, int vId4,
         int vId5);

    cell(int cellIdToSet, char typeOfCell, int matIdToSet,
         int vId1, int vId2, int vId3, int vId4,
         int vId5, int vId6, int vId7, int vId8);



    // destructor
    ~cell();

    /* Get functions */

    char getType();

    int getMatId();

    int getCellId();

    /* Set Functions */

    void setType(char newType);

    void setMatId(int newId);

    void setCellId(int newId);

    /* Calculation Functions */

    float calcVolume();

    vectorClass centreOfGravity();

    float calcWeight();

    // for the model to use vector Id list
    int* getVectorIdList();

private:
    /* Base Cell variables */
    int cellId;
    char type;
    int matId;

    // stores the IDs of the vectors in the cell
    std::vector<int> vectorIdList;

    // address to the models vector list, to be set during the reading of the model file
    //std::vector<vectorClass> vectorListAddress;

};

#endif // CELL_H
