#if 0

/********** Includes ****************************************/

#include "Cube.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

void Cube::vCreatePrimitive(
)
/*
  Written: 31 Aug 2010: JH
*/
{
  // Add all 8 vertices needed for a cube
  iAddVertex(-1.0f, -1.0f, -1.0f);
  iAddVertex( 1.0f, -1.0f, -1.0f);
  iAddVertex( 1.0f, -1.0f,  1.0f);
  iAddVertex(-1.0f, -1.0f,  1.0f);
  iAddVertex(-1.0f,  1.0f, -1.0f);
  iAddVertex( 1.0f,  1.0f, -1.0f);
  iAddVertex( 1.0f,  1.0f,  1.0f);
  iAddVertex(-1.0f,  1.0f,  1.0f);

  // Normals for all 6 sides
  iAddNormal( 1.0f,  0.0f,  0.0f);
  iAddNormal(-1.0f,  0.0f,  0.0f);
  iAddNormal( 0.0f,  1.0f,  0.0f);
  iAddNormal( 0.0f, -1.0f,  0.0f);
  iAddNormal( 0.0f,  0.0f,  1.0f);
  iAddNormal( 0.0f,  0.0f, -1.0f);

  // Add texture coordinates, all faces will use the same coordinates
  iAddTexCoord(0.0f, 0.0f);
  iAddTexCoord(0.0f, 1.0f);
  iAddTexCoord(1.0f, 0.0f);
  iAddTexCoord(1.0f, 1.0f);

  // Add all the 12 faces (each face is a triangle), remember: All the vertices, normals and texcoords have been put into arrays,
  // so the indices we pass to the vAddFace function must correspond to the indices in the arrays,
  // i.e. the order we added the vertices, normals and texcoords
  
  // -Z
  vAddFace(0, 4, 5, 5, 5, 5, 0, 1, 2);
  vAddFace(5, 1, 0, 5, 5, 5, 3, 2, 0);

  // +Z
  vAddFace(2, 6, 7, 4, 4, 4, 0, 1, 2);
  vAddFace(7, 3, 2, 4, 4, 4, 3, 2, 0);

  // -Y
  vAddFace(0, 1, 2, 3, 3, 3, 0, 1, 2);
  vAddFace(2, 3, 0, 3, 3, 3, 3, 2, 0);

  // +Y
  vAddFace(5, 4, 7, 2, 2, 2, 0, 1, 2);
  vAddFace(7, 6, 5, 2, 2, 2, 3, 2, 0);

  // -X
  vAddFace(3, 7, 4, 1, 1, 1, 0, 1, 2);
  vAddFace(4, 0, 3, 1, 1, 1, 3, 2, 0);

  // +X
  vAddFace(1, 5, 6, 0, 0, 0, 0, 1, 2);
  vAddFace(6, 2, 1, 0, 0, 0, 3, 2, 0);
}

#endif