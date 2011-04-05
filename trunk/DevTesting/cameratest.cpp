#define PROGRAM_TITLE "Assignment 1"
#define DISPLAY_INFO "Klassen, Chad"

#include <iostream>
#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>    
#include <string.h>  // For spring operations.

#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

#include "camera.h"
#include "building.h"
#include "cityblock.h"
#include "math.h"
#include "robot.h"
#include "CityManager.h"

using std::cout;
using std::endl;

// Some global variables.
// Window IDs, window width and height.
int Window_ID;
int Window_Width = 600;
int Window_Height = 400;

// Cube position and rotation speed variables.
float X_Rot   = 0.5f;  // Initially only rotate around X-axix.
float Y_Rot   = 0.0f;  // Later on you can use control keys to change
float X_Speed = 0.0f;  // the rotation.
float Y_Speed = 0.0f;
float Z_Off   =-5.0f;

int roadWidth = 5.0f;

Camera* camera = new Camera(0.0, 2.0, 5.0, 0.0, 0.0, -1.0);
Robot* robot = new Robot();

/////////////////////////////////////////////////////////
// Routine which actually does the drawing             //
/////////////////////////////////////////////////////////
void CallBackRenderScene(void)
{
  
   
   // Need to manipulate the ModelView matrix to move our model around.
   glMatrixMode(GL_MODELVIEW);
   
   // Clear the color and depth buffers.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Move back to the origin
   glLoadIdentity();
   
   
   camera->lookat();
   /*
   gluLookAt(3.0, 3.0, 3.0, 
	     0.0, 0.0, 0.0, 
	     0.0, 1.0, 0.0);
   */
    robot->setX(camera->getEye_x()+camera->getAt_x());
    robot->setY(camera->getEye_y()+camera->getAt_y()-1);
    robot->setZ(camera->getEye_z()+camera->getAt_z()-5);
    robot->draw();
   
  
   
  
 
   //////////TESTING Drawing city block ///////////////////
   
   glPushMatrix();
  
   /*
   ///Draws ground area
   glTranslatef(blockX, blockY, blockZ);
   
   glColor3f(0.1, 0.1, 0.1);
   glBegin(GL_QUADS);
   glVertex3f(-5.0, 0.0, 5.0);
   glVertex3f(5.0, 0.0, 5.0);
   glVertex3f(5.0, 0.0, -5.0);
   glVertex3f(-5.0, 0.0, -5.0);
   glEnd();
   */
      ///Draw a building
   float buildingX = 1.0;
   float buildingY = 0.0;
   float buildingZ = 0;
   
   float xSize = 1.0;
   float ySize = 5.0;
   float zSize = 1.0;
   
   /*
   glPushMatrix();
   glTranslatef(buildingX, buildingY/2, buildingZ);
   glScalef(xSize, ySize, zSize);
   glutSolidCube(1.0);
   glPopMatrix();
   */
   
   Building *bld = new Building();
   bld->SetOrigin(buildingX, buildingY, buildingZ);
   bld->SetScale(xSize, ySize, zSize);

   CityBlock *block = new CityBlock();
   block->AddBuilding(bld);
   
   block->AddBuilding( new Building(-2.0, 0.0, -1.0) );
   bld = new Building(3.0, 0.0, 4.0);
   bld->SetScale(2.5, 1.0, 1.5);
   block->AddBuilding(bld);
   
   bld = new Building(1.0);
   bld->SetScale(3.0, 3.0, 3.0);
   block->AddBuilding(bld);
   
   bld = new Building(-4.0, 0.0, 4.0);
   bld->SetScale(0.5, 7.0, 0.5);
   bld->SetColor(0, 7.0, 6.7);
   block->AddBuilding(bld);
   
   bld = new Building(-3.7, 0.0, 4.0);
   bld->SetScale(1.8, 4.0, 1.4);
   block->AddBuilding(bld);
      
   /*
   ///Again
   glPushMatrix();
   glTranslatef(-2.0, 3.0, 3.0);
   glScalef(1.5, 3.0, 1.0);
   glutSolidCube(2.0);
   glPopMatrix();
   */
   
   
   CityManager *city = new CityManager(); 
   
   CityBlock *b;
   for(int i = 0; i < 20; i++)
   {
     for(int j = 0; j < 20; j++)
     { 
       b = new CityBlock();
       *b = *block;
       b->SetOrigin( i * (10+roadWidth), 0, j * (10+roadWidth)  );
       city->AddCityBlock( b );
     }
   }
   city->setRoadWidth(roadWidth);
   city->Draw();
   
   glPopMatrix();
   
   ///////////////////////////////////////////////////////
   
   // All done drawing.  Let's show it.
   glutSwapBuffers();
}


