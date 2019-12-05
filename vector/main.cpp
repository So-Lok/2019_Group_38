#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <numeric>
#include "Vector.h"
int main() {
	myVector someVal(0,0,0);
	myVector vectar1(10, 100, 1000);
	myVector vectar2(70, 9000, 9000);
	someVal.cross_product(vectar1, vectar2);
}
