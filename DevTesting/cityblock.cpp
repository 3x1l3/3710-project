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

Building* CityBlock::BuildingAt(int index)
{
  return buildings.at(index);
}


void CityBlock::Draw()
{
   glPushMatrix();
   
   ///Draws ground area
   glTranslatef(x_coord, y_coord, z_coord);
   
   //glPushAttrib(GL_CURRENT_COLOR);
   glColor3f(0.1, 0.68, 0.1);
   glBegin(GL_QUADS);
   glVertex3f(-5.0, 0.0, 5.0);
   glVertex3f(5.0, 0.0, 5.0);
   glVertex3f(5.0, 0.0, -5.0);
   glVertex3f(-5.0, 0.0, -5.0);
   glEnd();
   //glPopAttrib();
   
   //drawing the right side street
   glColor3f(1.0, 1.0, 0.1);
   glBegin(GL_QUADS);
   glVertex3f(5.0, 0.0, 10.0);
   glVertex3f(10.0, 0.0, 10.0);
   glVertex3f(10.0, 0.0, -10.0);
   glVertex3f(5.0, 0.0, -10.0);
   glEnd();
   
   //drawing the left side street
   glColor3f(1.0, 1.0, 0.1);
   glBegin(GL_QUADS);
   glVertex3f(-10.0, 0.0, 10.0);
   glVertex3f(-5.0, 0.0, 10.0);
   glVertex3f(-5.0, 0.0, -10.0);
   glVertex3f(-10.0, 0.0, -10.0);
   glEnd();
   
   //drawing the top street
   glColor3f(1.0, 1.0, 0.1);
   glBegin(GL_QUADS);
   glVertex3f(-5.0, 0.0, 10.0);
   glVertex3f(5.0, 0.0, 10.0);
   glVertex3f(5.0, 0.0, 5.0);
   glVertex3f(-5.0, 0.0, 5.0);
   glEnd();
   
   //drawing the bottom side street
   glColor3f(1.0, 1.0, 0.1);
   glBegin(GL_QUADS);
   glVertex3f(-5.0, 0.0, -5.0);
   glVertex3f(5.0, 0.0, -5.0);
   glVertex3f(5.0, 0.0, -10.0);
   glVertex3f(-5.0, 0.0, -10.0);
   glEnd();
   
   for(unsigned i = 0; i < buildings.size(); i++)
   {
     glColor3f( buildings.at(i)->GetRed(), buildings.at(i)->GetGreen(), buildings.at(i)->GetBlue() );
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

CityBlock& CityBlock::operator=(const CityBlock& righthand)
{
  if(*this == righthand)  //Avoid self assignment
    return *this;
  
  this->x_coord = righthand.x_coord;
  this->y_coord = righthand.y_coord;
  this->z_coord = righthand.z_coord;
  
  for(unsigned i = 0; i < righthand.buildings.size(); i++)
  {
    this->AddBuilding( righthand.buildings.at(i) );
  }
  
  return *this;
}

bool CityBlock::operator==(const CityBlock& righthand)
{
  if(this->x_coord == righthand.x_coord
    && this->y_coord == righthand.y_coord
    && this->z_coord == righthand.z_coord
    && this->buildings == righthand.buildings)
  {
    return true;
  }
    
  return false;
}



