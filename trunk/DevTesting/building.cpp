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
  _blue = 0.36;
  
  buildingID = 00000;
  
  doRender = true;
  
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

///   COLOR METHODS   ///

void Building::SetColor(float r , float g , float b )
{
  _red = r;
  _green = g;
  _blue = b;
}

float Building::GetBlue()
{
  return _blue;
}

float Building::GetGreen()
{
  return _green;
}

float Building::GetRed()
{
  return _red;
}

int Building::getBuildingID()
{
  return buildingID;
}

void Building::setBuildingID(int newID)
{
  buildingID = newID;
}

