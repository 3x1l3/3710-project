#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include <vector>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <math.h>

using std::cout;
using std::endl;
class Camera {
  private:
    float eye_x;
    float eye_y;
    float eye_z;
    float at_x;
    float at_y;
    float at_z;
    float up_x;
    float up_y;
    float up_z;
    
    float yaxis_rotation_pos;
    float xaxis_rotation_pos;
    
    
    
  public:
    Camera();
    Camera(float, float, float, float, float, float);
    ~Camera();
    void lookat();
    void rotate_right(float);
    void rotate_left(float);
    void rotate_up(float);
    void rotate_down(float);
    void walk(int);
    
    float getAt_y();
    float getAt_x();
    float getAt_z();
    
    float getEye_x();
    float getEye_y();
    float getEye_z();
    
    float getYAngle();
   
  
};

#endif