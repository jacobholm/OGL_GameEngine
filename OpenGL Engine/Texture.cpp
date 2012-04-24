/*
  Written: 03 Mar 2010: JH
  Comment: 
*/

/********** Includes ****************************************/

#include "GLEngine.hpp"
#include "Texture.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

vector<Texture*>
  Texture::s_texturesVec;

/************************************************************/

Texture::Texture(
  string sFilename, // Filename including full path
  string sName      // A simplified name for the texture
)
/*
  Written: 03 Mar 2010: JH
  Purpose: 
*/
{
  m_pImageData = NULL;
  m_sName = sName;

  boLoadTGA(sFilename);
  Texture::s_texturesVecGet().push_back(NULL); // Store this texture in the static Vector3f
}

Texture::~Texture(
)
/*
  Written: 03 Mar 2010: JH
  Purpose: 
*/
{
  // Go through the static texture Vector3f and delete _this_ texture
  for(vector<Texture*>::iterator it = s_texturesVecGet().begin(); it != s_texturesVecGet().end(); it++)
    if((*it) == this)
    {
      s_texturesVecGet().erase(it);
    }

  if(m_pImageData)
    delete m_pImageData;
}

/************************************************************/

bool Texture::boLoadTGA(
  string sFilename
)
/*
  Written: 03 Mar 2010: JH
  Purpose: 
*/
{
  TGA_Header
    tgaHeader;
  ifstream
    fileStream(sFilename.data(), std::ios_base::binary);

  if(!fileStream.is_open())
    return false; // Give error message

  if(!fileStream.read((char*)&tgaHeader, sizeof(tgaHeader)))
    return false; // Give error message

  if(tgaHeader.imageType != 2)  // 2 == uncompressed, true color TGA
    return false; // Give error message

  m_iWidth = tgaHeader.imageWidth;
  m_iHeight = tgaHeader.imageHeight;
  m_iBpp = tgaHeader.pixelDepth;

  if(m_iWidth <= 0 || m_iHeight <= 0 || // If height or width is zero or less, or if pixel depth is not 24 or 32,
     (m_iBpp != 24 && m_iBpp != 32))    // we don't support the image file
    return false; // Give error message

  int // GLuint
    iType = GL_RGBA,                                        // Set default type to Red Green Blue Alpha
    iBytesPerPixel = m_iBpp / 8,                            // Convert from bits per pixel to bytes per pixel
    iImageByteSize = m_iWidth * m_iHeight * iBytesPerPixel; // Calculate the size of the image to read in bytes

  if(m_iBpp == 24)  // If image only has 24 bits per pixel alpha does not exist
    iType = GL_RGB;

  m_pImageData = new /*GLubyte*/unsigned char[iImageByteSize]; // Initialize image data pointer and allocate calculated size

  if(!fileStream.read((char*)m_pImageData, iImageByteSize))
  {
    delete m_pImageData;  // If file couldn't be read delete image data to avoid memory leak
    return false;         // Give error message
  }

  // RGB values in TGA files are stored backwards(BGR) so we need to convert them
  for(/*GLuint*/int i = 0; i < iImageByteSize; i += iBytesPerPixel)
  {
    /*GLuint*/int
      iTemp = m_pImageData[i];

    m_pImageData[i] = m_pImageData[i+2];
    m_pImageData[i+2] = iTemp;
  }

  // Find out how(and if) the image was flipped, and flip it back accordingly
  bool
    boFlipHorizontal = ((tgaHeader.imageDescriptor & 0x10) == 0x10),
    boFlipVertical = ((tgaHeader.imageDescriptor & 0x20) == 0x20);
  vFlipImage(m_pImageData, boFlipHorizontal, boFlipVertical, m_iWidth, m_iHeight, m_iBpp);

  boCreateTexture(m_pImageData, m_iWidth, m_iHeight, iType);

  return true;
}

/************************************************************/

void Texture::vFlipImage(
  unsigned char *pImage,
  bool boFlipHorizontal,
  bool boFlipVertical,
  unsigned short width, //GLushort width,
  unsigned short height, //GLushort height,
  unsigned char bpp  //GLbyte bpp
)
/*
  Written: 21 Mar. 2010: JH
  Purpose: The image might come out flipped, so we flip it back
*/
{
  unsigned char // GLbyte
    m_iBpp = bpp / 8;        

  if (boFlipHorizontal){
    for (int h = 0; h < height; h++) {
      for (int w = 0; w < width / 2; w++){                
        vSwap(pImage + (h * width + w) * m_iBpp, pImage + (h * width + width - w - 1)* m_iBpp, m_iBpp);
      }
    }
  }

  if (boFlipVertical){
    for (int w = 0; w < width; w++){
      for (int h = 0; h < height / 2; h++) {
        vSwap(pImage + (h * width + w) * m_iBpp, pImage + ((height - h - 1) * width + w)* m_iBpp, m_iBpp);
      }
    }
  }
}

void Texture::vSwap(
  unsigned char *pOri,
  unsigned char *pDest,
  int iSize  //GLint iSize
)
/*
  Written: 21 Mar. 2010: JH
  Purpose: 
*/
{
  unsigned char //GLubyte
    *pTemp = new unsigned char[iSize];

  memcpy(pTemp, pOri, iSize);
  memcpy(pOri, pDest, iSize);
  memcpy(pDest, pTemp, iSize);

  delete [] pTemp;
}

/************************************************************/

bool Texture::boCreateTexture(
  unsigned char *pImageData,
  int iWidth,
  int iHeight,
  int iType
)
/*
  Written: 06 Mar 2010: JH
  Purpose: 
*/
{
  glGenTextures(1, &m_iTexID);            // We will generate one texture
  glBindTexture(GL_TEXTURE_2D, m_iTexID); // Bind the texture to our texture ID

  // Set which filters to use on minimum and maximum distance from the texture
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Create the actual texture from the raw image data
  glTexImage2D(GL_TEXTURE_2D, 0, iType, iWidth, iHeight, 0, iType, GL_UNSIGNED_BYTE, pImageData);

  return true;
}