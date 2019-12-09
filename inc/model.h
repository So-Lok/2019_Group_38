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


class model
{
public:

    // constructor
    model();

    //destructor
    ~model();

    // function to read in model file
    void readFile();

    void saveCurrentModelToFile();

    int getNumberOfVertices();

    // Calculates the centre of the model using the vertices vector values
   vectorClass calculateModelCentre();





 /* Display function */
    void dispVectorList();

    void dispMaterials();

    void dispCells();

    void dispNumberOfCellsAndType();

    void dispNumberOfVertices();



private:

    // vector list of vertices
    std::vector<vectorClass> vectorList;
    std::vector<material> materials;
    std::vector<cell> cells;

};



#endif // MODEL_H_INCLUDED