void myCBKey(unsigned char key, int x, int y)
{
   switch (key) {
     case 119: //forward w
      camera->walk(1);
     break;
    case 115: //backward s
      camera->walk(2);
     break;
    case 97: //left a
      camera->walk(3);
      break;
    case 100: //right d
      camera->walk(4);
      break;
      
    }
    
    
}

void mySCBKey(int key, int x, int y) {
  
  switch (key)
  {
    case 1: //F1
      
      robot->turnHeadForward();
      break;
    case 2: //F2
    robot->turnHeadRight();
      break;
    case 3: //F3
      robot->turnHeadLeft();
      
      break;
    
    case 102:
     camera->rotate_right(0.1);
    break;
    case 100:
      camera->rotate_left(0.1);
      break;
    case 101: //up
      camera->rotate_up(0.5);
      break;
    case 103: //down
      camera->rotate_down(0.5);
      break;
    
  }
  
 printf("%d", key);
  
}




///////////////////////////////////////////////////////////////
// Callback routine executed whenever the window is resized. //
//////////////////////////////////////////////////////////////
void CallBackResizeScene(int Width, int Height)
{
   // Let's not core dump, no matter what.
   if (Height == 0)
      Height = 1;

   glViewport(0, 0, Width, Height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);

   Window_Width  = Width;
   Window_Height = Height;
}

////////////////////////////////////////////////////////
//   Setup your program before passing the control    //
//   to the main OpenGL event loop.                   //
////////////////////////////////////////////////////////
void MyInit(int Width, int Height) 
{
  
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 3.0, 3.0, 3.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_COLOR_MATERIAL);
   
   
   
   
   // Color to clear color buffer to.
   glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

   // Depth to clear depth buffer to; type of test.
   glClearDepth(1.0);
   glDepthFunc(GL_LESS); 

   // Enables Smooth Color Shading; try GL_FLAT for (lack of) fun.
   glShadeModel(GL_SMOOTH);

   // Load up the correct perspective matrix; using a callback directly.
   CallBackResizeScene(Width,Height);
}

///////////////////////////////////////////////////
// main() function.                              //
//   There are general steps in making           //
//   an OpenGL application.                      //
//   Inits OpenGL.                               //
//   Calls our own init function                 //
//   then passes control onto OpenGL.            //   
///////////////////////////////////////////////////
int main(int argc, char **argv)
{
  
  
   glutInit(&argc, argv);
   
   // To see OpenGL drawing, take out the GLUT_DOUBLE request.
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   // The following is for window creation.
   // Set Window size
   glutInitWindowSize(Window_Width, Window_Height);
   // Create and Open a window with its title.
   Window_ID = glutCreateWindow(PROGRAM_TITLE);

   // Register and install the callback function to do the drawing. 
   glutDisplayFunc(&CallBackRenderScene);

   // If there's nothing to do, draw.
   glutIdleFunc(&CallBackRenderScene);

   // It's a good idea to know when our window's resized.
   glutReshapeFunc(&CallBackResizeScene);

   // Register and install the callback function for
   // Some keys and special keys.
   glutKeyboardFunc(&myCBKey);
   glutSpecialFunc(&mySCBKey);

   // OK, OpenGL's ready to go.  Let's call our own init function.
   MyInit(Window_Width, Window_Height);
   
   // Print out a bit of help dialog.
   /*
   printf("\n%s\n\n", PROGRAM_TITLE);
   printf("Print out some helpful information here.\n");
   printf("When you program, you can also use\n");
   printf("printf to do debugging.\n\n");
*/
   // Above functions represents those you will do to set up your
   // application program.
   // Now pass off control to OpenGL.
   glutMainLoop(); 
   // Never returns.
   return 1; 
}


