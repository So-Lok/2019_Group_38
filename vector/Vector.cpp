#include "Vector.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <numeric>


/*myVector::myVector(std::vector<int> v) {

}*/

myVector::myVector(float new_x, float new_y, float new_z) 
	:x(new_x),y(new_y),z(new_z){}

myVector::~myVector() {
	std::cout << "Bye";
}
float myVector::get_x() {
	return x;
}
float myVector::get_y() {
	return y;
}
float myVector::get_z() {
	return z;
}  
float myVector::magnitude() {
	return sqrt((x * x) + (y * y) + (z * z));
}

float myVector::dot_product(const myVector& vec1, myVector& vec2) {
	return ((vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z));
}

float myVector::cross_product(const myVector& vec1, myVector& vec2) {
	
	vect.push_back((vec1.y*vec2.z)-(vec2.y*vec1.z));
	vect.push_back((vec1.z * vec2.x) - (vec2.z * vec1.x));
	vect.push_back((vec1.x * vec2.y) - (vec2.x * vec1.y));
	std::cout<< "<" <<vect[0]<< "," <<vect[1]<<","<< vect[2]<<">"<<"\n";
	return 0;
}










