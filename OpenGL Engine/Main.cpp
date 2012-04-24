/*
  Written: 02 Mar 2010: JH
  Comment: 
*/

/********** Includes ****************************************/

#include <stdlib.h>
#include <vector>
#include <list>

#include "GLEngine.hpp"
#include "Math.hpp" // Math must be after GLEngine because GLEngine includes windows.h, which probably includes math which in turn is needed in Math.hpp
#include "Structs.hpp"

//#include "Shader.hpp"

#include "Controls.hpp"
#include "SDL.h"
#include "Model.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Light.hpp"
#include "CollisionEngine.hpp"
#include "Texture.hpp"
#include "Item.hpp"
#include "Weapons.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

const GLsizei
  iWindowWidth = 1200,
  iWindowHeight = 690;
GLfloat
  fRotateX = 0.0f,      // These are for navigating the scene
  fRotateY = 0.0f,
  fCameraY = -65.0f,
  fCameraZ = 25;
const GLfloat
  iRotateXSpeed = 0.5f, // Speed when navigating and moving
  iRotateYSpeed = 0.5f,
  fZoomSpeed = 0.5f,
  fMovementSpeed = 0.006f;
Uint8
  *pKeys = NULL;        // Holds keys that are pressed
MouseState
  state;
CollisionEngine
  colEngine;
Player
  *pColModel2;
Control
  *pActiveControl;  // E.g. buttons and sliders
bool
  boNavigating;     // Are we currently zooming or rotating the scene
std::vector<lineSegment>
  walls;            // All the walls in the game
std::vector<Projectile*>
  projectiles;
std::vector<Player*>
  enemies;
std::vector<Item*>
  items;
bool
  boLeftBtnCurrUp = true,
  boHandlingInventory = false;

/************************************************************/

GLvoid vInitProjMat(
  GLsizei iWidth,
  GLsizei iHeight
)
/*
  Written: 02 Mar 2010: JH
  Purpose: Set projection matrix to perspective
*/
{
  glViewport(0, 0, iWidth, iHeight);  // Set up viewport
  glMatrixMode(GL_PROJECTION);        // Set the matrix to projection
  glLoadIdentity();                   // Reset matrix
  gluPerspective(45.0f, (GLfloat)iWidth / (GLfloat)iHeight, 0.1f, 200.0f);  // Set up perspective
}

/************************************************************/

GLvoid vSetOrtho(
  GLsizei iWidth,
  GLsizei iHeight
)
/*
  Written: 20 Mar. 2010: JH
  Purpose: Set projection matrix to orthographic
*/
{
  glViewport(0, 0, iWidth, iHeight);  // Set up viewport
  glMatrixMode(GL_PROJECTION);        // Set the matrix to projection
  glLoadIdentity();                   // Reset matrix
  gluOrtho2D(0, iWidth, iHeight, 0);  // Set orthographic projection
}

/************************************************************/

