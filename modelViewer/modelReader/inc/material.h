#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <string>

using namespace std;

class material
{
public:
    // constructor
    material();

    // override constructor
    material(int matIdToSet, int densityToSet, string colourToSet, string nameToSet);

    // destructor
    ~material();

    /* Get functions */

    int getMatId();
    int getDensity();
    string getColour();
    string getMatName();

    /* Set functions*/

    void setMatId(int matIdToSet);
    void setDensity(int densityToSet);
    void setColour(string colourToSet);
    void setMatName(string matNameToSet);



private:

    int matId;
    int density;
    string colour;
    string matName;

};

#endif // MATERIAL_H_INCLUDED
