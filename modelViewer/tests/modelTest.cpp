#include <iostream>

#include "model.h"
#include "vectorClass.h"
#include "material.h"
#include "cell.h"

using namespace std;

int main(int argc, char *argv[])
{
  
    bool calcModelVolumeTestReturn = false;
    bool getNumberOfVerticesReturn = false;
    bool calcModelWeightReturn = false;

    model test;
    // Use model1 to test1
    char modelFile1[20] = "ExampleModel1.mod";

    test.readFile(modelFile1);

    // testing of functions with a return value
    if(test.getNumberOfVertices()==12)
      getNumberOfVerticesReturn = true;

    if(test.calcModelVolume()>1.08332 && test.calcModelVolume()<1.08334) // so that calcModelVolume is acc to 2dp
      calcModelVolumeTestReturn = true;

    if(test.calcModelWeight()==90013)
      calcModelWeightReturn = true;

    if(calcModelVolumeTestReturn==true &&
       getNumberOfVerticesReturn==true &&
       calcModelWeightReturn==true)
    {
      return(1);
    }





}
