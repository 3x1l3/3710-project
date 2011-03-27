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

class Building
{
  public:
    Building(float x = 0, float y = 0, float z = 0);
    ~Building();
  
    void SetOrigin(float, float, float);
    void SetScale(float, float, float);
    void Draw();
    
  protected:
	
  private:
    float x, y, z;
    float xSize, ySize, zSize;
};

#endif