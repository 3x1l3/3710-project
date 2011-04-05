///\brief Class to encapsulate creation of a city block in OpenGL
///\author Jason Racine
///\date Mar 27

#ifndef CITYBLOCK_H
#define CITYBLOCK_H

#include <vector>
#include "building.h"
using std::vector;

class CityBlock
{
  public:
    CityBlock();
    ~CityBlock();
    
  void AddBuilding(Building* bld);
  void Draw();
  void SetOrigin(float x, float y, float z);
    
  private:
    //Coordinates are for the center of the city block
    int x_coord, y_coord, z_coord;
    vector<Building*> buildings;

};

#endif