void vInitLevel(
)
{
  walls.push_back(lineSegment(Point(2.0f, 0.0f, 0.0f) * 3, Point(2.0f, 0.0f, 2.5f) * 3));
  walls.push_back(lineSegment(Point(2.0f, 0.0f, 2.5f) * 3, Point(6.0f, 0.0f, 2.5f) * 3));
  walls.push_back(lineSegment(Point(6.0f, 0.0f, 2.5f) * 3, Point(6.0f, 0.0f, 5.5f) * 3));
  walls.push_back(lineSegment(Point(6.0f, 0.0f, 5.5f) * 3, Point(10.5f, 0.0f, 5.5f) * 3));
  walls.push_back(lineSegment(Point(10.5f, 0.0f, 5.5f) * 3, Point(10.5f, 0.0f, 11.5f) * 3));
  walls.push_back(lineSegment(Point(10.5f, 0.0f, 11.5f) * 3, Point(10.5f, 0.0f, 16.0f) * 3));
  walls.push_back(lineSegment(Point(10.5f, 0.0f, 16.0f) * 3, Point(2.0f, 0.0f, 16.0f) * 3));
  walls.push_back(lineSegment(Point(2.0f, 0.0f, 16.0f) * 3, Point(-4.5f, 0.0f, 16.0f) * 3));
  walls.push_back(lineSegment(Point(-4.5f, 0.0f, 16.0f) * 3, Point(-4.5f, 0.0f, 11.5f) * 3));
  walls.push_back(lineSegment(Point(-4.5f, 0.0f, 11.5f) * 3, Point(-8.0f, 0.0f, 11.5f) * 3));
  walls.push_back(lineSegment(Point(-8.0f, 0.0f, 11.5f) * 3, Point(-8.0f, 0.0f, 2.5f) * 3));
  walls.push_back(lineSegment(Point(-8.0f, 0.0f, 2.5f) * 3, Point(-2.0f, 0.0f, 2.5f) * 3));
  walls.push_back(lineSegment(Point(-2.0f, 0.0f, 2.5f) * 3, Point(-2.0f, 0.0f, 0.0f) * 3));
  walls.push_back(lineSegment(Point(-4.5f, 0.0f, 11.5f) * 3, Point(-2.0f, 0.0f, 11.5f) * 3));
  walls.push_back(lineSegment(Point(0.0f, 0.0f, 11.5f) * 3, Point(2.0f, 0.0f, 11.5f) * 3));
  walls.push_back(lineSegment(Point(2.0f, 0.0f, 11.5f) * 3, Point(5.0f, 0.0f, 11.5f) * 3));
  walls.push_back(lineSegment(Point(7.0f, 0.0f, 11.5f) * 3, Point(10.5f, 0.0f, 11.5f) * 3));
  walls.push_back(lineSegment(Point(2.0f, 0.0f, 11.5f) * 3, Point(2.0f, 0.0f, 16.0f) * 3));

  // Blob 1
  walls.push_back(lineSegment(Point(-4.5f, 0.0f, 5.0f) * 3, Point(-2.5f, 0.0f, 5.0f) * 3));
  walls.push_back(lineSegment(Point(-2.5f, 0.0f, 5.0f) * 3, Point(-2.5f, 0.0f, 6.0f) * 3));
  walls.push_back(lineSegment(Point(-2.5f, 0.0f, 6.0f) * 3, Point(-1.0f, 0.0f, 6.0f) * 3));
  walls.push_back(lineSegment(Point(-1.0f, 0.0f, 6.0f) * 3, Point(-1.0f, 0.0f, 7.5f) * 3));
  walls.push_back(lineSegment(Point(-1.0f, 0.0f, 7.5f) * 3, Point(-2.5f, 0.0f, 7.5f) * 3));
  walls.push_back(lineSegment(Point(-2.5f, 0.0f, 7.5f) * 3, Point(-2.5f, 0.0f, 8.5f) * 3));
  walls.push_back(lineSegment(Point(-2.5f, 0.0f, 8.5f) * 3, Point(-4.5f, 0.0f, 8.5f) * 3));
  walls.push_back(lineSegment(Point(-4.5f, 0.0f, 8.5f) * 3, Point(-4.5f, 0.0f, 5.0f) * 3));

  // Blob 2
  walls.push_back(lineSegment(Point(2.5f, 0.0f, 8.5f) * 3, Point(4.5f, 0.0f, 8.5f) * 3));
  walls.push_back(lineSegment(Point(4.5f, 0.0f, 8.5f) * 3, Point(4.5f, 0.0f, 10.5f) * 3));
  walls.push_back(lineSegment(Point(4.5f, 0.0f, 10.5f) * 3, Point(2.5f, 0.0f, 10.5f) * 3));
  walls.push_back(lineSegment(Point(2.5f, 0.0f, 10.5f) * 3, Point(2.5f, 0.0f, 8.5f) * 3));

  // Items
  items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(0, 0, 18), new Texture("itemicon.tga", "Item Icon")));  // Dummy object to test inventory
  items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(5, 0, 5), new Texture("itemicon2.tga", "Item Icon")));
  items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(15, 0, 22), new Texture("itemicon3.tga", "Item Icon")));
  items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(8, 0, 38), new Texture("itemicon4.tga", "Item Icon")));
  items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(35, 0, 12), new Texture("itemicon5.tga", "Item Icon")));
  items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(20, 0, 27), new Texture("itemicon6.tga", "Item Icon")));
//   items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(-5, 0, 8)));
//   items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(5, 0, 25)));
//   items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(-15, 0, 35)));
//   items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(5, 0, 35)));
//   items.push_back(new Ranged(0, 0, 0, 0, new Model("bearBox.3ds"), "Item on the ground", Point(-25, 0, 5)));
}

/************************************************************/

