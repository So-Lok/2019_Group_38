#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <numeric>

class myVector{
private:
	float x, y, z;

public:
	//myVector(std::vector<int> v);
	myVector(float new_x, float new_y, float new_z);
	std::vector<int> vect;
	~myVector();
	float get_x();
	float get_y();
	float get_z();
	float magnitude();
	float dot_product(const myVector& vec1,myVector& vec2);
	float cross_product(const myVector& vec1, myVector& vec2);

	








};
