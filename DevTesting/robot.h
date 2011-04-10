#ifndef ROBOT_H
#define ROBOT_H
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class Robot {
  

  private:
    float pos_x;
    float pos_y;
    float pos_z;
    float antenna_angle;
    float head_angle;
    float prev_head_angle;
    int head_position;
    vector<float> forward_vector;
    void antenna_rotate();
    float forward_amount;
    float body_angle;
    int body_position;
    void init();
    float currentForwardAngle;
    
 
    
  public:
    
    Robot();
    Robot(float, float, float);
    ~Robot();
    void draw();
    void setX(float);
    void setY(float);
    void setZ(float);
    float getX();
    float getY();
    float getZ();
    void turnHeadLeft();
    void turnHeadRight();
    void turnHeadForward();
    void head_rotate();
    void moveFoward();
    void turnBodyLeft();
    void turnBodyRight();
    void turnBodyForward();
    void body_rotate();
    void updateForwardVec(int);
    vector<float> getForwardVec();
  
  
};



#endif