GLvoid vInitGL(
  GLsizei iWidth,
  GLsizei iHeight
)
/*
  Written: 02 Mar 2010: JH
*/
{
  Engine->vInitialize(iWidth, iHeight);

  vInitProjMat(iWidth, iHeight);
  glShadeModel(GL_SMOOTH);              // Smooth shading
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear he background color to black
  glEnable(GL_DEPTH_TEST);              // So that the faces are drawn in the correct order
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // If possible use the nicest(and slowest) perspective deformation
  glEnable(GL_PERSPECTIVE_CORRECTION_HINT);

	//glewInit();	// Initialize glew

  //enemies.push_back(new Player("Player 1", Point(0, 0, 20), "bearBox.3ds"));
  pColModel2 = new Player("Player 2", Point(0, 0, 0), "bearBox.3ds");

  // Initialize level
  vInitLevel();
}

/************************************************************/

void vDrawControls(
)
/*
  Written: 20 Mar. 2010: JH
  Purpose: Draw and update each control
*/
{
  for(std::list<Control*>::iterator it = Control::s_controlsListGet().begin(); it != Control::s_controlsListGet().end(); it++)
  {
    Control
      *pControl = (*it);

    pControl->vDrawControl();

    // If we are currently using a control and this control(pControl) isn't the one we are using,
    // we don't want to update it
    if(0 && pActiveControl != NULL && pActiveControl != pControl || boNavigating)
      continue;
    
		// If this control is being used set it to be active and handle events
		if(pControl->boUpdateControls(state))
		{
			pActiveControl = pControl;

			// Handle events
		}
		else if(pControl == pActiveControl) // If the control had no events and is the active one, that means that we
		{                                   // just stopped manipulating it and we no longer have an active control
			pActiveControl = NULL;
		}
		else
		{
			// Control had no events
		}
  }
}

/************************************************************/

GLvoid vDisplayFps(
  GLvoid
)
/*
  Written: 02 Mar 2010: JH
  Purpose: 
*/
{
  static long
    s_lastTime = SDL_GetTicks(),
    s_loops = 0;
  static GLfloat
    fFps = 0.0f;
  int
    iNewTime = SDL_GetTicks();

  if(iNewTime - s_lastTime > 100) // Only update every 100 milliseconds(computers are so fast that the difference can be 0, which will cause error)
  {
    float
      fNewFps = (float)s_loops / (float)(iNewTime - s_lastTime) * 1000.0f;

    fFps = (fFps + fNewFps) / 2.0f;

    s_lastTime = iNewTime;  // Update last time var
    s_loops = 0;            // Reset loops
  }

  Engine->vDrawText(5, 5, "OpenGL Engine - %.2f", fFps);

  s_loops++;  // Increment loops
}

/************************************************************/

GLvoid vDrawCube(
)
/*
  Written: 17 Mar. 2010: JH
  Purpose: 
*/
{
  glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Front Face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    // Back Face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

    // Left Face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);

    // Right Face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

    // Top Face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

    // Bottom Face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
  glEnd();
}

/************************************************************/

