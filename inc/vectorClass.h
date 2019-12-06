#ifndef VECTORCLASS_H_INCLUDED
#define VECTORCLASS_H_INCLUDED

class vectorClass
{
public:

    // constructor
    vectorClass();

    // override constructor for testing?
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

    // set functions

    float setX();
    float setY();
    float setZ();

    // calculation functions
    float dot_product(vectorClass &vec1,vectorClass &vec2);
	float cross_product(vectorClass &vec1, vectorClass &vec2);




private:
    float xCoord;
    float yCoord;
    float zCoord;

    int vectorId;

};

#endif // VECTORCLASS_H_INCLUDED
