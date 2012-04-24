/*
  Written: 17 Mar 2010: JH
  Comment: 
*/

/********** Includes ****************************************/

#include <vector>

#include "GLEngine.hpp"
#include "Light.hpp"
#include "Texture.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

GLEngine::GLEngine(
)
/*
  Written: 17 Mar. 2010: JH
  Purpose: 
*/
{
  m_iFontSize = 13;
  m_iFontSpace = 7;
}

GLEngine::~GLEngine(
)
/*
  Written: 17 Mar. 2010: JH
  Purpose: 
*/
{

}

/************************************************************/

GLvoid GLEngine::vInitialize(
  GLint iWidth,
  GLint iHeight
)
/*
  Written: 17 Mar. 2010: JH
  Purpose: 
*/
{
  Light::s_vInitAvailableLights();

  // Initialize the font texture
  m_pFontTexture = new Texture("Textures/fontTexture.tga", "Font Texture");
  vBuildTextureFont();
}

/************************************************************/

GLvoid GLEngine::s_vUninitialize(
)
/*
  Written: 17 Mar. 2010: JH
  Purpose: 
*/
{
  delete Engine;
}

/************************************************************/

GLEngine *GLEngine::s_pGetEngine(
)
/*
  Written: 17 Mar. 2010: JH
  Purpose: 
*/
{
  static GLEngine
    *pGLEngine  = new GLEngine();

  return pGLEngine;
}

/************************************************************/

GLvoid GLEngine::vBuildTextureFont(
)
/*
  Written: 20 Mar. 2010: JH
  Purpose: Each character will be placed in its own display list
*/
{
  m_iFontBase = glGenLists(256);  // Generate one list ID for each character
  glBindTexture(GL_TEXTURE_2D, m_pFontTexture->iTexIDGet());
  glEnable(GL_BLEND); // Enable blending
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  float
    fCharX, // Character X coordinate
    fCharY; // Character Y coordinate

  for(int i = 0; i < 256; i++)
  {
    fCharX = (float)(i % 16) / 16.0f;
    fCharY = (float)(i / 16) / 16.0f;

    glNewList(m_iFontBase + i, GL_COMPILE); // Create all the lists

    // Draw the actual character(since we are working in orthographic view we can use glVertex2i as we are working with pixels)
    glBegin(GL_QUADS);  // 0.0625 is the height of one character
      glTexCoord2f(fCharX,           1 - fCharY - 0.0625f); glVertex2i(0, m_iFontSize);
      glTexCoord2f(fCharX + 0.0625f, 1 - fCharY - 0.0625f); glVertex2i(m_iFontSize, m_iFontSize);
      glTexCoord2f(fCharX + 0.0625f, 1 - fCharY);           glVertex2i(m_iFontSize, 0);
      glTexCoord2f(fCharX,           1 - fCharY);           glVertex2i(0, 0);
    glEnd();

    glTranslated(m_iFontSpace, 0, 0); // After each character make some space for the next one

    glEndList();
  }
}

/************************************************************/

GLvoid GLEngine::vDrawText(
  GLint iPosX,
  GLint iPosY,
  const char *sText,
  ...
)
/*
  Written: 20 Mar. 2010: JH
  Purpose: 
*/
{
  char
    sTmpText[256];

  va_list
    listPointer;  // A pointer to the first element of the variable argument list(ellipsis/...)

  // Print the final string into sTmpText
  va_start(listPointer, sText);
    vsprintf_s(sTmpText, sizeof(sTmpText), sText, listPointer);
  va_end(listPointer);

  // Set these just in case the user has changed them
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glBindTexture(GL_TEXTURE_2D, m_pFontTexture->iTexIDGet());

  GLint
    currMatrix;
  glGetIntegerv(GL_MATRIX_MODE, &currMatrix);  // Get current matrix mode so we can restore it afterwards
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glTranslated(iPosX, iPosY, 0);
  glListBase(m_iFontBase);
  glCallLists(strlen(sTmpText), GL_BYTE, sTmpText);

  glMatrixMode(GL_MODELVIEW); // Lists could have modified the matrix mode
  glPopMatrix();              // Restore previous matrix

  // Restore previous matrix mode
  glMatrixMode(currMatrix);
}

/************************************************************/

GLuint GLEngine::iTextWidthGet(
  const char *sText
)
/*
  Written: 20 Mar. 2010: JH
  Purpose: 
*/
{
  return strlen(sText) * m_iFontSpace;  // subtract m_iFontSpace and add m_iFontSize? Otherwise the length of the string will include the space of the last character as well
}

/************************************************************/

GLuint GLEngine::iTextHeightGet(
)
/*
  Written: 20 Mar. 2010: JH
  Purpose: 
*/
{
  return m_iFontSize;
}