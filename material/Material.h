#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <string>
using namespace std;

class Material {

private:
	string name;
	string colour;
	float density;
	int id;

public:

	string getName() const;
	void setName(string name);
	
	string getColour() const;
	void setColour(string color);

	float getDensity() const;
	void setDensity(float density);

	int getId() const;
	void setId( int id);

	/////////////////////////////// to set all value //////////////////////////////

	void setAll(std::string name, std::string colour, float density, int id);
	Material(string name, string colour, float density, int id);
	Material();
	~Material();
	void ToString();

	static int getNumOfMaterial();
	
};  

#endif

