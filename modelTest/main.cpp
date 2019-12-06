#include <iostream>

#include "model.h"

using namespace std;

int main()
{
    model test;

    //vectorClass testV(12.6, 5.2, 6.7);
    //cout << testV.getX() << testV.getY() << testV.getZ();

    // reads the mod file which is currently manually set by the user in the cpp code
    test.readFile();

    //test.dispVectorList();


 // test.dispMaterials();
    int numVertices;
    numVertices = test.getNumberOfVertices();
    cout << numVertices;



}
