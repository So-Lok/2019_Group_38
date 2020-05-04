#include <iostream>

#include "vectorClass.h"

int main(int argc, char *argv[])
{
    bool getSetFunctions = false;
    bool operatorFunctions = false;
    bool productFunctions = false;

    vectorClass vectorTest(1, 1.0, 1.0, 1.0);
    vectorClass vectorTest2(2, 1.0, 1.0, 1.0);
    vectorClass operations(4, 1.0, 1.0, 1.0);
    vectorClass equal;

    // get set functions
    vectorTest.setId(3);
    vectorTest.setX(6.9);
    vectorTest.setY(4.2);
    vectorTest.setZ(1.1);

    if(vectorTest.getId()==3)
      getSetFunctions = true;

    if(vectorTest.getX()==6.9)
      getSetFunctions = true;

    if(vectorTest.getY()==4.2)
      getSetFunctions = true;

    if(vectorTest.getZ()==1.1)
      getSetFunctions = true;

    // cross and scalar product
    if(vectorTest.scalarProduct(vectorTest, vectorTest2)==3.0 )
      productFunctions = true;

    vectorTest.vectorProduct(vectorTest, vectorTest2);
    if(vectorTest.getX()==0. &&
       vectorTest.getY()==0. &&
       vectorTest.getZ()==0.)
    {
      productFunctions = true;
    }
    // operator functions
    equal = vectorTest+vectorTest2;
    if(vectorTest.getX()==2. &&
       vectorTest.getY()==2. &&
       vectorTest.getZ()==2.)
    {
      operatorFunctions = true;
    }

    equal = vectorTest-vectorTest2;
    if(vectorTest.getX()==0. &&
       vectorTest.getY()==0. &&
       vectorTest.getZ()==0.)
    {
      operatorFunctions = true;
    }



    if(vectorTest.magnitude() > 1.7319 && vectorTest.magnitude() < 1.7321)


    if(getSetFunctions==true &&
       operatorFunctions==true &&
       productFunctions==true)
    {
      return(1);
    }
}
