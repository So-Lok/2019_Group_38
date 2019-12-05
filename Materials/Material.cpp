
#include "Material.h"

string Material::getName() const
{
	return name;
}

void Material::setName(string name)
{
	this->name = name;
}

string Material::getColour() const
{
	return colour;
}
void Material::setColour(string colour)
{
	this->colour = colour;
}

float Material::getDensity() const
{
	return density;
}
void Material::setDensity( float density )
{
	this->density = density;
}

int Material::getId() const
{
	return id;
}

void Material::setId( int id )
{
	this->id = id;
}

///////////////////////////printoutdata///////////////////

void Material::ToString()
{
	cout << "The density of " << this -> name << " is " <<
		this -> density << " and " << this -> colour << " is its colour " << this -> id << " is the ID ";
}

/////////////////// set all value ////////////////////////

void Material::setAll(std::string name, std::string colour, float density, int id)
{
	this->name = name;
	this->colour = colour;
	this->density = density;
	this->id = id;
}

///////////////////////////////////constructor////////////////////
Material::Material(string name, string colour, float density, int id)
{
	this->name = name;
	this->colour = colour;
	this->density = density;
	this->id = id;
}

/////constructor default///
Material::Material()
{
	this->name = " ";
	this->colour = " ";
	this->density = 0;
	this->id = 0;

}

/////////////////////destructor///////////////////////

Material::~Material()

{
	
}















 

