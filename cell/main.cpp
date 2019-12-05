#include <iostream>
#include <cmath>
#include <math.h>

 float volume_of_tetra(vector3d vertices[]){

    vector3d a = vertices[0];
    vector3d b = vertices[1];
    vector3d c = vertices[2];
    vector3d d = vertices[3];

     vector3d x = a-d;
     vector3d y = b-d;
     vector3d z = c-d;

     vector3d ycrossz= y.console(z);

     volume = pow(volume, 2);
     volume = sqrt(volume)/6);

     return volume;

 }
using namespace std;

class cell
{
protected:

    int material;
    int vector3d;
    int corners;

public:

     double getvolume();


};



class tetrahedron: public cell
{
private:
    vector3d vertices[4];

public:

    double getvolume();

};


   double tetrahedron ::  getvolume()
   {


    vector3d a = vertices[0];
    vector3d b = vertices[1];
    vector3d c = vertices[2];
    vector3d d = vertices[3];

     vector3d x = a-d;
     vector3d y = b-d;
     vector3d z = c-d;

     vector3d ycrossz= y.console(z);

     volume = pow(volume, 2);
     volume = sqrt(volume/6);

     return volume;


    };



class hexahedron: public cell
{
private:
    int vertices[8];
public:

    double getvolume();
    double centergravity();

};

 double hexahedron ::  getvolume()
   {


    vector3d a = vertices[0];
    vector3d b = vertices[1];
    vector3d c = vertices[2];
    vector3d d = vertices[3];
    vector3d e = vertices[4];
    vector3d f = vertices[5];
    vector3d g = vertices[6];
    vector3d h  = vertices[7];

    vector3d tetra1[]= {points[0],point[2],point[3],point[5]};
    vector3d tetra2[]= {points[0],point[1],point[7],point[5]};
    vector3d tetra3[]= {points[0],point[2],point[4],point[5]};
    vector3d tetra4[]= {points[0],point[5],point[7],point[4]};
    vector3d tetra5[]= {points[2],point[5],point[7],point[6]};

    float vol_tet_1= volume_of_tetra[tetra1];
    float vol_tet_2= volume_of_tetra[tetra2];
    float vol_tet_3= volume_of_tetra[tetra3];
    float vol_tet_4= volume_of_tetra[tetra4];
    float vol_tet_5= volume_of_tetra[tetra5];


    set_volume(vol_tet_1+ vol_tet_2+ vol_tet_3+ vol_tet_4+ vol_tet_5);

    return get_volume();
   }






     float volume_of_tetra[tetra1]

     vector3d x = a-d;
     vector3d y = b-d;
     vector3d z = c-d;

     vector3d ycrossz= y.console(z);

     volume = pow(volume, 2);
     volume = sqrt(volume/6);

     return volume;


    };

class pyramid: public cell
{

private:
    int vertices[5];

public:
    double getvolume();
    double centergravity();

};



float pyramid::volume_calc(){

    vector3d a = vertices[0];
    vector3d b = vertices[1];
    vector3d c = vertices[2];
    vector3d d = vertices[3];
    vector3d e = vertices[4];


     vector3d x = a-d;
     vector3d y = b-d;
     vector3d z = c-d;

     vector3d ycrossz= y.console(z);

     volume = pow(volume, 2);
     volume = sqrt(volume)/6);
     set_volume

     return volume;

 }


 int main()
{

    cell *cell[3];
    tetrahedron t;
    hexahedron h;
    pyramid p;

    int i;

    cell[0] = &t;
    cell[1] = &h;
    cell[2] = &p;

    for( i = 0; i < 3; i++ )
    {
        cell[i]->setcolour( col );
        cout << "Vol of shape " << i << " is " << shapes[i]->getvolume() << endl;
    }




}


