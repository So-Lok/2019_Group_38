#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <numeric>
#include "Vector.h"

int main() {
	//setting a float
	float x, y, z;
	//setting a class function
	vectorClass v1,v2,v3,v4,v5,v6;
	//set value
	v1.set_Value(1,10, 100, 1000);
	v2.set_Value(2, 1, 1, 1);
	//get value
	std::cout << "This is the result by using the function set_value() and then get() function ";
	std::cout << "ID:" << v1.get_ID() << " X:" << v1.get_X() << " Y:" << v1.get_Y() << " Z:" << v1.get_Z()<< "\n";
	std::cout << "-------------------------------------------------------------------------------------------\n";
	//print vector
	std::cout << "This is the example of printing ";
	v1.print_Vector(1, &x, &y, &z);
	std::cout << "-------------------------------------------------------------------------------------------\n";
	//get magnitude
	std::cout << "The magnitude of this vector is " << v1.magnitude()<<"\n";
	std::cout << "-------------------------------------------------------------------------------------------\n";
	//adding vector
	v3 = v1 + v2;
	std::cout << "The result by adding vector v1 and v2 is"<< " X:" << v3.get_X() << " Y:" <<v3.get_Y() << " Z:" << v3.get_Z() << "\n";
	std::cout << "-------------------------------------------------------------------------------------------\n";
	//subtract vector
	v4 = v1 - v2;
	std::cout << "The result by subtracting vector v1 and v2 is" << " X:" << v4.get_X() << " Y:" << v4.get_Y() << " Z:" << v4.get_Z() << "\n";
	std::cout << "-------------------------------------------------------------------------------------------\n";
	//dot product
	std::cout <<"The dot product of vector v1 and v2 is " <<dot_product(v1, v2)<<"\n";
	std::cout << "-------------------------------------------------------------------------------------------\n";
	//cross product
	v5 = cross_product(v1, v2);
	std::cout << "The result of cross product is ";
	v5.print_Vector(5, &x, &y, &z);
	std::cout << "-------------------------------------------------------------------------------------------\n";





	

	
	
	




}
	

