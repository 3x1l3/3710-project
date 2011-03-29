#ifndef ROBOT_H
#define ROBOT_H
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
class Robot {
  
  private:
    float pos_x;
    float pos_y;
    float pos_z;
    
    float antenna_angle;
    void antenna_rotate();
    
  public:
    
    Robot();
    Robot(float, float, float);
    ~Robot();
    void draw();
    void setX(float);
    void setY(float);
    void setZ(float);
    
    
  
  
};



#endif