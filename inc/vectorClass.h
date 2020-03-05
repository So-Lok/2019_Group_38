#ifndef VECTORCLASS_H_INCLUDED
#define VECTORCLASS_H_INCLUDED

class vectorClass
{
public:

    // constructor
    vectorClass();

    // override constructor
    vectorClass(int vectorId, float xCoord, float yCoord, float zCoord);


    // destructor
    ~vectorClass();

    // copy constructor
    vectorClass(vectorClass *vectorToCopy);

    // get functions

    int getId();

    float getX();
    float getY();
    float getZ();

    vectorClass getVector(int vectorId);

    // set functions

    void setId(int IdToSet);
    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);
    void setAll(int IdToSet, float newX, float newY, float newZ);

    // calculation functions
    float scalarProduct(vectorClass &vec1,vectorClass &vec2);
	vectorClass vectorProduct(vectorClass &vec1, vectorClass &vec2);

    //find magnitude
	float magnitude();
	//Adding vector
	vectorClass operator+(const vectorClass& vec2);
	//Subtracting vector
	vectorClass operator-(const vectorClass& vec2);
    // equal
    vectorClass& operator=(const vectorClass& vec2);


private:
    float xCoord;
    float yCoord;
    float zCoord;

    int vectorId;

};

#endif // VECTORCLASS_H_INCLUDED
