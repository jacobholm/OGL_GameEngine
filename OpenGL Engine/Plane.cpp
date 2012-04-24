#if 0

/********** Includes ****************************************/

#include "Plane.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

void Plane::vSetSize(
  float fWidth,
  float fHeight
)
{
  m_fWidth = fWidth;
  m_fHeight = fHeight;
}

/************************************************************/

void Plane::vSetDivisions(
  int iDivisions
)
{
  m_iDivisions = iDivisions;
}

/************************************************************/

void Plane::vCreatePrimitive(
)
/*
  Written: 31 Aug 2010: JH
*/
{
  float // The size of each part/division
    iIncX = m_fWidth / (float)m_iDivisions,
    iIncY = m_fHeight / (float)m_iDivisions;

  iAddNormal(0.0f, 1.0f, 0.0f); // The plane only has 1 normal
  iAddTexCoord(0.0f, 0.0f);     // We are not going to use texcoords for the plane

  for(float fX = -m_fWidth / 2; fX < m_fWidth / 2; fX += iIncX)
    for(float fY = -m_fHeight / 2; fY < m_fHeight / 2; fY += iIncY)
    {
      int
        iV1 = iAddVertex(fX + iIncX, 0.0f, fY + iIncY),
        iV2 = iAddVertex(fX, 0.0f, fY + iIncY),
        iV3 = iAddVertex(fX + iIncX, 0.0f, fY),
        iV4 = iAddVertex(fX,         0.0f, fY);

      // Add the two triangles that make up the plane
      vAddFace(iV1, iV3, iV4, 0, 0, 0, 0, 0, 0);
      vAddFace(iV4, iV2, iV1, 0, 0, 0, 0, 0, 0);
    }
}

#endif