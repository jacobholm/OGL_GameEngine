#ifndef STRUCTS_H
#define STRUCTS_H

#define _USE_MATH_DEFINES
//#include "Math.hpp"
//#include "Texture.hpp"

class Texture;

struct cachedAxis // A cached axis
{
	Vector3f
		direction;	// Direction of the axis
	float
		minA,				// The minimum and maximum extents of each polyhedra
		maxA,
		minB,
		maxB,
		overlap;		// The magnitude of the overlap
};

struct material // The materials that are assigned to the submodel
{
  char
    sName[16+1];  // Name of the material. 1-16 characters plus NULL
    
  unsigned short
    iNrFaces,     // The number of faces in the submodel which the material applies to
    *sIndices;    // The triangle/face indices that belong to this material
  Texture
    *pTexture;
};

struct triangleByIndex  // A triangle made up of point indices
{
  unsigned short
    a,
    b,
    c;
};

struct mapcoord // A texture mapcoordinate made up of u and v coordinates
{
  float
    u,
    v;
};

struct lineSegment
{
  Point
    m_p1,
    m_p2;

  //----------------------------------------------------------

  lineSegment(
    Point p1,
    Point p2
  ) : m_p1(p1), m_p2(p2)
  {

  }

  lineSegment(
  ) : m_p1(Point(0, 0, 0)), m_p2(Point(0, 0, 0))
  {

  }
};

#endif