GLvoid vDrawPlane(
)
/*
  Written: 18 Sep. 2010: JH
  Purpose: 
*/
{
  glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(500.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(500.0f, 500.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 500.0f, 0.0f);

  glEnd();
}

/************************************************************/


Point screenToWorldCoords(
  int iX,
  int iY
)
{
  GLdouble
    pos3D_x,
    pos3D_y,
    pos3D_z;

  // arrays to hold matrix information
  GLdouble
    model_view[16];
  glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
  GLdouble
    projection[16];
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  GLint
    viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  // get 3D coordinates based on window coordinates
  gluUnProject(iX, iY, 1.0f,	model_view, projection, viewport,	&pos3D_x, &pos3D_y, &pos3D_z);

  // Calculate the point where y = 0
  Vector3f
    rayPoint1(0, -fCameraY, fCameraZ),
    rayPoint2((float)pos3D_x, (float)pos3D_y, (float)pos3D_z);

  float
    fT = rayPoint1[Y] / (rayPoint2[Y] - rayPoint1[Y]),
    fX = -(rayPoint1[X] + ((rayPoint2[X] - rayPoint1[X]) * fT)),
    fZ = rayPoint1[Z] + ((rayPoint2[Z] - rayPoint1[Z]) * fT);

  return Point(fX, 0, fZ);
}

/************************************************************/

GLvoid vDrawScene(
  GLvoid
)
/*
  Written: 02 Mar 2010: JH
  Purpose: 
*/
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
  vInitProjMat(iWindowWidth, iWindowHeight);          // Set projection matrix to perspective
  glMatrixMode(GL_MODELVIEW);                         // Set matrix mode
  glLoadIdentity();                                   // Reset matrix
  
	// Transform model view matrix
	glRotatef(90/*fRotateX*/, 1.0f, 0.0f, 0.0f);
	glRotatef(0/*fRotateY*/, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, fCameraY, -fCameraZ);

  Point
    mouseWorldCoords = screenToWorldCoords(state.iPosX, state.iPosY);

  glPushMatrix();

	glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);

  // Draw walls
  {
    for(unsigned int i = 0; i < walls.size(); i++)
    {
      glBegin(GL_LINES);
      glColor3f(1.0f, 1.0f, 1.0f);

      glVertex3f(walls[i].m_p1[X], walls[i].m_p1[Y], walls[i].m_p1[Z]);
      glVertex3f(walls[i].m_p2[X], walls[i].m_p2[Y], walls[i].m_p2[Z]);
      glEnd();
    }
  }

  // Draw the players and items
  {
    glEnable(GL_TEXTURE_2D);
    pColModel2->vDraw(); // Draw players

    for(unsigned int i = 0; i < enemies.size(); i++)
      enemies[i]->vDraw();

    for(unsigned int i = 0; i < items.size(); i++)
      items[i]->vDraw();

    glDisable(GL_TEXTURE_2D);
  }

  // Draw projectiles
  {
    for(unsigned int i = 0; i < projectiles.size(); i++)
      projectiles[i]->vDraw();
  }

  // Draw FPS, text and controls

  // Set orthographic projection, remember to push and pop matrix as it will be messed with
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  vSetOrtho(iWindowWidth, iWindowHeight);

  // Draw inventory
  //if(Inventory active)
  {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    pColModel2->vDrawInventory(state.iPosX, state.iPosY);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
  }

  vDrawControls();
  vDisplayFps();

  // Check for collisions

  for(unsigned int i = 0; i < enemies.size(); i++)
    if(colEngine.boCircleCollision(enemies[i]->posGet(), enemies[i]->fCollCircleRadius(), pColModel2->posGet(), pColModel2->fCollCircleRadius()))
      Engine->vDrawText(0, 25, "Player Collision!");

  char
    sTmp[50];
  sprintf_s(sTmp, sizeof(sTmp), "Angle: %f", pColModel2->fRotYGet());
  Engine->vDrawText(0, 35, sTmp);
  sprintf_s(sTmp, sizeof(sTmp), "X: %f", mouseWorldCoords[X]);
  Engine->vDrawText(0, 45, sTmp);
  sprintf_s(sTmp, sizeof(sTmp), "Z: %f", mouseWorldCoords[Z]);
  Engine->vDrawText(0, 55, sTmp);
  
  glEnable(GL_TEXTURE_2D);

  glMatrixMode(GL_PROJECTION);
	glPopMatrix();

  // Clear buffers
  glFlush();

  // This line is modified in different window interfaces
  SDL_GL_SwapBuffers();  // Swap buffers to avoid flickering

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

/************************************************************/

