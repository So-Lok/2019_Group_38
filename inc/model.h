#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

// use vector to create object lists
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


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



private:

    // vector list of vertices
  //  <vector>vertices();
 //   material();
 //   cell();

};



#endif // MODEL_H_INCLUDED
