#define PROGRAM_TITLE "Final Project"
#define DISPLAY_INFO "Klassen, Chad   Racine, Jason    Jordan, Peoples   Shepley, Adam"
#define SIZE 512

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

#include "ConeBuilding.h"
#include "SquareBuilding.h"
#include <vector>
#include "TorusBuilding.h"
#include "SphereBuilding.h"
#include "Pylon.h"

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

float turnArrowExtraRot = 0;

int turned = 0;
float robotInitialX = 314.5;
float robotInitialZ = 314.5;

bool gamePaused;

Robot* robot = new Robot(robotInitialX, 0.5, robotInitialZ);
Camera* camera = new Camera(robot->getX(),1.5, robot->getZ()+viewing_distance, robot->getX(), robot->getY(), robot->getZ());


bool arrowDirection = false;
vector<int> destroyed;

static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}

static void drawTurningArrows()
{
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    
    //based off of where we're looking
    if(!arrowDirection)
    {
      glTranslatef( robot->getX() - 1, robot->getY() + 1, robot->getZ());
      glRotatef(-90.0, 0.0, 1.0, 0.0);
    }
    else
    {
      glTranslatef( robot->getX(), robot->getY() + 1, robot->getZ() - 1);
      glRotatef(-180.0, 0.0, 1.0, 0.0);
    }
    glutSolidCone(0.25, 0.7, 20, 20);
  glPopMatrix();
  glPushMatrix();
  
  //setup based on crossroad direction
  if(!arrowDirection)
  {
    glTranslatef( robot->getX() + 1, robot->getY() + 1, robot->getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
  }
  else
    glTranslatef( robot->getX(), robot->getY() + 1, robot->getZ()+1);
    glutSolidCone(0.25, 0.7, 20, 20);
  glPopMatrix();

}


/////////////////////////////////////////////////////////
// Routine which actually does the drawing             //
/////////////////////////////////////////////////////////
void CallBackRenderScene(void)
{
  if(gamePaused) { return; } 
  
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

    robot->draw();
   


    
   glPushMatrix();
  
   city->Draw(GL_RENDER);  

   
   glPopMatrix();
   
   if(showMoveHint == 1)
   {
     redClearColor = 1;
     greenClearColor = 0;
     blueClearColor = 0;
     glPushMatrix();

     drawTurningArrows();
     glPopMatrix();
  }
   else
   {
     redClearColor = 0;
     greenClearColor = 0.3;
     blueClearColor = 1.0;
   }

  
   // All done drawing.  Let's show it.
   glutSwapBuffers();
}


void myCBKey(unsigned char key, int x, int y)
{
    std::vector<float> test;
   
   if(key != 'p' && gamePaused)
   {
     return;
   }
  
   switch (key) {
     case 'z': //forward z
     robot->moveFoward();
     camera->setLookat(camera->getEye_x(), 1.5, camera->getEye_z(), robot->getX(), robot->getY(), robot->getZ());
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
     //changes the x pos of robbot by negative 0.5
     robot->moveBackward();
     
     camera->setLookat(camera->getEye_x(), 1.5, camera->getEye_z(), robot->getX(), robot->getY(), robot->getZ());
     
     //get the forwaed vector and put it into a local variable test
     test.push_back(robot->getForwardVec()[0]);
     test.push_back(robot->getForwardVec()[1]);
     test.push_back(robot->getForwardVec()[2]);
     //invert the forward vector to make it a backwards vector
     test[0] = -test[0];
     test[1] = -test[1];
     test[2] = -test[2];
     //send the test vector with the backwards vector into the move camera function the camera can follow.
     camera->moveCamera(test);
     
     //following code is the same as the forward case
     forwardStepsTaken -= 0.5;
     
     if(fmod(forwardStepsTaken, 37) == 0)
     {
       showMoveHint = 1;
     }
     else
     {
       showMoveHint = 0;
     }
     
     
     
     break;
    case 'q': //left q
      if(fmod(forwardStepsTaken, 37) == 0)
      {
	arrowDirection = !arrowDirection;
	camera->rotate_left(robot->getX(), robot->getZ());
	robot->turnBodyLeft();
	robot->updateForwardVec(2);
	turnArrowExtraRot+=1;
	turned = 1;
      }
      
      break;
    case 'a': //right a
      if(fmod(forwardStepsTaken, 37) == 0)
      {
	arrowDirection = !arrowDirection;
	camera->rotate_right(robot->getX(), robot->getZ());
	robot->turnBodyRight();
	robot->updateForwardVec(1);
	turnArrowExtraRot+=1;
	turned = 1;
      }
      break;
    case 102:
        
   
   
      
      break;
      
    case 'p':
      {
	gamePaused = !gamePaused;
      }
      break;
      
    case 'r':
        robot = new Robot(robotInitialX, 0.5, robotInitialZ);
        camera = new Camera(robot->getX(),1.5, robot->getZ()+viewing_distance, robot->getX(), robot->getY(), robot->getZ());
	forwardStepsTaken = 0.0f;
	showMoveHint = 0;
	if(turned == 1)
	{
	  	arrowDirection = !arrowDirection;
		turned = 0;
	}
      break;
      
    }
    
    //printf("%d", key);
    
}

void mySCBKey(int key, int x, int y) {
  
  if(gamePaused)
  {
    return;
  }
  
  
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
    
    //right arrow key
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

/*
  Mouse Callback function for selecting

*/
void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLint names, *ptr;

   //printf ("hits = %d\n", hits);
   ptr = (GLint *) buffer; 
   for (i = 0; i < hits; i++) { /*  for each hit  */
      names = *ptr;
           ptr+=3;
      for (j = 0; j < names; j++) { /*  for each name */
          //cout << (*ptr) << endl;
         if(*ptr!=0) 
           destroyed.push_back(*ptr);
         ptr++;
      }
      //printf ("\n");
   }
   
  
}

void mouse(int button, int state, int x, int y)
{
   GLuint selectBuf[SIZE];
   GLint hits;
   GLint viewport[4];

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
   {
        glGetIntegerv (GL_VIEWPORT, viewport);

        glSelectBuffer (SIZE, selectBuf);
        glRenderMode(GL_SELECT);

        glInitNames();
        glPushName(0);


        glMatrixMode (GL_PROJECTION);
        glPushMatrix ();
        glLoadIdentity ();
                /*  create 5x5 pixel picking region near cursor location        */
        gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y), 
                        5.0, 5.0, viewport);
        //gluOrtho2D (-2.0, 2.0, -2.0, 2.0);
        gluPerspective(90.0f,(GLfloat)viewport[2]/(GLfloat)viewport[3],0.0,300.0f);
        //glOrtho(-2.0, 2.0, -2.0, 2.0, -300.0f, 300.f);
        city->Draw(GL_SELECT);


        glMatrixMode (GL_PROJECTION);
        glPopMatrix ();
        glFlush ();

        hits = glRenderMode (GL_RENDER);
        processHits (hits, selectBuf);

        glutPostRedisplay();
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
   
   
   
   
   
   city = new CityManager(); 
   
   CityBlock *b;
   for(int i = 0; i < 20; i++)
   {
     for(int j = 0; j < 20; j++)
     { 
       
	  SquareBuilding *bld = new SquareBuilding();
      bld->SetOrigin(buildingX, buildingY, buildingZ);
      bld->SetScale(xSize * cityScale, ySize * cityScale, zSize * cityScale);

      CityBlock *block = new CityBlock();
      //block->AddBuilding(bld);
      
    //    block->AddBuilding( new SquareBuilding(2.0 * cityScale, 0.0 * cityScale, 1.0 * cityScale) );
      bld = new SquareBuilding(3.0 * cityScale, 1.0 * cityScale, 4.0 * cityScale);
      bld->SetScale(2.5 * cityScale, 1.0 * cityScale, 1.5 * cityScale);
      block->AddBuilding(bld);
      
      bld = new SquareBuilding(1.0);
      bld->SetScale(3.0 * cityScale, 3.0 * cityScale, 3.0 * cityScale);
      block->AddBuilding(bld);
      
      bld = new SquareBuilding(-6.0, 0.0, 6.0);
      bld->SetScale(0.5 * cityScale, 7.0 * cityScale, 0.5 * cityScale);
      bld->SetColor(0, 7.0, 6.7);
      block->AddBuilding(bld);
      
      bld = new SquareBuilding(-3.7, 0.0, 8.0);
      bld->SetScale(1.8 * cityScale, 4.0 * cityScale, 1.4 * cityScale);
      block->AddBuilding(bld);
      
      bld = new SquareBuilding(-6.0, 0.0, 4.0);
      bld->SetScale(2.5 * cityScale, 3.0 * cityScale, 1.0 * cityScale);
      block->AddBuilding(bld);
      
      bld = new SquareBuilding(-8.0, 0.0, -4.0);
      bld->SetScale(1.0 * cityScale, 10.0 * cityScale, 1.0 * cityScale);
      block->AddBuilding(bld);
      
      bld = new SquareBuilding(5.0, 0.0, -5.1);
      bld->SetColor(1.0, 0.50, 0.50);
      bld->SetScale(2.7 * cityScale, 1.7 * cityScale, 2.9 * cityScale);
      block->AddBuilding(bld);
      
      bld = new SquareBuilding(7.5, 0.0, -4.5);
      bld->SetColor(0.33, 0.33, 0.33);
      bld->SetScale(1.0 * cityScale, 6.0 * cityScale, 1.5 * cityScale);
      block->AddBuilding(bld);
      
      bld = new SquareBuilding(-4.0, 0.0, 0.0);
      bld->SetColor(0.2, 0.2, 0.2);
      bld->SetScale(1.0 * cityScale, 4.0 * cityScale, 5.8 * cityScale);
      block->AddBuilding(bld);
      
      bld = new SquareBuilding(2.9, 0.0, 2.0);
      bld->SetColor(0.3, 0.3, 0.47);
      bld->SetScale(1.0 * cityScale, 9.0 * cityScale, 1.3 * cityScale);
      block->AddBuilding(bld);
      
      SphereBuilding *sphere = new SphereBuilding(-10, -1.8, -7.0);
      sphere->SetColor(0.3, 0.3, 0.47);
      sphere->SetScale(1.7 * cityScale, 1.7 * cityScale, 1.7 * cityScale);
      block->AddBuilding(sphere);
      
      sphere = new SphereBuilding(10, -1.8, 7.0);
      sphere->SetColor(0.3, 0.3, 0.47);
      sphere->SetScale(1.3 * cityScale, 1.3 * cityScale, 1.0 * cityScale);
      block->AddBuilding(sphere);
      
      bld = new SquareBuilding(1, 0.0, 1.0);
      bld->SetColor(0.3, 0.3, 0.47);
      bld->SetScale(1.0 * cityScale, 9.0 * cityScale, 1.3 * cityScale);
      block->AddBuilding(bld);
      
    //    TorusBuilding *torus = new TorusBuilding(-8, 5, -3.0);
    //    torus->SetColor(0.3, 0.3, 0.47);
    //    torus->SetScale(2.0 * cityScale, 2.0 * cityScale, 2 * cityScale);
    //    block->AddBuilding(torus);
      
      ConeBuilding *cone = new ConeBuilding(8, 0, 6.0);
      cone->SetColor(0.3, 0.3, 0.47);
      cone->SetScale(0.5 * cityScale, 0.5 * cityScale, 0.9 * cityScale);
      block->AddBuilding(cone);
      
      cone = new ConeBuilding(-4, 0, -7.5);
      cone->SetColor(0.3, 0.3, 0.47);
      cone->SetScale(0.7 * cityScale, 0.7 * cityScale, 0.5 * cityScale);
      block->AddBuilding(cone);
      
      Pylon *pylon = new Pylon(0, 0.7, -8.0);
      pylon->SetColor(0.3, 0.3, 0.47);
      pylon->SetScale(0.5 * cityScale, 0.5 * cityScale, 0.5 * cityScale);
      block->AddBuilding(pylon);
      
      pylon = new Pylon(3, 0.7, -2.0);
      pylon->SetColor(0.3, 0.3, 0.47);
      pylon->SetScale(0.5 * cityScale, 0.5 * cityScale, 0.5 * cityScale);
      block->AddBuilding(pylon);
      
	  
      /*
      ///Again
      glPushMatrix();
      glTranslatef(-2.0, 3.0, 3.0);
      glScalef(1.5, 3.0, 1.0);
      glutSolidCube(2.0);
      glPopMatrix();
      */
       
       
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
   glutMouseFunc(mouse);

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


