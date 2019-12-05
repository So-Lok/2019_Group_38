#include <iostream>
#include <string>
#include "Material.h"

using namespace std;
int main()
{
	Material fred;
	fred.ToString();
	fred.setName( "pop" );
	fred.setColour( "pink");
	fred.setDensity( 23 );
	fred.setId( 1 );
	fred.ToString();

	return 0;

}