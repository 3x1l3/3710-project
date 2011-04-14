///\brief took jasons city block class and created a city manager class with it
///\brief stores city blocks in a vector, and calls each ones draw function
///\date: mar 31 2011
///\author jordan peoples

#include "CityManager.h"


CityManager::CityManager()
{
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
  
  roadWidth = 15;
  
  cityBlocks.clear();
  
  
  //Alter these three variables when scaling the city size.
  //~Adam
  
  //DECIDES the space between ticks
  spacer = 4;
  
  blockSpacer = 18.277;
  
  betweenSpacer = 37;
}

CityManager::~CityManager()
{

}
void CityManager::setRoadWidth(int newWidth)
{
  roadWidth = newWidth;
}
void CityManager::AddCityBlock(CityBlock* newBlock)
{
  cityBlocks.push_back(newBlock);
}

CityBlock* CityManager::BlockAt(int index)
{
  return cityBlocks.at(index);
}


void CityManager::Draw(GLenum mode)
{
   glPushMatrix();
   
   //translate the whole city to the specified coordinates
   glTranslatef(x_coord, y_coord, z_coord);
  
   int size = cityBlocks.size();
   
  
   //draw our ground plane)
   glColor3f(1.0, 1.0, 0.1);
   glBegin(GL_QUADS);
   glVertex3f(0-15, -0.01, 0-15);
   glVertex3f(1.7*size, -0.01, 0-15);
   glVertex3f(1.7*size, -0.01, 1.7*size);
   glVertex3f(0-15, -0.01, 1.7*size);
   glEnd();
  
   int x = 0;
   int y = 0;

   
while(y < 19)
{

  
  //drawing our forward lines
   while( x < 185 )
   {
    
    glColor3f(1.0,0.2,0.45);
    glBegin(GL_QUADS);
    glVertex3f( 0   + (blockSpacer) + (y * betweenSpacer)  , 0.02 , 0 + x * spacer);
    glVertex3f( 0.3 + (blockSpacer) + (y * betweenSpacer), 0.02 , 0 + x * spacer);
    glVertex3f( 0.3 + (blockSpacer) + (y * betweenSpacer), 0.02, 1 + x * spacer);
    glVertex3f( 0   + (blockSpacer) + (y * betweenSpacer), 0.02 , 1 + x * spacer);
    glEnd();
    
    x++;
   }
   x = 0;
   //drawing our sideways lines
   
   while( x < 185 )
   {
    
    glColor3f(1.0,0.55,0.2);
    glBegin(GL_QUADS);
    
    glVertex3f(0 + x * spacer, 0.02, 0 + blockSpacer + (y * betweenSpacer));
    glVertex3f(0 + x * spacer, 0.02, 0.3 + blockSpacer + (y * betweenSpacer));
    glVertex3f(1 + x * spacer, 0.02, 0.3 + blockSpacer + (y * betweenSpacer));
    glVertex3f(1 + x * spacer, 0.02, 0 + blockSpacer + (y * betweenSpacer));
    glEnd();
    
    x++;
   }
   
   
   x = 0;
   y++;

}
   for(unsigned i = 0; i < cityBlocks.size(); i++)
   {
     cityBlocks[i]->setRoadWidth(roadWidth);
     cityBlocks.at(i)->Draw(mode);
   }
   
   glPopMatrix();

}

void CityManager::SetOrigin(float x, float y, float z)
{
  x_coord = x;
  y_coord = y;
  z_coord = z;
}
