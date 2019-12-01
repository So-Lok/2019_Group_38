// model.cpp

#incldue model.h

//constructor
model::model()

//destructor
model::~model();

// read file function, string could also be the path location of the model - file string nameOfModelfile
void model::readFile()
{
  // create a string variable to contain the information on each line
  string line;

  // input the file into the strean
  ifstream modelFile(ExampleModel1.mod);

  // conditional statement in case error occurs when opening thefile
  if(modelFile.is_open)
  {
    // loops until every line has been read
    // Loop will read and store data depending on the information in the file
    while(getline(modelFile,line))
    {

    }
  }
}







int model::getNumberOfVertices();

// data type required model::getNumberOfCellsAndType();

// calculation of the model
// should use a object list of the vertices to calculate the centre
vector model::calculateModelCentre();
