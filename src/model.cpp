// model.cpp

#include "model.h"

//constructor
model::model()
{

}

//destructor
model::~model()
{

}
// Model Functions -----------------------------------------------------------------
// read file function, string could also be the path location of the model - file string nameOfModelfile
void model::readFile(const char* fileName)
{
    //* Function variables used to store values*//
    int id;
    /* Temporary material variables */
    int density;
    string colour;
    string name;

    /*Temporary vector variables */
    float xCoord;
    float yCoord;
    float zCoord;

    /*Temporary cell variables */
    char type;
    int matId;
    short vId1, vId2, vId3, vId4, vId5, vId6, vId7, vId8;


    // create a string variable to contain the information on each line
    string line;

    // input the file into the stream
    ifstream modelFile(fileName);

    // conditional statement in case error occurs when opening the file
    if(modelFile.is_open())
    {
        // loops until every line has been read
        // Loop will read and store data depending on the information in the file

        while(getline(modelFile,line))
        {

            if (line[0] == 'm') // check for the vertex character
            {
                // ssline for string stream line
                stringstream ssline(line);

                // converts terms inside of the string stream to the data types of the
                // variables stated

                // omits the first character, the identifier character
                ssline.ignore(1);

                /*
                stores the next terms in the string stream into the variables stated
                we can do this as we know the structure of the model file and therefore
                can set the variable types up
                */


                ssline >> id >> density >> colour >> name;
                material newMaterial(id, density, colour, name);
                materials.push_back(newMaterial);
              //  cout << id << "\n" << density << "\n" << colour << "\n" << name << "\n";    // display

            }

            // looks for lines with the vector identifier
            if(line[0] == 'v')
            {
                stringstream ssline(line);
                ssline.ignore(1);
                ssline >> id >> xCoord >> yCoord >> zCoord;
                // construct a vector using id and coordinates
                vectorClass newVector(id, xCoord, yCoord, zCoord);
                // push the constructed vector class into the vectorClass list called vectorList
                vectorList.push_back(newVector);


                // displays vector out
                //cout << "Vectors :" << id << " " << xCoord << " " << yCoord << " " << zCoord << "\n";
            }

            // looks for lines with the cell identifier
            if(line[0] == 'c')
            {
                //cout << "\n"<< line << "\n"; // Testing input
                stringstream ssline(line);
                ssline.ignore(1);
                ssline >> id >> type >> matId;

               // cout << id << " " << type << " ";


                // hexahedron cell
                if(type == 'h')
                {

                    ssline >>  vId1 >>  vId2 >>  vId3 >>  vId4
                           >>  vId5 >>  vId6 >>  vId7 >>  vId8;

                    // create temporary vector
                    vectorClass temp1; vectorClass temp2;
                    vectorClass temp3; vectorClass temp4;
                    vectorClass temp5; vectorClass temp6;
                    vectorClass temp7; vectorClass temp8;
                    // Setting all variables to the temporary vectors
                    // Needs compacting later

                    temp1.setAll(vId1, vectorList[vId1].getX(), vectorList[vId1].getY(), vectorList[vId1].getZ());
                    temp2.setAll(vId2, vectorList[vId2].getX(), vectorList[vId2].getY(), vectorList[vId2].getZ());
                    temp3.setAll(vId3, vectorList[vId3].getX(), vectorList[vId3].getY(), vectorList[vId3].getZ());
                    temp4.setAll(vId4, vectorList[vId4].getX(), vectorList[vId4].getY(), vectorList[vId4].getZ());
                    temp5.setAll(vId5, vectorList[vId5].getX(), vectorList[vId5].getY(), vectorList[vId5].getZ());
                    temp6.setAll(vId6, vectorList[vId6].getX(), vectorList[vId6].getY(), vectorList[vId6].getZ());
                    temp7.setAll(vId7, vectorList[vId7].getX(), vectorList[vId7].getY(), vectorList[vId7].getZ());
                    temp8.setAll(vId8, vectorList[vId8].getX(), vectorList[vId8].getY(), vectorList[vId8].getZ());


                    // class constructor with vectors
                    cell newCell(id, type, matId, vId1, vId2, vId3, vId4,
                                                  vId5, vId6, vId7, vId8,
                                                  temp1, temp2, temp3, temp4,
                                                  temp5, temp6, temp7, temp8);
                    cells.push_back(newCell);

                   // cout <<  vId1 <<  vId2 <<  vId3 <<  vId4
                        //r <<  vId5 <<  vId6 <<  vId7 <<  vId8;
                }

                // tetrahedron cell
                if(type == 't')
                {

                    ssline >>  vId1 >>  vId2 >>  vId3 >>  vId4;
                    // create temporary vector
                    vectorClass temp1; vectorClass temp2;
                    vectorClass temp3; vectorClass temp4;

                    temp1.setAll(vId1, vectorList[vId1].getX(), vectorList[vId1].getY(), vectorList[vId1].getZ());
                    temp2.setAll(vId2, vectorList[vId2].getX(), vectorList[vId2].getY(), vectorList[vId2].getZ());
                    temp3.setAll(vId3, vectorList[vId3].getX(), vectorList[vId3].getY(), vectorList[vId3].getZ());
                    temp4.setAll(vId4, vectorList[vId4].getX(), vectorList[vId4].getY(), vectorList[vId4].getZ());


                    cell newCell(id, type, matId, vId1, vId2, vId3, vId4,
                                                  temp1, temp2, temp3, temp4);
                    cells.push_back(newCell);
                }

                // Pyramid cell
                if(type == 'p')
                {

                    ssline >>  vId1 >>  vId2 >>  vId3 >>  vId4 >>  vId5;
                    // create temporary vector
                    vectorClass temp1; vectorClass temp2;
                    vectorClass temp3; vectorClass temp4; vectorClass temp5;

                    temp1.setAll(vId1, vectorList[vId1].getX(), vectorList[vId1].getY(), vectorList[vId1].getZ());
                    temp2.setAll(vId2, vectorList[vId2].getX(), vectorList[vId2].getY(), vectorList[vId2].getZ());
                    temp3.setAll(vId3, vectorList[vId3].getX(), vectorList[vId3].getY(), vectorList[vId3].getZ());
                    temp4.setAll(vId4, vectorList[vId4].getX(), vectorList[vId4].getY(), vectorList[vId4].getZ());
                    temp5.setAll(vId5, vectorList[vId5].getX(), vectorList[vId5].getY(), vectorList[vId5].getZ());


                    cell newCell(id, type, matId, vId1, vId2, vId3, vId4, vId5,
                                                  temp1, temp2, temp3, temp4,
                                                  temp5);
                    cells.push_back(newCell);
                }

            }

        }

    }


}

