// model.h

#ifndef MODEL_H
#define MODEL_H

// use vector to create object lists
#include <vector>


class model
{
  public:

  // constructor
  // constructor should read a .vtk file
  model();

  //destructor
  ~model();

  //get functions
  int getNumberOfVertices();

  // needs data type
  getNumberOfCellsAndType();

  // Calculates the centre of the model using the vertices vector values
  vector calculateModelCentre();



  private:


  vector();
  material();
  cell();

}


#endif
