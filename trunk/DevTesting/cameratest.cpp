#define PROGRAM_TITLE "Final Project"
#define DISPLAY_INFO "Klassen, Chad   Racine, Jason    Jordan, Peoples   Shepley, Adam"

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

#include <stdio.h>
#include <math.h>

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

int roadWidth = 15;

CityManager* city;
int cityScale = 3;

float viewing_distance = 5.0; //camera is 5.0 from the robot

float forwardStepsTaken = 0;

int showMoveHint = 0;

float redClearColor = 0;
float greenClearColor = 1;
float blueClearColor = 100;


Robot* robot = new Robot(314.5, 0.5, 314.5);
Camera* camera = new Camera(robot->getX(),2.2, robot->getZ()+viewing_distance, robot->getX(), robot->getY(), robot->getZ());

static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}

/////////////////////////////////////////////////////////
// Routine which actually does the drawing             //
/////////////////////////////////////////////////////////
void CallBackRenderScene(void)
{
   //clearing the color so we can tell when the robot is able to turn left and right
   //made the sky turn red when he is able to turn
   glClearColor(redClearColor,greenClearColor,blueClearColor, 0); 
   
   // Need to manipulate the ModelView matrix to move our model around.
   glMatrixMode(GL_MODELVIEW);
   
   // Clear the color and depth buffers.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Move back to the origin
   glLoadIdentity();
   
   //cout << camera->getAt_x() <<  " " << camera->getAt_y() << " " << camera->getAt_z() << endl;
   camera->lookat();
   /*
   gluLookAt(3.0, 3.0, 3.0, 
	     0.0, 0.0, 0.0, 
	     0.0, 1.0, 0.0);
   */
   
    robot->draw();
   


    
   glPushMatrix();
  
     city->Draw();
  

   
   glPopMatrix();
   
   if(showMoveHint == 1)
   {
     redClearColor = 1;
     greenClearColor = 0;
     blueClearColor = 0;
   }
   else
   {
     redClearColor = 0;
     greenClearColor = 1;
     blueClearColor = 100;
   }

   // All done drawing.  Let's show it.
   glutSwapBuffers();
}


