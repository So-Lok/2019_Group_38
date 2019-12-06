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

using namespace std;


class model
{
public:

    // constructor
    // constructor should read a .vtk file
    model();

    //destructor
    ~model();

    // Function to read the model file
    // string nameOfModelfile ? maybe
    void readFile();

    //get functions
    int getNumberOfVertices();

    // needs data type
//    getNumberOfCellsAndType();

    // Calculates the centre of the model using the vertices vector values
 //   vector calculateModelCentre();

    void dispVectorList();

    void dispMaterials();

private:

    // vector list of vertices
    std::vector<vectorClass> vectorList;
    std::vector<material> materials;
   //std::vector<cell> cells;

};



#endif // MODEL_H_INCLUDED
