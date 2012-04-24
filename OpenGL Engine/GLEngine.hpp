/*
  Written: 17 Mar 2010: JH
  Comment:
*/

#ifndef GLENGINE_H
#define GLENGINE_H

/********** Includes ****************************************/

#ifdef WIN32 // Only include windows headers if Windows OS is used, otherwise the application won't be cross platform
  #define WIN32_LEAN_AND_MEAN // This will prevent a lot of headers, which we do not need, from being included
  #include <windows.h>
#endif

// These have to be included manually in SDL as opposed to GLUT
// If using Macintosh headers will have a different path
#if defined (__APPLE__) && defined (__MACH__)
  #include <OpenGL\gl.h>
  #include <OpenGL\glu.h>
#else
  #include <gl\gl.h>
  #include <gl\glu.h>
#endif

//#include "Light.hpp"
//#include "Texture.hpp"

/********** Local Defines ***********************************/

#define Engine GLEngine::s_pGetEngine()

/************************************************************/

class Texture;

class GLEngine
/*
  Written: 17 Mar. 2010: JH
  Purpose: Singleton wrapper class for OpenGL stuff
*/
{

//---------- Member Variables --------------------------------

  GLuint
    m_iFontBase;      // Id for the base displaylist(256 lists in all, one for each character)
  Texture
    *m_pFontTexture;  // The texture containing all the characters
  int
    m_iFontSize,
    m_iFontSpace;
//---------- Ctor/Dtor ---------------------------------------

protected:

  GLEngine( // Ctor is protected since this is a singleton class
  );

public:

  ~GLEngine(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  GLvoid vInitialize(
    GLint iWidth,
    GLint iHeight
  );

  //----------------------------------------------------------

  static GLvoid s_vUninitialize(
  );

  //----------------------------------------------------------

  static GLEngine *s_pGetEngine(
  );

  //----------------------------------------------------------

  GLvoid vBuildTextureFont( // Create the display lists holding each character
  );

  //----------------------------------------------------------

  GLvoid vDrawText(
    GLint iPosX,
    GLint iPosY,
    const char *sText,
    ...
  );

  //----------------------------------------------------------

  GLuint iTextWidthGet(
    const char *sText
  );

  //----------------------------------------------------------

  GLuint iTextHeightGet(
  );

//---------- Private Functions -------------------------------

private:

};

#endif