/**
* @file material.h
* @brief contains all declarations for the material class
*/

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <string>

using namespace std;
/**
* This class contains the material proprties for a model
* To be used with model class
*/
class material
{
public:
    /**
    * Default constructor of material
    */
    material();

    // override constructor
    /**
    * contructor of material with given parameters
    * @param matIdToSet material ID
    * @param densityToSet density of the material
    * @param colourToSet colour of the material
    * @param nameToSet namer of the material
    */
    material(int matIdToSet, int densityToSet, string colourToSet, string nameToSet);

    // destructor

    /**
    * Default destuctor
    */
    ~material();

    /* Get functions */

    /**
    * Gets the material ID
    */
    int getMatId();
    /**
    * Gets the material density
    */
    int getDensity();
    /**
    * Gets the material colour
    */
    string getColour();
    /**
    * Gets the material name
    */
    string getMatName();

    /* Set functions*/

    /**
    * sets the material ID
    * @param matIdToSet new material ID
    */
    void setMatId(int matIdToSet);
    /**
    * sets the material denstiy
    * @param densityToSet new material denstiy
    */
    void setDensity(int densityToSet);
    /**
    * sets the material colour
    * @param colourToSet new material colour
    */
    void setColour(string colourToSet);
    /**
    * sets the material name
    * @param matNameToSet new material name
    */
    void setMatName(string matNameToSet);



private:

    int matId; ///< material ID
    int density; ///< density of material
    string colour; ///< colour of the material
    string matName; ///< name of the material

};

#endif // MATERIAL_H_INCLUDED
