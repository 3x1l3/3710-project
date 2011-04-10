#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include <vector>
#include <string>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <math.h>


using std::cout;
using std::endl;
using std::string;
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
    float eyefromat;
    float yaxis_rotation_pos;
    float xaxis_rotation_pos;
    float deye_z;
    float deye_x;
    bool default_view_set; 
    string state;
    void storeDefaultView();
    void viewRotateRight(float, float);
    void viewRotateLeft(float, float);
    
    
  public:
    Camera();
    Camera(float, float, float, float, float, float);
    ~Camera();
    void setLookat(float, float, float, float, float, float);
    void lookat();
    void rotate_right(float, float);
    void rotate_left(float, float);
    void rotate_up(float);
    void rotate_down(float);
    void walk(int);
    void moveCamera(std::vector<float>);
    void viewDefault();
    void viewBR(float, float);
    void viewBL(float, float);
    void viewFR(float, float);
    void viewFL(float, float);
    
    float getAt_y();
    float getAt_x();
    float getAt_z();
    
    float getEye_x();
    float getEye_y();
    float getEye_z();
    
    void setEye_x(float);
    void setEye_y(float);
    void setEye_z(float);
    
    void setAt_x(float);
    void setAt_y(float);
    void setAt_z(float);
    
    float getYAngle();
   
  
};

#endif
