/**
* @file vectorClass.h
* @brief contains all declarations for the vector class
*/

#ifndef VECTORCLASS_H_INCLUDED
#define VECTORCLASS_H_INCLUDED

class vectorClass
{
public:

    // constructor
    /**
    * default constructor
    */
    vectorClass();

    // override constructor

    /**
    * vector constuctor with given ID and x y z coordinates
    */
    vectorClass(int vectorId, float xCoord, float yCoord, float zCoord);


    /**
    * default destructor
    */
    ~vectorClass();

    // copy constructor

    /**
    * copy constructor
    */
    vectorClass(vectorClass *vectorToCopy);

    // get functions
    /**
    * gets the vector's ID
    */
    int getId();
    /**
    * gets the vector's x coordinate
    */
    float getX();
    /**
    * gets the vector's y coordinate
    */
    float getY();
    /**
    * gets the vector's z coordinate
    */
    float getZ();

    //old
    //vectorClass getVector(int vectorId);

    // set functions


    /**
    * sets the ID of the vector
    * @param IdToSet new value for the vector ID
    */
    void setId(int IdToSet);
    /**
    * sets the x coordinate of the vector
    * @param newX new value for x coordinate
    */
    void setX(float newX);
    /**
    * sets the y coordinate of the vector
    * @param newY new value for y coordinate
    */
    void setY(float newY);
    /**
    * sets the z coordinate of the vector
    * @param newZ new value for z coordinate
    */
    void setZ(float newZ);
    /**
    * sets all parameters for a vector
    * @param IdToSet new ID value
    * @param newX new X value
    * @param newY new Y value
    * @param newZ new Z value
    */
    void setAll(int IdToSet, float newX, float newY, float newZ);

    // calculation functions
    /**
    * calculates the scalar/dot product between any two vectors
    * Is called using any vector even if it is not one of those in the product
    * @param vec1 the first vector
    * @param vec2 the second vector
    */
    float scalarProduct(vectorClass &vec1,vectorClass &vec2);

    /**
    * calculates the vector/cross product between any two vectors
    * Is called using any vector even if it is not one of those in the product
    * @param vec1 the first vector
    * @param vec2 the second vector
    */
	  vectorClass vectorProduct(vectorClass &vec1, vectorClass &vec2);

    //find magnitude
    /**
    * calculates the magnitude of the vector
    */
	  float magnitude();
	  //Adding vector
    /**
    * calculates the sum of 2 vectors, invoked with vec1 + vec2
    * @param vec2 this is the second vector term in the expression
    */
	  vectorClass operator+(const vectorClass& vec2);
	  //Subtracting vector
    /**
    * calculates the difference between 2 vectors, invoked with vec1 + vec2
    * @param vec2 this is the second vector term in the expression
    */
	  vectorClass operator-(const vectorClass& vec2);
    // equal
    /**
    * makes this vector equal to vector 2
    * @param vec2 this is the second vector term in the expression
    */
    vectorClass& operator=(const vectorClass& vec2);


private:
    float xCoord; ///< x coordinate of the vector
    float yCoord; ///< y coordinate of the vector
    float zCoord; ///< z coordinate of the vector

    int vectorId; ///< ID of the vector 

};

#endif // VECTORCLASS_H_INCLUDED
