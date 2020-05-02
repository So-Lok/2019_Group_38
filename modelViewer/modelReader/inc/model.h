#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

// use vector to create object lists
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "vectorClass.h"
#include "material.h"
#include "cell.h"

using namespace std;

/**
* This class stores the properties of a model
*/
class model
{
public:


    /**
    * Standard constructor
    */
    model();


    /**
    * Standard constructor
    */
    ~model();

    // Model file functions
    /**
    * Reads in .mod files which contain information on the models properties
    */
    void readFile(const char* fileName);
    /**
    * Saves the current model and generates a file
    */
    void saveCurrentModelToFile(const char* fileName);

    /* Calculation Functions */
    /**
    * Calculates the approx centre of the model
    */
    vectorClass calculateModelCentre();
    /**
    * Calculates volume of the model
    */
    float calcModelVolume();
    /**
    * Calculates the weight of the model
    */
    float calcModelWeight();




    /* Display function */

    /**
    * Calculates the the xyz dimensions of the model
    */
    void calcOverallDimensions();

    /**
    * Displays the model's vectors on the command line
    */
    void dispVectorList();
    /**
    * Displays the model's materials on the command line
    */
    void dispMaterials();
    /**
    * Displays the model's cells on the command line
    */
    void dispCells();
    /**
    * Displays the numeber of cells inside of the model and their type on the command line
    */
    void dispNumberOfCellsAndType();
    /**
    * Displays number of vertices on the command line
    */
    void dispNumberOfVertices();



    // get functions
    /**
    *  Returns the number of vertices
    */
    int getNumberOfVertices();

    /**
    *  Returns the list of vectors as a vector
    */
    std::vector<vectorClass> getVectorList();

    /**
    *  Returns the list of cells vector
    */
    std::vector<cell> getCells();

private:

    // vector list of vertices
    /**
    *  vector of the vectorList class
    */
    std::vector<vectorClass> vectorList;
    /**
    *  vector of the materials class
    */
    std::vector<material> materials;
    /**
    *  vector of the cell class
    */
    std::vector<cell> cells;

};



#endif // MODEL_H_INCLUDED
