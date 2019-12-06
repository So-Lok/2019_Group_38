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
	this->vectorId = vectorIdIn;
	this->xCoord = xCoordIn;
	this->yCoord = yCoordIn;
	this->zCoord = zCoordIn;
}
//copy constructor
vectorClass::vectorClass(vectorClass& vectorToCopy) {
	vectorId = vectorToCopy.vectorId;
	xCoord = vectorToCopy.xCoord;
	yCoord = vectorToCopy.yCoord;
	zCoord = vectorToCopy.zCoord;
}



//get function
int vectorClass::get_ID(){
	return vectorId;
}

float vectorClass::get_X() {
	return xCoord;
}

float vectorClass::get_Y() {
	return yCoord;
}

float vectorClass::get_Z() {
	return zCoord;
}

//set function
float vectorClass::set_X(float xCoordIn) {
	this->xCoord = xCoordIn;
	return xCoord;
}

float vectorClass::set_Y(float yCoordIn) {
	this->yCoord = yCoordIn;
	return yCoord;
}

float vectorClass::set_Z(float zCoordIn) {
	this->zCoord = zCoordIn;
	return zCoord;
}

void vectorClass::set_Value(int vectorIdIn, float xCoordIn, float yCoordIn, float zCoordIn) {
	this->vectorId = vectorIdIn;
	this->xCoord = xCoordIn;
	this->yCoord = yCoordIn;
	this->zCoord = zCoordIn;
}

//calculation function
float vectorClass::magnitude() {
	return sqrt((xCoord * xCoord) + (yCoord * yCoord) + (zCoord * zCoord));
}

float dot_product(const vectorClass& vec1, vectorClass& vec2) {
	float dotprod = ((vec1.xCoord * vec2.xCoord) + (vec1.yCoord * vec2.yCoord) + (vec1.zCoord * vec2.zCoord));
	return dotprod;
}

vectorClass cross_product(const vectorClass& vec1, vectorClass& vec2) {
	vectorClass result;
	result.set_X((vec1.yCoord * vec2.zCoord) - (vec2.yCoord * vec1.zCoord));
	result.set_Y((vec1.zCoord * vec2.xCoord) - (vec2.zCoord * vec1.xCoord));
	result.set_Z((vec1.xCoord * vec2.yCoord) - (vec2.xCoord * vec1.yCoord));
	return result;
}

vectorClass vectorClass::operator+(const vectorClass& vec2) {
	vectorClass result;
	result.set_X(xCoord + vec2.xCoord);
	result.set_Y(yCoord + vec2.yCoord);
	result.set_Z(zCoord + vec2.zCoord);
	return result;
}
vectorClass vectorClass::operator-(const vectorClass& vec2) {
	vectorClass result;
	result.set_X(xCoord - vec2.xCoord);
	result.set_Y(yCoord - vec2.yCoord);
	result.set_Z(zCoord - vec2.zCoord);
	return result;
}

//print function
void vectorClass::printV() {
	std::cout << "<" <<xCoord << ","<< yCoord<< "," << zCoord<< ">\n";
}







