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
  void setRoadWidth(int newWidth);
    
  CityBlock& operator=(const CityBlock &righthand);
  bool operator==(const CityBlock &righthand);
  
  Building* BuildingAt(int index);
  
  private:
    //Coordinates are for the center of the city block
    int x_coord, y_coord, z_coord;
    int roadWidth;
    vector<Building*> buildings;

};

#endif