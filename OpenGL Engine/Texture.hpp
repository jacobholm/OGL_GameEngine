/*
  Written: 02 Mar 2010: JH
  Comment: 
*/

#ifndef TEXTURE_H
#define TEXTURE_H

/********** Includes ****************************************/

#include <fstream>
#include <string>
#include <vector>

/********** Local Defines ***********************************/

/************************************************************/

using std::ifstream;
using std::string;
using std::vector;

struct TGA_Header
{
  // NB!!! It is important that each variable come in the correct order as the struct will read raw data from a TGA file
  unsigned char // GLubyte
    IDLength,
    colorMapType,
    imageType,
    colorMapSpecification[5];
  short // GLshort
    xOrigin,
    yOrigin,
    imageWidth,
    imageHeight;
  unsigned char
    pixelDepth,
    imageDescriptor;
};

class Texture
/*
  Written: 02 Mar. 2010: JH
  Purpose: Class for handling textures(i.e. loading, applying etc..)
*/
{

//---------- Member Variables --------------------------------

  static vector<Texture*>
    s_texturesVec;  // A global Vector3f containing all the textures in use

  string
		m_sName,  // Name of the material. 1-16 characters plus NULL
		m_sFile;  // Texture map filename, basename + extension (12 characters plus NULL)

	unsigned short
		iNrFaces;       // The number of faces in the submodel which the material applies to
  std::vector<unsigned short>
		indices;        // The triangle/face indices that belong to this material
	int
		iTextureId;
  unsigned char
    *m_pImageData;  // Raw image data
  unsigned int
    m_iBpp,         // Bits per pixel
    m_iWidth,
    m_iHeight,
    m_iTexID;       // Unique ID for _this_ texture

//---------- Ctor/Dtor ---------------------------------------

public:

  Texture(
    string sFilename, // Filename including full path
    string sName = "" // A simplified name for the texture
  );

  ~Texture(
  );

//---------- Set/Get Member Variables ------------------------

  void pImageDataSet(
    unsigned char* pImageData
  )
  {
    m_pImageData = pImageData;
  }

  unsigned char* pImageDataGet(
  )
  {
    return m_pImageData;
  }

  //----------------------------------------------------------

  void iBppSet(
    unsigned int iBpp
  )
  {
    m_iBpp = iBpp;
  }

  unsigned int iBppGet(
  )
  {
    return m_iBpp;
  }

  //----------------------------------------------------------

  void iWidthSet(
    unsigned int iWidth
  )
  {
    m_iWidth = iWidth;
  }

  unsigned int iWidthGet(
  )
  {
    return m_iWidth;
  }

  //----------------------------------------------------------

  void iHeightSet(
    unsigned int iHeight
  )
  {
    m_iHeight = iHeight;
  }

  unsigned int iHeightGet(
  )
  {
    return m_iHeight;
  }

  //----------------------------------------------------------

  void iTexIDSet(
    unsigned int iTexID
  )
  {
    m_iTexID = iTexID;
  }

  unsigned int iTexIDGet(
  )
  {
    return m_iTexID;
  }

  //----------------------------------------------------------

  static vector<Texture*> &s_texturesVecGet(
  )
  {
    return s_texturesVec;
  }

//---------- Public Functions --------------------------------

//---------- Private Functions -------------------------------

private:

  bool boLoadTGA( // Load a *.tga file
    string sFilename  // Path to the file
  );  // Returns true if loaded successfully

  //----------------------------------------------------------

  void vFlipImage(
    unsigned char *pImage,
    bool boFlipHorizontal,
    bool boFlipVertical,
    unsigned short width,   //GLushort width,
    unsigned short height,  //GLushort height,
    unsigned char bpp       //GLbyte bpp
  );

  //----------------------------------------------------------

  void vSwap(
    unsigned char *pOri,
    unsigned char *pDest,
    int iSize // GLint
  );

  //----------------------------------------------------------

  bool boCreateTexture( // Create/initialize the texture from the given parameters
    unsigned char *pImageData,  // Raw image data
    int iWidth,                 // The width
    int iHeight,                // The height
    int iType                   // The type(e.g. RGB format)
  );  // Returns true if created successfully
};

#endif