/* Save/export current model file */

void model::saveCurrentModelToFile(const char* fileName)
{
    // create index/counter for looping
    unsigned int i;

    // create ofstream variable, file, to output to
    std::ofstream outputFile(fileName, std::ofstream::out);

    for(i = 0; i<materials.size();i++)
    {
        outputFile
        << "m "
        << materials[i].getMatId() << " "
        << materials[i].getDensity() << " "
        << materials[i].getColour() << " "
        << materials[i].getMatName() << "\n";
    }

    for(i = 0; i<vectorList.size();i++)
    {
        outputFile
        << "v "
        << vectorList[i].getId() << " "
        << vectorList[i].getX() << " "
        << vectorList[i].getY() << " "
        << vectorList[i].getZ() << "\n";
    }


    for(i = 0; i<materials.size();i++)
    {
        outputFile
        << "c "
        << cells[i].getCellId() << " "
        << cells[i].getType() << " "
        << cells[i].getMatId() << " ";
        for(unsigned int j =0; j<cells[i].vectorIdList.size();j++)
            outputFile << cells[i].vectorIdList[j] << " ";

        outputFile << "\n";
    }
}
// /Model Functions --------------------------------------------------------

// Calculation Functions

float model::calcModelVolume()
{
    float totalVolume = 0;
    int cellsSize = cells.size();
    // send the list of vectors to cell so that each cell can calculate its volume
    for(int i = 0; i< cellsSize; i++)
    {
        totalVolume = totalVolume + cells[i].calcVolume();
        //cells[i].dispCellVectors();
        //cout << totalVolume << "\n";
    }

    return totalVolume;
}

/* Display functions */ //-----------------------------------------------------------------

