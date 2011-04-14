
#include "Pylon.h"

Pylon::Pylon (float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
  
  xSize = 1.0;
  ySize = 1.0;
  zSize = 1.0;
  
  _red = 0.3;
  _green = 0.3;
  _blue = 0.36;
  
  buildingID = 00000;
  
  doRender = true;
  
}


Pylon::~Pylon ()
{
}

void Pylon::Draw(GLenum mode)
{
   glPushMatrix();
   glPushAttrib(GL_CURRENT_COLOR); //may or may not work

   //drawing the ring around the pylon
   glTranslatef(x, y , z); 
   glScalef(xSize, ySize, zSize);
   glTranslatef(0,1.0,0);
   glRotatef(90,1,0,0);
   glColor3f(.5f,.5f,.0f);
   glutSolidTorus(.1, .7, 10, 10);
   glRotatef(-90,1,0,0);
   glTranslatef(0,-1.0,0);
   
   //glColor3f(_red, _green, _blue);
   glMaterialf ( GL_FRONT_AND_BACK, GL_AMBIENT, 1.0) ;
    if (mode == GL_SELECT)
      glLoadName(this->getBuildingID());
   //drawring the bottom of the pylon
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(1.0f,45.0f,50.0f);
   glVertex3f(0,-0.5,0);
   glColor3f(1.0f,88.0f,5.0f);
   glVertex3f(-.5,1,.25);
   glColor3f(13.0f,0.0f,50.0f);
   glVertex3f(-.25,1,.5);
   glColor3f(1.0f,45.0f,50.0f);
   glVertex3f(.25,1,.5);
   glColor3f(4.0f,4.0f,0.0f);
   glVertex3f(.5,1,.25);
   glColor3f(67.0f,6.0f,0.0f);
   glVertex3f(.5,1,-.25);
   glColor3f(1.0f,45.0f,0.0f);
   glVertex3f(.25,1,-.5);
   glColor3f(1.0f,4.0f,50.0f);
   glVertex3f(-.25,1,-.5);
   glColor3f(1.0f,1.0f,50.0f);
   glVertex3f(-.5,1,-.25);
   glColor3f(56.0f,45.0f,50.0f);
   glVertex3f(-.5,1,.25);
   glEnd();
   
      if (mode == GL_SELECT)
      glLoadName(this->getBuildingID());
   //drawring the yop of the pylon
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(1.0f,45.0f,50.0f);
   glVertex3f(0,2.5,0);
   glColor3f(1.0f,88.0f,5.0f);
   glVertex3f(-.5,1,.25);
   glColor3f(13.0f,0.0f,50.0f);
   glVertex3f(-.25,1,.5);
   glColor3f(1.0f,45.0f,50.0f);
   glVertex3f(.25,1,.5);
   glColor3f(4.0f,4.0f,0.0f);
   glVertex3f(.5,1,.25);
   glColor3f(67.0f,6.0f,0.0f);
   glVertex3f(.5,1,-.25);
   glColor3f(1.0f,45.0f,0.0f);
   glVertex3f(.25,1,-.5);
   glColor3f(1.0f,4.0f,50.0f);
   glVertex3f(-.25,1,-.5);
   glColor3f(1.0f,1.0f,50.0f);
   glVertex3f(-.5,1,-.25);
   glColor3f(56.0f,45.0f,50.0f);
   glVertex3f(-.5,1,.25);
   glEnd();
   
   glPopAttrib();			//matched with PushAttrib above.
   glPopMatrix();
}


