/**
* @file cell.h
* @brief contains declarations for the cell class
*/


#ifndef CELL_H
#define CELL_H

#include <vector>

#include "vectorClass.h"
/**
*  This class contains information for each cell
*/
class cell
{
public:
    // allow model class to access vectorIdList
     friend class model;

    // constructor

    /**
    *  Default contructor for cell
    */
    cell();

    // override constructor X3 FOR EACH TYPE

    /**
    *  Ovveride costructor for tetrahedron cell type
    */
    cell(int cellIdToSet, char typeOfCell, int matIdToSet,
         int vId1, int vId2, int vId3, int vId4,
         vectorClass temp1, vectorClass temp2, vectorClass temp3, vectorClass temp4);
    /**
    *  Ovveride costructor for pyramid cell type
    */
    cell(int cellIdToSet, char typeOfCell, int matIdToSet,
         int vId1, int vId2, int vId3, int vId4,
         int vId5,
         vectorClass temp1, vectorClass temp2, vectorClass temp3, vectorClass temp4,
         vectorClass temp5);

    /**
    *  Ovveride costructor for hexahedron cell type
    */
    cell(int cellIdToSet, char typeOfCell, int matIdToSet,
         int vId1, int vId2, int vId3, int vId4,
         int vId5, int vId6, int vId7, int vId8,
         vectorClass temp1, vectorClass temp2, vectorClass temp3, vectorClass temp4,
         vectorClass temp5, vectorClass temp6, vectorClass temp7, vectorClass temp8);



    // destructor
    /**
    *  Default destructor
    */
    ~cell();

    /* Get functions */

    /**
    *  gets the cell type
    *  h - hexahedron
    *  t - tetrahedron
    *  p - pyramid
    */
    char getType();

    /**
    * gets the material ID of the cell
    */
    int getMatId();
    /**
    * gets the ID of the cell
    */
    int getCellId();

    //sem2

    /**
    * gets a list of this cell's vector IDs
    */
    std::vector<int> getThisCellVectorIdList();


    /* Set Functions */

    /**
    * sets a new type for the cell
    * @param newType new cell type to be set
    */
    void setType(char newType);

    /**
    * sets the cell's material
    * @param newId new ID for the cell's material
    */
    void setMatId(int newId);

    /**
    * sets the cell's ID
    * @param newId new ID for the cell
    */
    void setCellId(int newId);

    /* Calculation Functions */

    // vectorlist passed from model
    
    float calcVolume();

    vectorClass centreOfGravity();

    float calcWeight(int density);

    void dispCellVectors();

    // for the model to use vector Id list
   // int* getVectorIdList();

private:
    /* Base Cell variables */
    int cellId;
    char type;
    int matId;

    // stores the IDs of the vectors in the cell
    std::vector<int> vectorIdList;
    std::vector<vectorClass> vectorList;
    // address to the models vector list, to be set during the reading of the model file
    //std::vector<vectorClass> vectorListAddress;

};

#endif // CELL_H
