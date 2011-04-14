///\brief Class to encapsulate creation and drawing of a single building object in OpenGL
///\author Jason Racine
///\date Mar 27

#ifndef BUILDING_H
#define BUILDING_H

// This class is intended to be used in openGL,
// these are included here because openGL functions
// are needed by the class itself.
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <iostream>
#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>    
#include <string.h>  // For spring operations.


class Building
{
  public:
    Building(float x = 0, float y = 0, float z = 0);
    ~Building();
  
    void SetColor(float, float, float);
    void SetOrigin(float, float, float);
    void SetScale(float, float, float);
    virtual void Draw(GLenum mode) = 0;
    
    void setBuildingID(int newID);
    int getBuildingID();
    
    float GetRed();
    float GetGreen();
    float GetBlue();
    
    
  protected:
	
    float x, y, z;
    int buildingID;
    
    bool doRender;
    float xSize, ySize, zSize;
    float _red, _green, _blue;
};

#endif
