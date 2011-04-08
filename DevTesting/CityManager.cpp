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
  
  roadWidth = 15;
  
  cityBlocks.clear();
  
}

CityManager::~CityManager()
{

}
void CityManager::setRoadWidth(int newWidth)
{
  roadWidth = newWidth;
}
void CityManager::AddCityBlock(CityBlock* newBlock)
{
  cityBlocks.push_back(newBlock);
}

CityBlock* CityManager::BlockAt(int index)
{
  return cityBlocks.at(index);
}


void CityManager::Draw()
{
   glPushMatrix();
   
   //translate the whole city to the specified coordinates
   glTranslatef(x_coord, y_coord, z_coord);
  
   int size = cityBlocks.size();
   
  
   //draw our ground plane)
   glColor3f(1.0, 1.0, 0.1);
   glBegin(GL_QUADS);
   glVertex3f(0-15, -0.01, 0-15);
   glVertex3f(1.7*size, -0.01, 0-15);
   glVertex3f(1.7*size, -0.01, 1.7*size);
   glVertex3f(0-15, -0.01, 1.7*size);
   glEnd();
   
   for(unsigned i = 0; i < cityBlocks.size(); i++)
   {
     cityBlocks[i]->setRoadWidth(roadWidth);
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
