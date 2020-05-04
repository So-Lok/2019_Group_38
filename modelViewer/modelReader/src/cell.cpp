
//cell.cpp

/**
* @file cell.cpp
* @brief definitions of functions declared in cell.h
*/



#include "cell.h"
#include "model.h"

#include <iostream>
#include <math.h>

using namespace std;

// constructor
cell::cell() {}

// override constructor
// tetrahedron
cell::cell(int cellIdToSet, char typeOfCell, int matIdToSet,
           int vId1, int vId2, int vId3, int vId4,
           vectorClass temp1, vectorClass temp2, vectorClass temp3, vectorClass temp4)
{
    this->cellId = cellIdToSet;
    this->type = typeOfCell;
    this->matId = matIdToSet;

    vectorIdList.push_back(vId1);
    vectorIdList.push_back(vId2);
    vectorIdList.push_back(vId3);
    vectorIdList.push_back(vId4);
    // use temporary vectors to store in cell's list of array
    vectorList.push_back(temp1);
    vectorList.push_back(temp2);
    vectorList.push_back(temp3);
    vectorList.push_back(temp4);

}

// hexahedron
cell::cell(int cellIdToSet, char typeOfCell, int matIdToSet,
           int vId1, int vId2, int vId3, int vId4,
           int vId5, int vId6, int vId7, int vId8,
           vectorClass temp1, vectorClass temp2, vectorClass temp3, vectorClass temp4,
           vectorClass temp5, vectorClass temp6, vectorClass temp7, vectorClass temp8)
{
    this->cellId = cellIdToSet;
    this->type = typeOfCell;
    this->matId = matIdToSet;

    vectorIdList.push_back(vId1);
    vectorIdList.push_back(vId2);
    vectorIdList.push_back(vId3);
    vectorIdList.push_back(vId4);
    vectorIdList.push_back(vId5);
    vectorIdList.push_back(vId6);
    vectorIdList.push_back(vId7);
    vectorIdList.push_back(vId8);
    // use temporary vectors to store in cell's list of array
    vectorList.push_back(temp1);
    vectorList.push_back(temp2);
    vectorList.push_back(temp3);
    vectorList.push_back(temp4);
    vectorList.push_back(temp5);
    vectorList.push_back(temp6);
    vectorList.push_back(temp7);
    vectorList.push_back(temp8);



}

// pyramid
cell::cell(int cellIdToSet, char typeOfCell, int matIdToSet,
           int vId1, int vId2, int vId3, int vId4,
           int vId5,
           vectorClass temp1, vectorClass temp2, vectorClass temp3, vectorClass temp4, vectorClass temp5)
{

    this->cellId = cellIdToSet;
    this->type = typeOfCell;
    this->matId = matIdToSet;

    vectorIdList.push_back(vId1);
    vectorIdList.push_back(vId2);
    vectorIdList.push_back(vId3);
    vectorIdList.push_back(vId4);
    vectorIdList.push_back(vId5);
    // use temporary vectors to store in cell's list of array
    vectorList.push_back(temp1);
    vectorList.push_back(temp2);
    vectorList.push_back(temp3);
    vectorList.push_back(temp4);
    vectorList.push_back(temp5);

}


// destructor
cell::~cell() {}

/* Get functions */

char cell::getType()
{
    return this->type;
}

int cell::getMatId()
{
    return this->matId;
}

int cell::getCellId()
{
    return this->cellId;
}
/* Set Functions */

void cell::setType(char newType)
{
    this->type = newType;
}

void cell::setMatId(int newId)
{
    this->matId = newId;
}

void cell::setCellId(int newId)
{
    this->cellId = newId;
}

void cell::dispCellVectors()
{
    int listSize = vectorList.size();
    //cout << listSize << " here";
    for(int i=0;i<listSize;i++)
    {
        cout
        << vectorList[i].getId() << " "
        << vectorList[i].getX() << " "
        << vectorList[i].getY() << " "
        << vectorList[i].getZ() << "\n";
    }
}

/* Calculation Functions */

/* Inherited cells will have their own calcVolume function definition */

