#include "robot.h"


Robot::Robot()
{
  this->init();
}


Robot::Robot(float x, float y, float z)
{
 
  this->init();
  this->pos_x = x;
  this->pos_y = y;
  this->pos_z = z;
}

void Robot::init() {
  this->pos_x = 0.0;
  this->pos_y = 0.0;
  this->pos_z = 0.0;
  this->antenna_angle = 0.0;
  this->head_position = 3;
  this->body_position = 3;
  this->head_angle = 0.0f;
  this->body_angle = 0.0f;
  forward_vector.push_back(0.0);
  forward_vector.push_back(0.0);
  forward_vector.push_back(-1.0);
  this->currentForwardAngle = 0;
  this->forward_amount = 0.5;
}
void Robot::setX(float x)
{
  this->pos_x = x;
}
void Robot::setY(float y)
{
  this->pos_y = y;
}
void Robot::setZ(float z)
{
  this->pos_z = z;
}

float Robot::getX() {
    return this->pos_x;
}

float Robot::getY()
{
  return this->pos_y;
}
float Robot::getZ()
{
  return this->pos_z;
}


Robot::~Robot()
{

}

void Robot::antenna_rotate() {
  
  if (antenna_angle >= 360)
      this->antenna_angle = 0.0;
  else
      this->antenna_angle += 0.5;
}

void Robot::head_rotate() {

  switch(this->head_position) {
    case 1:
      if (this->head_angle <= 90)
	this->head_angle += 3.5;
      break;
    case 2:
      if (this->head_angle >= -90)
      this->head_angle -= 3.5;
      break;
      
    case 3:
      if (this->head_angle > 0)
	this->head_angle -= 3.5;
      else if (this->head_angle < 0)
	this->head_angle += 3.5;
      break;
    
  }
  
 
}

void Robot::turnHeadLeft()
{
  this->head_position = 1;
}
void Robot::turnHeadRight()
{
  this->head_position = 2;
}

void Robot::turnHeadForward()
{
  this->head_position = 3;
}
/////////////////////////BODY ROTATIONS/////////////////////////////////////////////
void Robot::body_rotate() {
  float angle_magnitude = 8.0;
  switch(this->body_position) {
    case 1:
      if (this->body_angle <= currentForwardAngle)
      {
	this->body_angle += angle_magnitude;
	if(this->body_angle > currentForwardAngle)
	{
	  this->body_angle=currentForwardAngle;
	}
      }
      
      break;
      
    case 2:
      if (this->body_angle >= currentForwardAngle)
      {
	this->body_angle -= angle_magnitude;
	if(this->body_angle < currentForwardAngle)
	{
	  this->body_angle=currentForwardAngle;
	}
      }
      break;
      
    case 3:
      if (this->body_angle > currentForwardAngle)
	this->body_angle -= angle_magnitude;
      else if (this->body_angle < currentForwardAngle)
	this->body_angle += angle_magnitude;
      break;
    
  }
  
 
}


void Robot::turnBodyLeft()
{
  this->body_position = 1;
  currentForwardAngle += 90;
}
void Robot::turnBodyRight()
{
  this->body_position = 2;
  currentForwardAngle -= 90;
}

void Robot::turnBodyForward()
{
  this->body_position = 3;
}

/////////////////////////BODY ROTATIONS/////////////////////////////////////////////

/*
  direction = 1 right
  direction = 2 left
*/
void Robot::updateForwardVec(int direction)
{
  
  if (this->forward_vector[0] != 0.0) {
    
    if (direction == 1) {
      
      if (this->forward_vector[0] > 0.0)
	this->forward_vector[2] = 1.0;
      else if (this->forward_vector[0] < 0.0)
	this->forward_vector[2] = -1.0;
      
    } 
    else if (direction == 2) {
       if (this->forward_vector[0] > 0.0)
	 this->forward_vector[2] = -1.0;
       else if (this->forward_vector[0] < 0.0)
	 this->forward_vector[2] = 1.0;
    }
    
    this->forward_vector[0] = 0.0;
    
  }
  else if (this->forward_vector[2] != 0.0) {
  
    if (direction == 1) {
    
      if (this->forward_vector[2] > 0.0){
	this->forward_vector[0] = -1.0;
      }
      else if (this->forward_vector[2] < 0.0) {
	this->forward_vector[0] = 1.0;
      }
    } 
    else if (direction == 2) {
      
      if (this->forward_vector[2] > 0.0)
	this->forward_vector[0] = 1.0;
      else if (this->forward_vector[2] < 0.0) 
	this->forward_vector[0] = -1.0;
      
    }
    this->forward_vector[2] = 0.0;
    
  }
  
  
  
}



