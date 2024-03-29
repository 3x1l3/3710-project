///\brief Class to encapsulate creation of a city block in OpenGL
///\author Jason Racine
///\date Mar 27

#ifndef CITYBLOCK_H
#define CITYBLOCK_H

#include <vector>
#include "building.h"
#include <time.h>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

class CityBlock
{
  public:
    CityBlock();
    ~CityBlock();
    
  void AddBuilding(Building* bld);
  void Draw(GLenum mode);
  void SetOrigin(float x, float y, float z);
  void setRoadWidth(int newWidth);
    
  CityBlock& operator=(const CityBlock &righthand);
  bool operator==(const CityBlock &righthand);
  
  void setID(int newID);
  int getID();
  int getBuildingCount();
  
  Building* BuildingAt(int index);
 
  private:
    //Coordinates are for the center of the city block
    int x_coord, y_coord, z_coord;
    int roadWidth;
    vector<Building*> buildings;
    int blockID;
    bool isBuildingDestroyed(int);
   
    
};

#endif