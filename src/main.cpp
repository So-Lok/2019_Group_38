#include <iostream>

#include "model.h"
#include "vectorClass.h"

using namespace std;

int main()
{
    model test;

    /* Model Functions */
    // Tasks -----------------------

    // To test create a character array to store the file name
    char modelFile[20] = "ExampleModel3.mod";
    test.readFile(modelFile);

   // char name[20] = "test1.mod";
    // test.saveCurrentModelToFile(name);
    float volume;
    volume = test.calcModelVolume();
    cout << " Volume: " <<volume << endl; //ex1 works

    // Weight Test
    float weight;
    weight = test.calcModelWeight();
    cout << " Weight: " << weight <<  endl;


    // Centre of Gravity
    cout << " Centre of gravity approximation: \n---------------------------------\n" <<
     " X Coord: " << test.calculateModelCentre().getX() << endl <<
     " Y Coord: " << test.calculateModelCentre().getY() << endl <<
     " Z Coord: " << test.calculateModelCentre().getZ() << endl <<
     "---------------------------------" << endl;

    // Overall Dimensions
    test.calcOverallDimensions();

    //test.dispNumberOfCellsAndType();
   // test.dispCells();
   // test.dispNumberOfVertices();
    // /Tasks --------------------
/*
    test.dispMaterials();
    test.dispVectorList();
    test.dispCells();

*/

    // Display for all models

    model example1;
    model example2;
    model example3;

    char modelFile1[20] = "ExampleModel1.mod";
    char modelFile2[20] = "ExampleModel2.mod";
    char modelFile3[20] = "ExampleModel3.mod";

    // Example Model #1

    // Reading the file
    example1.readFile(modelFile1);










}
