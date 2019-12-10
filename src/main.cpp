#include <iostream>

#include "model.h"
#include "vectorClass.h"

using namespace std;

int main()
{
    model test;

    vectorClass testV(1 ,2, 1, 1);
    vectorClass test2(1,2,3,1);

    /* Vector Functions */
    /*
    float result = testV.scalarProduct(testV, test2);
    cout << result << " ";
    vectorClass vresult = testV.vectorProduct(testV, test2);
    cout << vresult.getX() << " " << vresult.getY() << " " << vresult.getZ() <<  " | ";
    // add
    vresult = testV+test2;
    cout << vresult.getX() << " " << vresult.getY() << " " << vresult.getZ() <<  " | ";
    // subtract
    vresult = testV-test2;
    cout << vresult.getX() << " " << vresult.getY() << " " << vresult.getZ() <<  " | ";

    //cout << testV.getX() << testV.getY() << testV.getZ();
*/
    /* Model Functions */
    // Tasks -----------------------

    // To test create a character array to store the file name
    char modelFile[20] = "ExampleModel2.mod";
    test.readFile(modelFile);

   // char name[20] = "test1.mod";
    // test.saveCurrentModelToFile(name);
    float volume;
    volume = test.calcModelVolume();
    cout << "Volume " <<volume << endl; //ex1 works

    // Weight Test
    float weight;
    weight = test.calcModelWeight();
    cout << "Weight : " << weight<< endl;

    // Centre of Gravity
    cout <<
     "X Coord: " << test.calculateModelCentre().getX() << endl <<
     "Y Coord: " << test.calculateModelCentre().getY() << endl <<
     "Z Coord: " << test.calculateModelCentre().getZ() << endl;


    //test.dispNumberOfCellsAndType();
   // test.dispCells();
   // test.dispNumberOfVertices();
    // /Tasks --------------------
/*
    test.dispMaterials();
    test.dispVectorList();
    test.dispCells();

*/
}
