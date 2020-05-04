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
    * @param cellIdToSet new cell ID value
    * @param typeOfCell new cell type value
    * @param matIdToSet new material value
    * @param vId1 ID for vector 1
    * @param vId2 ID for vector 2
    * @param vId3 ID for vector 3
    * @param vId4 ID for vector 4
    * @param temp1 temporary vector1 for storing purposes
    * @param temp2 temporary vector2 for storing purposes
    * @param temp3 temporary vector3 for storing purposes
    * @param temp4 temporary vector4 for storing purposes
    */
    cell(int cellIdToSet, char typeOfCell, int matIdToSet,
         int vId1, int vId2, int vId3, int vId4,
         vectorClass temp1, vectorClass temp2, vectorClass temp3, vectorClass temp4);
    /**
    *  Ovveride costructor for pyramid cell type
    * @param cellIdToSet new cell ID value
    * @param typeOfCell new cell type value
    * @param matIdToSet new material value
    * @param vId1 ID for vector 1
    * @param vId2 ID for vector 2
    * @param vId3 ID for vector 3
    * @param vId4 ID for vector 4
    * @param vId5 ID for vector 5
    * @param temp1 temporary vector1 for storing purposes
    * @param temp2 temporary vector2 for storing purposes
    * @param temp3 temporary vector3 for storing purposes
    * @param temp4 temporary vector4 for storing purposes
    * @param temp5 temporary vector5 for storing purposes
    */
    cell(int cellIdToSet, char typeOfCell, int matIdToSet,
         int vId1, int vId2, int vId3, int vId4,
         int vId5,
         vectorClass temp1, vectorClass temp2, vectorClass temp3, vectorClass temp4,
         vectorClass temp5);

    /**
    *  Ovveride costructor for hexahedron cell type
    * @param cellIdToSet new cell ID value
    * @param typeOfCell new cell type value
    * @param matIdToSet new material value
    * @param vId1 ID for vector 1
    * @param vId2 ID for vector 2
    * @param vId3 ID for vector 3
    * @param vId4 ID for vector 4
    * @param vId5 ID for vector 5
    * @param vId6 ID for vector 6
    * @param vId7 ID for vector 7
    * @param vId8 ID for vector 8
    * @param temp1 temporary vector1 for storing purposes
    * @param temp2 temporary vector2 for storing purposes
    * @param temp3 temporary vector3 for storing purposes
    * @param temp4 temporary vector4 for storing purposes
    * @param temp5 temporary vector5 for storing purposes
    * @param temp6 temporary vector6 for storing purposes
    * @param temp7 temporary vector7 for storing purposes
    * @param temp8 temporary vector8 for storing purposes
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
    /**
    * Calculates the volume of the cell depending on its type
    * only works for tetrahedron, hexahedron and pyramid
    */
    float calcVolume();

    /**
    * Calculates an estimate of the centre of gravity of the cell by averaging the vertices
    */
    vectorClass centreOfGravity();

    /**
    * Calculates the weight of the cell
    * @param density denisty of the cell material
    */
    float calcWeight(int density);

    /**
    * Displays the cell's vectors to the command line
    */
    void dispCellVectors();

    // for the model to use vector Id list
   // int* getVectorIdList();

private:
    /* Base Cell variables */
    int cellId; ///< Cell's ID
    char type; ///< Cell's type
    int matId; ///< the material ID of the cell

    // stores the IDs of the vectors in the cell
    std::vector<int> vectorIdList; ///< vector array of vector IDs
    std::vector<vectorClass> vectorList; ///< vector array of vectors within the cell

    // address to the models vector list, to be set during the reading of the model file
    //std::vector<vectorClass> vectorListAddress;

};

#endif // CELL_H
