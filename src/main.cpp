#include <iostream>

#include "model.h"
#include "vectorClass.h"

using namespace std;

int main()
{
    // Display for all models

    model example1;
    model example2;
    model example3;

    char modelFile1[20] = "ExampleModel1.mod";
    char modelFile2[20] = "ExampleModel2.mod";
    char modelFile3[20] = "ExampleModel3.mod";

    // Temporary variables to store params for display
    float volume;
    float weight;

    // Reading the model files
    example1.readFile(modelFile1);
    example2.readFile(modelFile2);
    example3.readFile(modelFile3);

    // Model #1

    cout << "==================" << endl
         << " Example Model #1 " << endl
         << "==================" << endl;

    // Volume
    volume = example1.calcModelVolume();
    cout << " Volume: " << volume << endl;

    // Weight
    weight = example1.calcModelWeight();
    cout << " Weight: " << weight <<  endl;

    // Overall Dimensions
    example1.calcOverallDimensions();

    // Centre of Gravity
    cout << " Centre of gravity approximation: \n---------------------------------\n" <<
     " X Coord: " << example1.calculateModelCentre().getX() << endl <<
     " Y Coord: " << example1.calculateModelCentre().getY() << endl <<
     " Z Coord: " << example1.calculateModelCentre().getZ() << endl <<
     "---------------------------------" << endl;


    // Model #2

    cout << "==================" << endl
         << " Example Model #2 " << endl
         << "==================" << endl;

    // Volume
    volume = example2.calcModelVolume();
    cout << " Volume: " << volume << endl;

    // Weight
    weight = example2.calcModelWeight();
    cout << " Weight: " << weight <<  endl;

    // Overall Dimensions
    example2.calcOverallDimensions();

    // Centre of Gravity
    cout << " Centre of gravity approximation: \n---------------------------------\n" <<
     " X Coord: " << example2.calculateModelCentre().getX() << endl <<
     " Y Coord: " << example2.calculateModelCentre().getY() << endl <<
     " Z Coord: " << example2.calculateModelCentre().getZ() << endl <<
     "---------------------------------" << endl;

     // Model #3

    cout << "==================" << endl
         << " Example Model #3 " << endl
         << "==================" << endl;

    // Volume
    volume = example3.calcModelVolume();
    cout << " Volume: " << volume << endl;

    // Weight
    weight = example3.calcModelWeight();
    cout << " Weight: " << weight <<  endl;

    // Overall Dimensions
    example3.calcOverallDimensions();

    // Centre of Gravity
    cout << " Centre of gravity approximation: \n---------------------------------\n" <<
     " X Coord: " << example3.calculateModelCentre().getX() << endl <<
     " Y Coord: " << example3.calculateModelCentre().getY() << endl <<
     " Z Coord: " << example3.calculateModelCentre().getZ() << endl <<
     "---------------------------------" << endl;


     /* Additional Model Functions */
    // model test;

    /// Save to a file
    // char name[20] = "test1.mod";
    // test.saveCurrentModelToFile(name);

    /// Display Functions
    // test.dispNumberOfCellsAndType();
    // test.dispCells();
    // test.dispNumberOfVertices();
    // test.dispMaterials();
    // test.dispVectorList();
    // test.dispCells();





}
