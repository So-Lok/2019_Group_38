#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <numeric>

class vectorClass{
private:
	float  xCoord, yCoord, zCoord; //setting variable
	int vectorId; //setting integer for id

public:
	//constructor
	vectorClass();
	
	//deconstructor
	~vectorClass();
	
	//overide constructor
	vectorClass(int vectorId,float xCoord, float yCoord, float zCoord);
	
	//copy constructor
	vectorClass(vectorClass& vectorToCopy);
	
	//get function
	float get_X(); //get x value
	float get_Y(); //get y value
	float get_Z(); //get z value
	int get_ID(); //get id value
	
	//print vector
	void print_Vector(int vectorId, float* xCoord, float* yCoord, float* zCoord);
	
	//set function
	float set_X(float xCoord); //set x value
	float set_Y(float yCoord); //set y value
	float set_Z(float zCoord); //set z value
	void set_Value(int vectorId,float xCoord, float yCoord , float zCoord); //set value to the vector

	
	//calculation function
	
	//find magnitude
	float magnitude();
	//Adding vector
	vectorClass operator+(const vectorClass& vec2);
	//Subtracting vector
	vectorClass operator-(const vectorClass& vec2);
	//Dot product
	friend float dot_product(const vectorClass& vec1,vectorClass& vec2);
	//Cross product
	friend vectorClass cross_product(const vectorClass& vec1, vectorClass& vec2);
	


	








};