void myCBKey(unsigned char key, int x, int y)
{
   switch (key) {
     case 119: //forward w
     robot->moveFoward();
     camera->setLookat(camera->getEye_x(), 2.2, camera->getEye_z(), robot->getX(), robot->getY(), robot->getZ());
     camera->moveCamera(robot->getForwardVec());
     
     forwardStepsTaken += 0.5;
     
     if(fmod(forwardStepsTaken, 37) == 0)
     {
       showMoveHint = 1;
     }
     else
     {
       showMoveHint = 0;
     }
   
     
   break;
   
    case 115: //backwards
     break;
    case 97: //left a
      if(fmod(forwardStepsTaken, 37) == 0)
      {
	camera->rotate_left(robot->getX(), robot->getZ());
	robot->turnBodyLeft();
	robot->updateForwardVec(2);
      }
      
      break;
    case 100: //right d
      if(fmod(forwardStepsTaken, 37) == 0)
      {
	camera->rotate_right(robot->getX(), robot->getZ());
	robot->turnBodyRight();
	robot->updateForwardVec(1);
      }
      break;
    case 102:
        
   
   
      
      break;
    }
    
    //printf("%d", key);
    
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
      
    case 4:
      camera->viewDefault(robot->getX(), robot->getZ(), robot->getForwardVec());
      break;
    case 5:
      camera->viewBL(robot->getX(), robot->getZ());
     break;
    case 6:
      camera->viewBR(robot->getX(), robot->getZ());
      break;
    case 7:
      camera->viewFR(robot->getX(), robot->getZ());
      break;
    case 8:
      camera->viewFL(robot->getX(), robot->getZ());
      break; 
    
    case 102:
     //camera->rotate_right(0.1);
     
     
     
     robot->turnBodyRight();
    break;
    case 100:
      robot->turnBodyLeft();
      break;
    case 101: //up
      camera->rotate_up(0.5);
      break;
    case 103: //down
      camera->rotate_down(0.5);
      break;
    
  }
  

  
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
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,300.0f);

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
   GLfloat light_position[] = { 200.0, 400.0, 200.0, 0.5 };
   glShadeModel (GL_SMOOTH);

   glEnable(GL_LIGHTING);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_COLOR_MATERIAL);
   
   
   
   
   // Color to clear color buffer to.
   glClearColor(redClearColor,greenClearColor,blueClearColor, 0);/*(20.0/255.0, 20.0/255.0, 205.0/255.0, 0.0f)*/;

   // Depth to clear depth buffer to; type of test.
   glClearDepth(1.0);
   glDepthFunc(GL_LESS); 

   // Enables Smooth Color Shading; try GL_FLAT for (lack of) fun.
   glShadeModel(GL_SMOOTH);

   // Load up the correct perspective matrix; using a callback directly.
   CallBackResizeScene(Width,Height);
   
   //*******************************************************************************************//
   
   {   //Moved Building initialization here, so it doesn't remake the city randomly on every draw
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
   float buildingY = 0;
   float buildingZ = 0;
   
   float xSize = 1.0;
   float ySize = 5.0 * cityScale;
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
   bld->SetScale(xSize * cityScale, ySize * cityScale, zSize * cityScale);

   CityBlock *block = new CityBlock();
   block->AddBuilding(bld);
   
   block->AddBuilding( new Building(-2.0 * cityScale, 0.0 * cityScale, -1.0 * cityScale) );
   bld = new Building(3.0 * cityScale, 0.0 * cityScale, 4.0 * cityScale);
   bld->SetScale(2.5 * cityScale, 1.0 * cityScale, 1.5 * cityScale);
   block->AddBuilding(bld);
   
   bld = new Building(1.0);
   bld->SetScale(3.0 * cityScale, 3.0 * cityScale, 3.0 * cityScale);
   block->AddBuilding(bld);
   
   bld = new Building(-4.0, 0.0, 4.0);
   bld->SetScale(0.5 * cityScale, 7.0 * cityScale, 0.5 * cityScale);
   bld->SetColor(0, 7.0, 6.7);
   block->AddBuilding(bld);
   
   bld = new Building(-3.7, 0.0, 4.0);
   bld->SetScale(1.8 * cityScale, 4.0 * cityScale, 1.4 * cityScale);
   block->AddBuilding(bld);
   
   bld = new Building(-1.0, 0.0, 4.0);
   bld->SetScale(2.5 * cityScale, 3.0 * cityScale, 1.0 * cityScale);
   block->AddBuilding(bld);
   
   bld = new Building(-4.0, 0.0, -4.0);
   bld->SetScale(1.0 * cityScale, 10.0 * cityScale, 1.0 * cityScale);
   block->AddBuilding(bld);
   
   bld = new Building(3.0, 0.0, -3.1);
   bld->SetColor(1.0, 0.50, 0.50);
   bld->SetScale(2.7 * cityScale, 1.7 * cityScale, 2.9 * cityScale);
   block->AddBuilding(bld);
   
   bld = new Building(4.5, 0.0, -0.5);
   bld->SetColor(0.33, 0.33, 0.33);
   bld->SetScale(1.0 * cityScale, 6.0 * cityScale, 1.5 * cityScale);
   block->AddBuilding(bld);
   
   bld = new Building(-4.0, 0.0, 0.0);
   bld->SetColor(0.2, 0.2, 0.2);
   bld->SetScale(1.0 * cityScale, 4.0 * cityScale, 5.8 * cityScale);
   block->AddBuilding(bld);
   
   bld = new Building(2.9, 0.0, 2.0);
   bld->SetColor(0.3, 0.3, 0.47);
   bld->SetScale(1.0 * cityScale, 9.0 * cityScale, 1.3 * cityScale);
   block->AddBuilding(bld);
      
   /*
   ///Again
   glPushMatrix();
   glTranslatef(-2.0, 3.0, 3.0);
   glScalef(1.5, 3.0, 1.0);
   glutSolidCube(2.0);
   glPopMatrix();
   */
   
   
   city = new CityManager(); 
   
   CityBlock *b;
   for(int i = 0; i < 20; i++)
   {
     for(int j = 0; j < 20; j++)
     { 
       b = new CityBlock();
       
       int var = 0; 
       for(int jabber = 0; jabber < 4; jabber++)
       {
	 var = rand() % block->getBuildingCount();
	 b->AddBuilding( block->BuildingAt(var) );
       }
       
       //We want to give every building an ID number
       //syntax is ...QXXX where Q is the block is belongs to.
       //we assume a max of 999 buildings per block.
       //cout << b->getBuildingCount() << endl;
       for(int a = 0; a < b->getBuildingCount(); a++)
       {
	 b->BuildingAt(a)->setBuildingID((((j+1)+(i*20)) * 1000) + (a+1));
	 //cout << "iteration is " << a << endl;
       }
       b->setID(j+1 + (i*20));
       b->SetOrigin( i * (22+roadWidth), 0, j * (22+roadWidth)  );
       city->AddCityBlock( b );
       
       //cout << "Created City Block " << b->getID() << endl;
     }
   }
   city->setRoadWidth(roadWidth);

    
  }
   
   //*******************************************************************************************//
   
   
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


