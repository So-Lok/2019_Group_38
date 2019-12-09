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

// read file function, string could also be the path location of the model - file string nameOfModelfile
void model::readFile()
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
    ifstream modelFile("ExampleModel1.mod");

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

                    // derived class constructor
                    cell newCell(id, type, matId, vId1, vId2, vId3, vId4,
                                                        vId5, vId6, vId7, vId8);
                    cells.push_back(newCell);

                   // cout <<  vId1 <<  vId2 <<  vId3 <<  vId4
                        //r <<  vId5 <<  vId6 <<  vId7 <<  vId8;
                }

                // tetrahedron cell
                if(type == 't')
                {

                    ssline >>  vId1 >>  vId2 >>  vId3 >>  vId4;
                    // derived class constructor
                    cell newCell(id, type, matId, vId1, vId2, vId3, vId4);
                    cells.push_back(newCell);
                }

                // Pyramid cell
                if(type == 'p')
                {

                    ssline >>  vId1 >>  vId2 >>  vId3 >>  vId4 >>  vId5;
                    // derived class constructor
                    cell newCell(id, type, matId, vId1, vId2, vId3, vId4, vId5);
                    cells.push_back(newCell);
                }

            }

        }

    }


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


