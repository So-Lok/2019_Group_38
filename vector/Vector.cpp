#include "Vector.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <numeric>

//constructor
vectorClass::vectorClass() {

}

//deconstructor
vectorClass::~vectorClass() {
	
}

//overide constructor
vectorClass::vectorClass(int vectorIdIn,float xCoordIn,float yCoordIn,float zCoordIn) { 
	vectorId = vectorIdIn; //to set the value for testing, ID
	xCoord = xCoordIn; //set x value
	yCoord = yCoordIn; //set y value
	zCoord = zCoordIn; //set z value
}
//copy constructor 
vectorClass::vectorClass(vectorClass& vectorToCopy) { //in case you want to create a new class with the same fuction as vectorClass
	vectorId = vectorToCopy.vectorId; //set id value
	xCoord = vectorToCopy.xCoord; //set x value
	yCoord = vectorToCopy.yCoord; //set y value
	zCoord = vectorToCopy.zCoord; //set z value
}

//get function

//get id
int vectorClass::get_ID(){
	return vectorId; //get the id
}
//get x
float vectorClass::get_X() {
	return xCoord;//get x coordinate
}
//get y
float vectorClass::get_Y() {
	return yCoord;//get y coordinate
}
//get z
float vectorClass::get_Z() {
	return zCoord;//get z coordinate
}

//print vector
void vectorClass::print_Vector(int vectorIdIn, float* xCoordIn, float* yCoordIn, float* zCoordIn) {
	*xCoordIn = xCoord; //set the value to x coordinate 
	*yCoordIn = yCoord; //set the value to y coordinate
	*zCoordIn = zCoord; //set the vlaue to z coordinate
	//for example (1,&x,&y,&z)
	std::cout<< "vector(" << vectorIdIn << "," << xCoord << "," << yCoord << "," << zCoord << ")\n"; //print out the value
}
//set function

//set x
float vectorClass::set_X(float xCoordIn) {
	xCoord = xCoordIn; //set value to x coordinate
	return xCoord; 
}
//set y
float vectorClass::set_Y(float yCoordIn) {
	yCoord = yCoordIn; //set value to y coordinate
	return yCoord;
}
//set z
float vectorClass::set_Z(float zCoordIn) {
	zCoord = zCoordIn; //set value to z coordinate
	return zCoord;
}
//set value to the vector
void vectorClass::set_Value(int vectorIdIn, float xCoordIn, float yCoordIn, float zCoordIn) {
	vectorId = vectorIdIn; //set all the value to the variable in the vector
	xCoord = xCoordIn; //set to x 
	yCoord = yCoordIn; //set to y
	zCoord = zCoordIn; //set to z
}

//calculation function

//magnitude
float vectorClass::magnitude() {
	return sqrt((xCoord * xCoord) + (yCoord * yCoord) + (zCoord * zCoord)); //return the magnitude 
}

//dot product
float dot_product(const vectorClass& vec1, vectorClass& vec2) {
	float dotprod = ((vec1.xCoord * vec2.xCoord) + (vec1.yCoord * vec2.yCoord) + (vec1.zCoord * vec2.zCoord)); //calculate and set to the float variable.
	return dotprod; //return the variable
}

//cross product
vectorClass cross_product(const vectorClass& vec1, vectorClass& vec2) {
	vectorClass result; //create a vectorClass function to store the result
	result.set_X((vec1.yCoord * vec2.zCoord) - (vec2.yCoord * vec1.zCoord)); //calculate and set to the x coordinate
	result.set_Y((vec1.zCoord * vec2.xCoord) - (vec2.zCoord * vec1.xCoord)); //calculate and set to the y coordinate
	result.set_Z((vec1.xCoord * vec2.yCoord) - (vec2.xCoord * vec1.yCoord)); //calculate and set to the z coordinate
	return result; //return the result in the require format
}

//adding vector
vectorClass vectorClass::operator+(const vectorClass& vec2) {
	vectorClass result; //create a vectorClass function to store the result
	result.set_X(xCoord + vec2.xCoord); //calculate and set to the x coordinate
	result.set_Y(yCoord + vec2.yCoord); //calculate and set to the y coordinate
	result.set_Z(zCoord + vec2.zCoord); //calculate and set to the z coordinate
	return result; //return the result in the require format
}

//subtracting vector
vectorClass vectorClass::operator-(const vectorClass& vec2) {
	vectorClass result; //create a vectorClass function to store the result
	result.set_X(xCoord - vec2.xCoord); //calculate and set to the x coordinate
	result.set_Y(yCoord - vec2.yCoord); //calculate and set to the y coordinate
	result.set_Z(zCoord - vec2.zCoord); //calculate and set to the z coordinate
	return result; //return the result in the require format
}







