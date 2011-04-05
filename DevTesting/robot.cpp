#include "robot.h"


Robot::Robot()
{
  this->pos_x = 0.0;
  this->pos_y = 0.0;
  this->pos_z = 0.0;
  
  this->antenna_angle = 0.0;
}

Robot::Robot(float x, float y, float z)
{
  this->pos_x = x;
  this->pos_y = y;
  this->pos_z = z;
  
  this->antenna_angle = 0.0;
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
	this->head_angle += 0.5;
      break;
    case 2:
      if (this->head_angle >= -90)
      this->head_angle -= 0.5;
      break;
      
    case 3:
      if (this->head_angle > 0)
	this->head_angle -= 0.5;
      else if (this->head_angle < 0)
	this->head_angle += 0.5;
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


void Robot::draw()
{
  this->antenna_rotate();
  this->head_rotate();
  
 GLUquadric* quad = gluNewQuadric();
   glPushMatrix();
    
    glTranslatef(this->pos_x, this->pos_y, this->pos_z);
    glRotatef(180, 0.0, 1.0, 0.0);
    
   //Body
   glPushMatrix();
   glScalef(0.75, 1.0, 0.75);
   glutSolidCube(1);
   glPopMatrix();
   
   //neck
   glPushMatrix();
   glTranslatef(0.0, 1.0, 0.0);
   glRotatef(90, 1.0, 0.0, 0.0);
   gluCylinder(quad, 0.25, 0.25, 0.5, 100, 100);
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
