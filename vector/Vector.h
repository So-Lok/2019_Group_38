#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <numeric>

class vectorClass{
private:
	float  xCoord, yCoord, zCoord;
	int vectorId;

public:
	//constructor
	vectorClass();
	
	//deconstructor
	~vectorClass();
	
	//overide constructor
	vectorClass(int vectorId,float xCoord, float yCoord, float zCoord);
	
	//copy constructor
	vectorClass(vectorClass* vectorToCopy);
	
	//get function
	float get_X();
	float get_Y();
	float get_Z();
	int get_ID();
	
	//set function
	float set_X(float xCoord);
	float set_Y(float yCoord);
	float set_Z(float zCoord);
	void set_Value(int vectorId,float xCoord, float yCoord , float zCoord);
	
	//calculation function
	float magnitude();
	vectorClass operator+(const vectorClass& vec2);
	vectorClass operator-(const vectorClass& vec2);
	friend float dot_product(const vectorClass& vec1,vectorClass& vec2);
	friend vectorClass cross_product(const vectorClass& vec1, vectorClass& vec2);
	
	//print function if needed
	void printV();

	








};