// Base volume calculation, to be left blank
float cell::calcVolume()
{


    if(this->type == 't')
    {
        float volume;

        // Store the vertices of the tetrahedron and label a-d
        vectorClass a = vectorList[0];
        vectorClass b = vectorList[1];
        vectorClass c = vectorList[2];
        vectorClass d = vectorList[3];



        //cout << "here "<< a.getX() << a.getY() << a.getZ() << endl;

        // finding edge lengths
        vectorClass ab = b-a;

        vectorClass ac = c-a;
        vectorClass ad = d-a;
       // cout << "here "<< ac.getX() << ac.getY() << ac.getZ() << endl;

        //
        vectorClass crossProdTerm;
        crossProdTerm = crossProdTerm.vectorProduct(ac, ad);
        //
        vectorClass dotProdTerm;
        // 6*volume currently
        //cout << dotProdTerm.scalarProduct(crossProdTerm, ab);
        volume = fabs(dotProdTerm.scalarProduct(crossProdTerm, ab));
       // cout << volume << endl;
        volume = volume/6;
       // cout << volume << " tetra" << endl;
        return volume;


    }

    if(this->type == 'p')
    {
        float volume;

        // Store the vertices
        vectorClass a = vectorList[0];
        vectorClass b = vectorList[1];
        vectorClass c = vectorList[2];
        vectorClass d = vectorList[3];
        vectorClass e = vectorList[4];

        // finding edge lengths
        vectorClass ab = b-a;
        vectorClass ac = c-a;
        vectorClass ad = d-a;
        vectorClass ae = e-a;

        // treat as two tetrahedron
        vectorClass crossProdTerm;
        crossProdTerm = crossProdTerm.vectorProduct(ab, ac);

        vectorClass dotProdTerm;
        vectorClass dotProdTerm2;

        // 6*volume

        volume = dotProdTerm.scalarProduct(crossProdTerm, ad) + dotProdTerm2.scalarProduct(crossProdTerm, ae);
        volume = volume/6;

        return volume;

    }

    if(this->type == 'h')
    {
        float volume;

        // Store the vertices, using numbers for clarity
        vectorClass v0 = vectorList[0];vectorClass v1 = vectorList[1];
        vectorClass v2 = vectorList[2];vectorClass v3 = vectorList[3];
        vectorClass v4 = vectorList[4];vectorClass v5 = vectorList[5];
        vectorClass v6 = vectorList[6];vectorClass v7 = vectorList[7];


        // 3x 3x3 determinants // v6 is corner
        // 1 - label a1 b1 c1

        vectorClass a1 = v6-v0; // replacing all v7 with v6 and vice versa
        vectorClass b1 = v1-v0;
        vectorClass c1 = v2-v5; // replacing all v2 with v3

        // 2 - label a2 b2 c2

       // vectorClass a2 = v6-v0;dotProdTerm.scalarProduct(crossProdTerm, ab)
        vectorClass b2 = v4-v0;
        vectorClass c2 = v5-v7;

        // 3 - label a3 b3 c3

        //vectorClass a3 = v6-v0; // = a1 = a2
        vectorClass b3 = v3-v0;
        vectorClass c3 = v7-v2;

        // create terms to hold the terms for A(dot)(BxC)
        vectorClass crossProdTerm1;
        vectorClass crossProdTerm2;
        vectorClass crossProdTerm3;

        // place holder to show what is happening
        vectorClass dotProdTerm1;
        vectorClass dotProdTerm2;
        vectorClass dotProdTerm3;
        // BxC
        crossProdTerm1 = crossProdTerm1.vectorProduct(b1, c1);
        crossProdTerm2 = crossProdTerm2.vectorProduct(b2, c2);
        crossProdTerm3 = crossProdTerm3.vectorProduct(b3, c3);
        // A dot BxC - output is float for each one
        float term1=0, term2=0, term3=0;
        term1 = dotProdTerm1.scalarProduct(crossProdTerm1, a1);
        term2 = dotProdTerm2.scalarProduct(crossProdTerm2, a1);
        term3 = dotProdTerm3.scalarProduct(crossProdTerm3, a1);

        // |A dot BxC| magnitude
        term1 = fabs(term1);
        term2 = fabs(term2);
        term3 = fabs(term3);
        //cout << term1 << " " << term2 << " " << term3 <<endl;
         volume = (term1 + term2 + term3)/6;
        //cout << volume << " | hexa \n";
        return volume;

    }

}

vectorClass cell::centreOfGravity()
{
    // average all vector xyz
    vectorClass centreOfGravity;
    float xTotal=0;
    float yTotal=0;
    float zTotal=0;

    int numVertices = vectorList.size();

    for(int i = 0; i<numVertices; i++)
    {
        xTotal = xTotal + vectorList[i].getX();
        yTotal = yTotal + vectorList[i].getY();
        zTotal = zTotal + vectorList[i].getZ();
    }

    xTotal = xTotal/numVertices;
    yTotal = yTotal/numVertices;
    zTotal = zTotal/numVertices;

    centreOfGravity.setX(xTotal);
    centreOfGravity.setY(yTotal);
    centreOfGravity.setZ(zTotal);

    return centreOfGravity;
}

float cell::calcWeight(int density)
{
    // weight = pVg where p = density V = volume and g = gravity on earth, ~9.8
    float weight;

    weight = density*calcVolume()*9.8;

    return weight;



}

// sem2
std::vector<int> cell::getThisCellVectorIdList()
{
  return vectorIdList;
}