GLboolean boCheckKeys(
  long diffTime
)
/*
  Written: 02 Mar 2010: JH
  Purpose: 
*/
{
  if(state.iLeftBtnDown)  // Left mouse button is down
  {
    SDL_WM_GrabInput(SDL_GRAB_ON);  // Do not allow mouse to move outside window

    if(boLeftBtnCurrUp && pColModel2->boHandleInventory(state.iPosX, state.iPosY))
    {
      boLeftBtnCurrUp = false;
      boHandlingInventory = true;

      Item
        *pDroppedItem = pColModel2->pClickInventory(state.iPosX, state.iPosY);

      if(pDroppedItem != NULL)
      {
        // Drop in a random direction
        Point
          newPos = pColModel2->posGet();
        int
          iRandomDegree = (rand()%360)+1;

        newPos[X] += cos(DegreesToRads(iRandomDegree)) * 6;
        newPos[Y] = 0;  // Might have been modified when moved around in inventory
        newPos[Z] += sin(DegreesToRads(iRandomDegree)) * 6;

        pDroppedItem->vPosSet(newPos);
        items.push_back(pDroppedItem);
      }
    }
    else if(!boHandlingInventory)
    {
      bool
        boDone = false; // If we clicked an item or enemy, we are done, no need to check for more collisions
      Point
        rayPoint1(0, -fCameraY, fCameraZ),
        screenCoords = (screenToWorldCoords(state.iPosX, state.iPosY));

      // Create ray
      lineSegment
        ray(Point(rayPoint1[X], rayPoint1[Y], rayPoint1[Z]), Point(screenCoords[X], screenCoords[Y], screenCoords[Z]));

      // Check ray/box intersection on enemies
      for(unsigned int i = 0; i < enemies.size() && !boDone; i++)
      {
        lineSegment
          bounds(
          Point(enemies[0]->posGet()[X] + enemies[0]->colBoxGet().m_p1[X], enemies[0]->posGet()[Y] + enemies[0]->colBoxGet().m_p1[Y], enemies[0]->posGet()[Z] + enemies[0]->colBoxGet().m_p1[Z]),
          Point(enemies[0]->posGet()[X] + enemies[0]->colBoxGet().m_p2[X], enemies[0]->posGet()[Y] + enemies[0]->colBoxGet().m_p2[Y], enemies[0]->posGet()[Z] + enemies[0]->colBoxGet().m_p2[Z])
          );

        if(colEngine.boRayBoxIntersection(ray, bounds))
        {
          if(pColModel2->boCanAttack(SDL_GetTicks()))
          {
            projectiles.push_back( enemies[0]->pShoot(Point(0, 0, 0)) );

            boDone = true;
            break;
          }
        }
      } // End for, ray intersection on enemies

      if(!boDone)
        pColModel2->vTargetMove(screenCoords); // Move to mouse click
    }
  }
  else if(state.iRightBtnDown && pActiveControl == NULL) // Same as above, but with right mouse button
  {
    SDL_WM_GrabInput(SDL_GRAB_ON);

    // Shoot
    if(pColModel2->boCanAttack(SDL_GetTicks()))
    {
      projectiles.push_back( pColModel2->pShoot(screenToWorldCoords(state.iPosX, state.iPosY)) );
    }
  }
  else  // No mouse buttons are pressed
  {
    SDL_WM_GrabInput(SDL_GRAB_OFF); // Allow mouse to move outside window
    boNavigating = false;
  }

  if(state.iLeftBtnDown == 0)
  {
    boLeftBtnCurrUp = true;
    boHandlingInventory = false;
  }

#if 0
  if(pKeys[SDLK_s])
  {
    Point
      pos(pColModel2->posGet());

    pos[X] -= cos(DegreesToRads(pColModel2->fRotYGet() - 90)) * fMovementSpeed;
    pos[Z] -= sin(DegreesToRads(pColModel2->fRotYGet() - 90)) * fMovementSpeed;

    pColModel2->vPosSet(pos);
  }
  if(pKeys[SDLK_a])
  {
    pColModel2->vRotate(pColModel2->fRotYGet() - 0.3f, Y);
  }
  if(pKeys[SDLK_d])
  {
    pColModel2->vRotate(pColModel2->fRotYGet() + 0.3f, Y);
  }
#endif
  if(pKeys[SDLK_ESCAPE])
    return true;

  return false;
}

/************************************************************/

