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

    // Model file functions
    void readFile(const char* fileName);
    void saveCurrentModelToFile(const char* fileName);

    /* Calculation Functions */
   vectorClass calculateModelCentre();
   float calcModelVolume();
   float calcModelWeight();
   void calcOverallDimensions();


 /* Display function */
    void dispVectorList();

    void dispMaterials();

    void dispCells();

    void dispNumberOfCellsAndType();

    void dispNumberOfVertices();
    int getNumberOfVertices();

    // get functions
    std::vector<vectorClass> getVectorList();
    std::vector<cell> getCells();

private:

    // vector list of vertices
    std::vector<vectorClass> vectorList;
    std::vector<material> materials;
    std::vector<cell> cells;

};



#endif // MODEL_H_INCLUDED
