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
    /* Function variables used to store values*/
    int id;
    /* Temporary material variables*/
    int density;
    string colour;
    string name;

    /*Temporary vector variables */
    float xCoord;
    float yCoord;
    float zCoord;

    /*Temporary cell variables - id, type, */
    char type;
    // the number of vertex ids varies and therefore
    // there will need to be a for loop to store them depending on the type
    // of cell
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

        // For each line a new object will need to be created and then added to a vector list of the object
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
                //cout << line;
                stringstream ssline(line);
                ssline.ignore(1);
                ssline >> id >> type;

               // cout << id << " " << type << " ";



                if(type == 'h')
                {
                    ssline.ignore(3);
                    ssline >>  vId1 >>  vId2 >>  vId3 >>  vId4
                           >>  vId5 >>  vId6 >>  vId7 >>  vId8;

                    //cout <<  vId1 <<  vId2 <<  vId3 <<  vId4
                       //  <<  vId5 <<  vId6 <<  vId7 <<  vId8;
                }

                if(type == 't')
                {
                    ssline.ignore(3);
                    ssline >>  vId1 >>  vId2 >>  vId3 >>  vId4;
                }


                if(type == 'p')
                {
                    ssline.ignore(3);
                    ssline >>  vId1 >>  vId2 >>  vId3 >>  vId4 >>  vId5;
                }




            }





        }


    }
}

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
        cout << "Test:"
        << materials[i].getMatId() << " "
        << materials[i].getDensity() << " "
        << materials[i].getColour() << " "
        << materials[i].getMatName() << "\n";
    }
}






int model::getNumberOfVertices()
{
    return this->vectorList.size();
}
/*
// data type required model::getNumberOfCellsAndType();
// calculation of the model
// should use a object list of the vertices to calculate the centre
// vector model::calculateModelCentre()
{

}
*/
