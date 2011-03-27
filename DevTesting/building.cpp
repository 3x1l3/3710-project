///\brief Class to encapsulate creation and drawing of a single building object in OpenGL
///\author Jason Racine
///\date Mar 27

#include "building.h"

Building::Building(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
  
  xSize = 1.0;
  ySize = 1.0;
  zSize = 1.0;
  
  _red = 0.3;
  _green = 0.3;
  _blue = 0.3;
  
}

Building::~Building()
{
}

void Building::SetOrigin(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

void Building::SetScale(float sX, float sY, float sZ)
{
  xSize = sX;
  ySize = sY;
  zSize = sZ;
}

void Building::Draw()
{
   glPushMatrix();
   glPushAttrib(GL_CURRENT_COLOR); //may or may not work
   glTranslatef(x, ySize / 2 , z);  // ySize/2 because we only need to scale up half the vertical height of the object
   glScalef(xSize, ySize, zSize);
   glColor3f(_red, _green, _blue);
   glutSolidCube(1.0);
   glPopAttrib();			//matched with PushAttrib above.
   glPopMatrix();
}

void Building::SetColor(float r , float g , float b )
{
  _red = r;
  _green = g;
  _blue = b;
}

