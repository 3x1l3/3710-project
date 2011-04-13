

#ifndef SPHEREBUILDING_H
#define SPHEREBUILDING_H


#include "building.h"

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


class SphereBuilding : public Building
{
  public:
    SphereBuilding(float x = 0, float y = 0, float z = 0);
    ~SphereBuilding();

    void Draw();
};

#endif