int main(
  int argc,
  char *argv[]
)
/*
  Written: 02 Mar 2010: JH
  Purpose: 
*/
{
  static long
    s_lastTime = SDL_GetTicks();
  long
    currTime,
    diffTime;

  if(SDL_Init(SDL_INIT_VIDEO) < 0)  // Try to initialize video mode
  {
    // Error
    fprintf(stderr, "Unable to initialize SDL video: %s", SDL_GetError()); // Print error to file
    exit(1);
  }

	// Anti aliasing using multi sampling
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

  if(SDL_SetVideoMode(iWindowWidth, iWindowHeight, 0, SDL_OPENGL) == NULL)  // Initialize window
  {
    // Error
    fprintf(stderr, "Unable to set SDL video mode: %s", SDL_GetError()); // Print error to file
    exit(2);  // exit(2) so that we know that error nr 2 hit
  }

  vInitGL(iWindowWidth, iWindowHeight);

  int
    iDone = 0;

  while(!iDone)
  {
    currTime = SDL_GetTicks();
    diffTime = currTime - s_lastTime;
    SDL_Event
      event;

    // Update mouse state
    SDL_GetMouseState(&state.iPosX, &state.iPosY);  // Get position
    state.iLeftBtnDown    = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
    state.iMiddleBtnDown  = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
    state.iRightBtnDown   = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);

    vDrawScene();

    // Update player
    // Update position if we are currently moving to a target position
    if(pColModel2->boMovingToTarget())
    {
      Point
        pos(pColModel2->posGet());
      Vector3f
        wallVector;

      pos[X] += (float)cos(DegreesToRads(pColModel2->fRotYGet())) * fMovementSpeed * diffTime;
      pos[Z] += (float)sin(DegreesToRads(pColModel2->fRotYGet())) * fMovementSpeed * diffTime;

      // Collision between player and wall
      for(unsigned int i = 0; i < walls.size(); i++)
      {
        if( colEngine.boIntersectCircleSegment(pos, pColModel2->fCollCircleRadius(), walls[i]) )
        {
          wallVector.vWallVectorSet(walls[i].m_p1, walls[i].m_p2);

          // Check if the line is horizontal or vertical, and stop movement in either X or Y
          if(wallVector[X] == 0)  // Vertical
            pos[X] = pColModel2->posGet()[X];
          else                    // Horizontal
            pos[Z] = pColModel2->posGet()[Z];
        }
      }

      pColModel2->vPosSet(pos);

      // Check for collision with items and pick them up
      for(unsigned int i = 0; i < items.size(); i++)
      {
        float
          fRadItem = Vector3f(items[i]->colBox().m_p1, items[i]->colBox().m_p2).fMagnitude()/2;

        if(colEngine.boCircleCollision(pColModel2->posGet(), pColModel2->fCollCircleRadius(), items[i]->pos(), fRadItem))
        {
          pColModel2->vAddItem(items[i]);
          items.erase(items.begin() + i);

          break;  // Found the item that was clicked
        }
      } // End for, ray intersection on items
    }

    // Update projectiles
    bool
      boProjColl;

    for(unsigned int i = 0; i < projectiles.size(); i++)
    {
      boProjColl = false;
      projectiles[i]->vUpdatePosition(diffTime);

      // Check for collisions between player 1 and projectiles
      for(unsigned int j = 0; j < enemies.size(); j++)
      {
        if(colEngine.boCircleCollision(enemies[j]->posGet(), enemies[j]->fCollCircleRadius(), projectiles[i]->pos(), 0.5f))
        {
          boProjColl = true;

          // Player 1 takes damage, and dies if health reaches zero
          float
            fNewHealth = enemies[j]->fHealth() - projectiles[i]->fDamage();
          if(fNewHealth <= 0)
          {
            delete enemies[j];
            enemies.erase(enemies.begin() + j);
            j--;
          }
          else
            enemies[j]->vHealthSet(fNewHealth);

          // Delete projectile
          delete projectiles[i];
          projectiles.erase(projectiles.begin() + i);
          i--;
        }
      }

      if(boProjColl)
        continue;

      // Projectiles against walls
      for(unsigned int j = 0; j < walls.size(); j++)
      {
        if(colEngine.boIntersectCircleSegment(projectiles[i]->pos(), 0.5f, walls[j]))
        {
          boProjColl = true;

          delete projectiles[i];
          projectiles.erase(projectiles.begin() + i);
          i--;
          break;  // Break this for loop, outer loop continues to the next projectile
        }
      }

      if(boProjColl)
        continue;
    }

    while(SDL_PollEvent(&event))  // As long as there are events in queue
    {
      if(event.type == SDL_QUIT)  // Event tells us to quit SDL
        iDone = 1;

      pKeys = SDL_GetKeyState(NULL);
    }

    if(boCheckKeys(diffTime))  // Check for key states
        iDone = 1;

    s_lastTime = currTime;
  }

  // Delete all enemies
  for(unsigned int i = 0; i < enemies.size(); i++)
    delete enemies[i];

  // Delete all items
  for(unsigned int i = 0; i < items.size(); i++)
    delete items[i];

  // Delete all controls
  for(std::list<Control*>::iterator it = Control::s_controlsListGet().begin(); it != Control::s_controlsListGet().end(); it++)
  {
    delete (*it);

    // It's a linked list and the destructor removes the control pointer from the static control list,
    // so if we increment the iterator we will jump over a control pointer. So always delete the first pointer
    it = Control::s_controlsListGet().begin();
  }

  // Delete all lights
  while(Light::s_vecLightsGet().size() > 1)
    delete (*Light::s_vecLightsGet().begin());

  GLEngine::s_vUninitialize();

  SDL_Quit();

  return 0;
}