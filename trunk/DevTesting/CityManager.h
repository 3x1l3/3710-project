///\brief took jasons city block class and created a city manager class with it
///\brief stores city blocks in a vector, and calls each ones draw function
///\date: mar 31 2011
///\author jordan peoples

#ifndef CITYMANAGER_H
#define CITYMANAGER_H

#include <vector>
#include "cityblock.h"

using std::vector;

class CityManager
{
  public:
    CityManager();
    ~CityManager();
    
  void AddCityBlock(CityBlock* newBlock);
  void Draw();
  void SetOrigin(float x, float y, float z);
  void setRoadWidth(int newWidth);
  
  CityBlock* BlockAt(int index);
    
  private:
    //coordinates for the center of the City
    int x_coord, y_coord, z_coord;
    int roadWidth;
    vector<CityBlock*> cityBlocks;

};

#endif