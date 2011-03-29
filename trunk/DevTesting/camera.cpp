#include "camera.h"

Camera::Camera() {
  this->eye_x = 0.0;
  this->eye_y = 1.0;
  this->eye_z = 5.0;
  this->at_x = 0.0;
  this->at_y = 0.0;
  this->at_z = -1.0;
  this->up_x = 0.0;
  this->up_y = 1.0;
  this->up_z = 0.0;
  
  this->yaxis_rotation_pos = 0.0;
  this->xaxis_rotation_pos = 0.0;
  
}

Camera::Camera(float eyex, float eyey, float eyez, float atx, float aty, float atz)
{
  this->eye_x = eyex;
  this->eye_y = eyey;
  this->eye_z = eyez;
  this->at_x = atx;
  this->at_y = aty;
  this->at_z = atz;
  this->up_x = 0.0;
  this->up_y = 1.0;
  this->up_z = 0.0;
  
  this->yaxis_rotation_pos = 0.0;
  this->xaxis_rotation_pos = 0.0;
}



Camera::~Camera() {


}

float Camera::getYAngle() {
 return this->yaxis_rotation_pos; 
}

float Camera::getAt_y() {
  return this->at_y;
}

float Camera::getAt_x() {
  return this->at_x;
}

float Camera::getAt_z() {
  
 return this->at_z; 
}


float Camera::getEye_x() {
 return this->eye_x; 
}

float Camera::getEye_y() {
 return this->eye_y;
}

float Camera::getEye_z() {
 return this->eye_z; 
}

void Camera::lookat() {

  gluLookAt(this->eye_x, this->eye_y, this->eye_z,
	    this->eye_x+this->at_x, this->eye_y+this->at_y, this->eye_z+this->at_z,
	    this->up_x, this->up_y, this->up_z);
	    
}



void Camera::walk(int direction) {
 
  switch (direction) {
    case 1:
      this->eye_x += this->at_x * 1.0;
      this->eye_z += this->at_z * 1.0;
      
    break;
    case 2:
     this->eye_x -= this->at_x * 1.0;
     this->eye_z -= this->at_z * 1.0; 
     
    break;
    case 4:
     
      
    break;
    case 3:  
    
    break;  
  }  
 
  
}


void Camera::rotate_right(float angle) {

   this->yaxis_rotation_pos += angle; 
  this->at_x = sin(yaxis_rotation_pos);
  this->at_z = -cos(yaxis_rotation_pos);

}

void Camera::rotate_left(float angle) {
   this->yaxis_rotation_pos -= angle; 
  this->at_x = sin(yaxis_rotation_pos);
  this->at_z = -cos(yaxis_rotation_pos);
  
    
  
  
  
  
}

void Camera::rotate_down(float angle) {
  if(this->xaxis_rotation_pos >= 360) {
      this->xaxis_rotation_pos = static_cast<int>(this->xaxis_rotation_pos) % 360;
  } else {
   this->xaxis_rotation_pos += angle; 
  }
  
}

void Camera::rotate_up(float angle) {
      if(this->xaxis_rotation_pos <= 0) {
      this->xaxis_rotation_pos = 360 - this->xaxis_rotation_pos;
  } else {
   this->xaxis_rotation_pos -= angle; 
  }
}