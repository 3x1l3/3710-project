///\brief Class to encapsulate creation of a city block in OpenGL
///\author Jason Racine
///\date Mar 27

#include "cityblock.h"

CityBlock::CityBlock()
{
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
  
  buildings.clear();
  
}

CityBlock::~CityBlock()
{

}

void CityBlock::AddBuilding(Building* bld)
{
  buildings.push_back(bld);
}

void CityBlock::Draw()
{
   glPushMatrix();
   
   ///Draws ground area
   glTranslatef(x_coord, z_coord, z_coord);
   
   glColor3f(0.1, 0.1, 0.1);
   glBegin(GL_QUADS);
   glVertex3f(-5.0, 0.0, 5.0);
   glVertex3f(5.0, 0.0, 5.0);
   glVertex3f(5.0, 0.0, -5.0);
   glVertex3f(-5.0, 0.0, -5.0);
   glEnd();
   
   for(unsigned i = 0; i < buildings.size(); i++)
   {
     buildings.at(i)->Draw();
   }
   
   glPopMatrix();

}

void CityBlock::SetOrigin(float x, float y, float z)
{
  x_coord = x;
  y_coord = y;
  z_coord = z;
}
