///\brief took jasons city block class and created a city manager class with it
///\brief stores city blocks in a vector, and calls each ones draw function
///\date: mar 31 2011
///\author jordan peoples

#include "CityManager.h"

CityManager::CityManager()
{
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
  
  cityBlocks.clear();
  
}

CityManager::~CityManager()
{

}

void CityManager::AddCityBlock(CityBlock* newBlock)
{
  cityBlocks.push_back(newBlock);
}

void CityManager::Draw()
{
   glPushMatrix();
   
   //translate the whole city to the specified coordinates
   glTranslatef(x_coord, y_coord, z_coord);
   
   
   for(unsigned i = 0; i < cityBlocks.size(); i++)
   {
     cityBlocks.at(i)->Draw();
   }
   
   glPopMatrix();

}

void CityManager::SetOrigin(float x, float y, float z)
{
  x_coord = x;
  y_coord = y;
  z_coord = z;
}