void Robot::moveFoward()
{
  
  this->pos_x += (this->forward_vector[0] * this->forward_amount);
  this->pos_y += (this->forward_vector[1] * this->forward_amount);
  this->pos_z += (this->forward_vector[2] * this->forward_amount);
 
}


std::vector< float > Robot::getForwardVec()
{
  return this->forward_vector;
}


void Robot::draw()
{
  
  this->antenna_rotate();
  this->head_rotate();
  this->body_rotate();
  
 GLUquadric* quad = gluNewQuadric();
   glPushMatrix();
    
    glTranslatef(this->pos_x, this->pos_y, this->pos_z);
    glRotatef(180, 0.0, 1.0, 0.0);
    glRotatef(this->body_angle, 0.0, 1.0, 0.0);
    
   //Body
   glPushMatrix();
   glPushAttrib(GL_COLOR_BUFFER_BIT);
   glScalef(0.75, 1.0, 0.75);
   glutSolidCube(1);
   glTranslatef(0.0, 0.0, 0.75);
   glColor3f(1.0, 0.8, 0.0);
   glBegin(GL_QUADS);
    glVertex3f(-0.25, 0.3, 0);
    glVertex3f(0.25, 0.3, 0);
    glVertex3f(0.25, -0.3, 0);
    glVertex3f(-0.25, -0.3, 0);
   glEnd();
   glTranslatef(0.0, 0.1, -1.50);
   glBegin(GL_TRIANGLES);
     glVertex3f(0.0, 0.0, 0.0);
     glVertex3f(0.3, -0.3, 0.0);
     glVertex3f(-0.3, -0.3, 0.0);
     glVertex3f(0.0, 0.3, 0.0);
     glVertex3f(0.3, 0.0, 0.0);
     glVertex3f(-0.3, 0.0, 0.0);
   glEnd();

   glPopAttrib();
   glPopMatrix();
   
   //neck
   glPushMatrix();
   glColor3f(0.2, 0.2, 0.5);
   glTranslatef(0.0, 1.0, 0.0);
   glRotatef(90, 1.0, 0.0, 0.0);
   gluCylinder(quad, 0.20, 0.20, 0.5, 100, 100);
   glTranslatef(1.0, 0.0, 0.0);
   glPopMatrix();
   
   //antenna
   glPushMatrix();
   glRotatef(this->antenna_angle, 0.0, 1.0, 0.0);
   glTranslatef(0.0, 1.4, 0.0);
   glRotatef(90, 1.0, 0.0, 0.0);
   glColor3f(0.2, 0.2, 0.5);
   gluCylinder(quad, 0.1, 0.1, 0.2, 100, 100);
   glPopMatrix();
   
   //eyes
   glPushMatrix();
   glRotatef(this->head_angle, 0.0, 1.0, 0.0);
   glTranslatef(-0.10, 1.1, 0.3);
   glutSolidSphere(0.05, 15, 15);
   glTranslatef(0.25, 0.0, 0.0);
   glutSolidSphere(0.05, 15, 15);
   glPopMatrix();
   
   //head
   glPushMatrix();
   
   glTranslatef(0.0, 1, 0.0);
   
   glColor3f(0.2, 0.5, 0.5);
   glRotatef(this->head_angle, 0.0, 1.0, 0.0);
   glutSolidCube(0.5);
   glPopMatrix();
  
   glPopMatrix();
  
}