void model::dispVectorList()
{
    int listSize = vectorList.size();

    for(int i = 0; i < listSize;i++)
    {
        cout
        << vectorList[i].getId() << " "
        << vectorList[i].getX() << " "
        << vectorList[i].getY() << " "
        << vectorList[i].getZ() << "\n";
    }

}

void model::dispMaterials()
{
    int listSize = materials.size();

    for(int i = 0; i < listSize;i++)
    {
        cout
        << materials[i].getMatId() << " "
        << materials[i].getDensity() << " "
        << materials[i].getColour() << " "
        << materials[i].getMatName() << "\n";
    }
}

void model::dispCells()
{
    int listSize = cells.size();
    // loops for all cells
    for(int i = 0; i < listSize;i++)
    {

        cout << "\n" <<"Cell " << i << ": "
        << cells[i].getCellId() << " "
        << cells[i].getType() << " "
        << cells[i].getMatId() << "\n";


        // Loops through all vector IDs within the current cell
        for(unsigned int j =0; j<cells[i].vectorIdList.size();j++)
            cout <<cells[i].vectorIdList[j] << " ";
    }

}

void model::dispNumberOfCellsAndType()
{
    // counters for each cell type
    int numT = 0, numH = 0, numP = 0;
    int listSize = cells.size();
    for(int i = 0; i < listSize;i++)
    {
        if(cells[i].getType() == 't')
        {
            numT++;
        }
        else if(cells[i].getType() == 'h')
        {
            numH++;
        }
        else
        {
            numP++;
        }
    }

    cout << "Number of cells : " << listSize << "\n";
    cout
    << "Tetrahedron cells: " << numT
    << "\nHexahedron cells: " << numH
    << "\nPyramid cells " << numP << "\n";

}

void model::dispNumberOfVertices()
{
   int numV = this->vectorList.size();
   cout << "The number of vertices in this model is: " <<numV << "\n";
}
// Display functions END // -------------------------------------------------------------------------------

int model::getNumberOfVertices()
{
    return this->vectorList.size();
}

float model::calcModelWeight()
{
    // create limits for for loops based on material and cell array size
    int numCells = cells.size();
    int numMaterials = materials.size();

    float weight=0;
    // for all materials
    for(int i = 0;i<numMaterials;i++)
    {
        int matIdx = materials[i].getMatId();
        int density = materials[i].getDensity();
        // select only the cells of material i
        for(int j=0;j<numCells;j++)
        {
            if(matIdx == cells[j].getMatId())
            {
                weight = weight + cells[j].calcWeight(density);
            }
        }
    }


    return weight;
}

vectorClass model::calculateModelCentre()
{
    int numCells = cells.size();
    vectorClass modelCentre;

    float xTotal=0;
    float yTotal=0;
    float zTotal=0;

    for(int i=0;i<numCells;i++)
    {
        xTotal = xTotal + cells[i].centreOfGravity().getX();
        yTotal = yTotal + cells[i].centreOfGravity().getY();
        zTotal = zTotal + cells[i].centreOfGravity().getZ();

    }

    xTotal = xTotal/numCells;
    yTotal = yTotal/numCells;
    zTotal = zTotal/numCells;

    modelCentre.setX(xTotal);
    modelCentre.setY(yTotal);
    modelCentre.setZ(zTotal);

    return modelCentre;
}

// calculates and displays the overall dimensions to the user
void model::calcOverallDimensions()
{
    float minX=0, maxX=0, minY=0, maxY=0, minZ=0, maxZ=0;

    // vector list size - for looping
    int vlistSize = vectorList.size();

    for(int i = 0; i<vlistSize; i++)
    {
        // comparisons to get the highest and lowest xyz vector coordinates
        // X dimensions
        if(vectorList[i].getX() > maxX)
            maxX = vectorList[i].getX();
        if(vectorList[i].getX() < minX)
            minX = vectorList[i].getX();

        // Y dimensions
        if(vectorList[i].getY() > maxY)
            maxY = vectorList[i].getY();
        if(vectorList[i].getX() < minY)
            minY = vectorList[i].getY();

        // Z dimensions
        if(vectorList[i].getZ() > maxZ)
            maxZ = vectorList[i].getZ();
        if(vectorList[i].getX() < minZ)
            minZ = vectorList[i].getZ();
    }



}


