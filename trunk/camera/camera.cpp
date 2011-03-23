#include "camera.h"

Camera::Camera() {
  this->eye_x = 5.0;
  this->eye_y = 5.0;
  this->eye_z = 5.0;
  this->at_x = 0.0;
  this->at_y = 0.0;
  this->at_z = 0.0;
  this->up_x = 0.0;
  this->up_y = 1.0;
  this->up_z = 0.0;
  this->yaxis_rotation_pos = 0.0;
  this->xaxis_rotation_pos = 0.0;
  
}

Camera::~Camera() {


}

void Camera::lookat() {

    this->rotate(1);
    this->rotate(2);

  gluLookAt(this->eye_x, this->eye_y, this->eye_z,
	    this->at_x, this->at_y, this->at_z,
	    this->up_x, this->up_y, this->up_z);
   
}

/*
  Rotation by angle and direction
  yaxis = 1, xaxis = 2
*/
void Camera::rotate(int axis) {

 switch (axis) {
   case 1:
     glRotatef(this->yaxis_rotation_pos, 0.0, 1.0, 0.0);
    break;
   case 2:
     glRotatef(this->xaxis_rotation_pos, 1.0, 0.0, 0.0);
     break;
 }
 
 

}

//think this will need to be done with a directional vector
//

void Camera::walk(int direction) {
 
 
  
}


void Camera::rotate_right(float angle) {
  if(this->yaxis_rotation_pos >= 360) {
      this->yaxis_rotation_pos = static_cast<int>(this->yaxis_rotation_pos) % 360;
  } else {
   this->yaxis_rotation_pos += angle; 
  }
}

void Camera::rotate_left(float angle) {
    if(this->yaxis_rotation_pos <= 0) {
      this->yaxis_rotation_pos = 360 - this->yaxis_rotation_pos;
  } else {
   this->yaxis_rotation_pos -= angle; 
  }
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