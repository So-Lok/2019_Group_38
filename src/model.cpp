// model.cpp

#incldue model.h

//constructor
model::model();

// constructor with param of the vtk datafile
//model::model();

//destructor
model::~model();

int model::getNumberOfVertices();

// data type required model::getNumberOfCellsAndType();

// calculation of the model
// should use a object list of the vertices to calculate the centre
vector model::calculateModelCentre();
