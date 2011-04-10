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
  this->eyefromat = 5.0;
  this->default_view_set = false;
  this->yaxis_rotation_pos = 0.0;
  this->xaxis_rotation_pos = 0.0;
  this->state = "D";
  
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
  this->eyefromat = 5;
  this->yaxis_rotation_pos = 0.0;
  this->xaxis_rotation_pos = 0.0;
  this->state = "D";
}

void Camera::setLookat(float eyex, float eyey, float eyez, float atx, float aty, float atz)
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
  this->eyefromat = 5;
  
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
	    this->at_x, this->at_y, this->at_z,
	    this->up_x, this->up_y, this->up_z);
	      
	    
}



void Camera::walk(int direction) {
 
  switch (direction) {
    case 1:
      this->eye_x += this->at_x * 1.0;
     // this->at_x += this->eye_x;
      
      this->eye_z += this->at_z * 1.0;
     // this->at_z += this->eye_z;
      
    break;
    case 2:
     this->eye_x -= this->at_x * 1.0;
     this->eye_z -= this->at_z * 1.0; 
//      this->at_x += this->eye_x;
//      this->at_z += this->eye_z;
     
    break;
    case 4:
     //rotate_right(0.1);
      
    break;
    case 3:  
    // rotate_left(0.1);
    break;  
  }  
 
  
}

void Camera::setEye_x(float x) {
 this->eye_x = x; 
}

void Camera::setEye_y(float y) {
  this->eye_y = y;
}

void Camera::setEye_z(float z) {
 this->eye_z = z; 
}

void Camera::setAt_x(float x) {
  this->at_x = x;
}

void Camera::setAt_y(float y)
{
  this->at_y = y;
}
void Camera::setAt_z(float z)
{
  this->at_z = z;
}


void Camera::rotate_right(float robot_x, float robot_z) {
  
 
  if (this->eye_x == robot_x) {
      
    if (this->eye_z > robot_z)
      this->eye_x = robot_x - this->eyefromat;
    else if (this->eye_z < robot_z)
      this->eye_x = robot_x + this->eyefromat;
    
    this->eye_z = robot_z;
    
    
  }
  else if (this->eye_z == robot_z) {
 
    if (this->eye_x > robot_x)
      this->eye_z = robot_z + this->eyefromat;
    else if (this->eye_x < robot_x)
      this->eye_z = robot_z - this->eyefromat;
    
    this->eye_x = robot_x;
    
  }
  
  this->viewRotateRight(robot_x, robot_z);

}

void Camera::rotate_left(float robot_x, float robot_z) {
  
  if (this->eye_x == robot_x) {
    
    if (this->eye_z > robot_z)
      this->eye_x = robot_x + this->eyefromat;
    else if (this->eye_z < robot_z)
      this->eye_x = robot_x - this->eyefromat;
    
    this->eye_z = robot_z;
    
    
  }
  else if (this->eye_z == robot_z) {
   
    if (this->eye_x > robot_x)
      this->eye_z = robot_z - this->eyefromat;
    else if (this->eye_x < robot_x)
      this->eye_z = robot_z + this->eyefromat;
    
    this->eye_x = robot_x;
    
  }
  
 
  this->viewRotateLeft(robot_x, robot_z);
  
}

void Camera::moveCamera(std::vector< float > forwardVec)
{
  this->eye_x -= (forwardVec[0] * -1);
  this->eye_y -= (forwardVec[1] * -1);
  this->eye_z -= (forwardVec[2] * -1);
 
}


void Camera::viewRotateRight(float robot_x, float robot_z) {

  float diff = this->eyefromat*2;
  
  if (this->eye_x > robot_x && this->eye_z < robot_z) {
      this->eye_z += diff;
      
  }
  
  else if (this->eye_x > robot_x && this->eye_z > robot_z) {
      this->eye_x -= diff;
  
      
  }
  
  else if (this->eye_x < robot_x && this->eye_z > robot_z) {
      this->eye_z -= diff;
     
  }
  
  else if (this->eye_x < robot_x && this->eye_z < robot_z) {
      this->eye_x += diff;
   
  }
 
}

void Camera::viewRotateLeft(float robot_x, float robot_z) {
 
  float diff = this->eyefromat*2;
  if (this->eye_x > robot_x && this->eye_z < robot_z) {
   this->eye_x -= diff;
  }
  
  else if (this->eye_x > robot_x && this->eye_z > robot_z) {
    this->eye_z -= diff;
  }
  
  else if (this->eye_x < robot_x && this->eye_z > robot_z) {
     this->eye_x += diff;
  }
  
  else if (this->eye_x < robot_x && this->eye_z < robot_z) {
    this->eye_z += diff;
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
void Camera::viewDefault()
{
  this->eye_x = this->deye_x;
  this->eye_z = this->deye_z;
  this->default_view_set = false;
  this->state = "D";
}

void Camera::storeDefaultView()
{
  if (!this->default_view_set) {
    this->deye_x = this->eye_x;
    this->deye_z = this->eye_z;
    this->default_view_set = true;
  }
}


void Camera::viewBL(float robot_x, float robot_z)
{
  this->storeDefaultView();
  this->eye_x = robot_x - this->eyefromat;
  this->eye_z = robot_z + this->eyefromat;
  this->state = "BL";
}

void Camera::viewBR(float robot_x, float robot_z)
{
  this->storeDefaultView();
  this->eye_x = robot_x + this->eyefromat;
  this->eye_z = robot_z + this->eyefromat;
  this->state = "BR";
}

void Camera::viewFL(float robot_x, float robot_z)
{
  this->storeDefaultView();
  this->eye_x = robot_x - this->eyefromat;
  this->eye_z = robot_z - this->eyefromat;
  this->state = "FL";
}
void Camera::viewFR(float robot_x, float robot_z)
{
  this->storeDefaultView();
  this->eye_x = robot_x + this->eyefromat;
  this->eye_z = robot_z - this->eyefromat;
  this->state = "FR";
   
}
