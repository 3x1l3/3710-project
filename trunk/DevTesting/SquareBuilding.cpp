

#include "SquareBuilding.h"

SquareBuilding::SquareBuilding(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
  
  xSize = 1.0;
  ySize = 1.0;
  zSize = 1.0;
  
  _red = 0.3;
  _green = 0.3;
  _blue = 0.36;
  
  buildingID = 00000;
  
  doRender = true;
  
}


SquareBuilding::~SquareBuilding()
{
}

void SquareBuilding::Draw()
{
   glPushMatrix();
   glPushAttrib(GL_CURRENT_COLOR); //may or may not work
   glTranslatef(x, ySize / 2 , z);  // ySize/2 because we only need to scale up half the vertical height of the object
   glScalef(xSize, ySize, zSize);
   
   //glColor3f(_red, _green, _blue);
   glMaterialf ( GL_FRONT_AND_BACK, GL_AMBIENT, 1.0) ;

   glutSolidCube(1.0);
   glPopAttrib();			//matched with PushAttrib above.
   glPopMatrix();
}


