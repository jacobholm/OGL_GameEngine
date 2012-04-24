#if 0

/********** Includes ****************************************/

#include "Mesh.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

FbxMesh::FbxMesh(
  std::string sName
)
{

}

FbxMesh::~FbxMesh(
)
{

}

/************************************************************/

bool FbxMesh::boDrawMesh(
  Vector3f *pTransformedVerts
)
{

}

/************************************************************/

std::vector<FbxFace*> &FbxMesh::getFaces(
)
{

}

/************************************************************/

Vector3f *FbxMesh::pGetVertices(
)
{

}

/************************************************************/

Vector3f *FbxMesh::pGetNormals(
)
{

}

/************************************************************/

Vector3f *FbxMesh::pGetUVs(
)
{

}

/************************************************************/

void FbxMesh::vAddFace(
  int iV1, int iV2, int iV3,
  int iN1, int iN2, int iN3,
  int iUV1, int iUV2, int iUV3,
  FbxMaterial *pMaterial
)
{

}

/************************************************************/

void FbxMesh::vAddFace(
  FbxFace *pFace
)
{

}

/************************************************************/

void FbxMesh::vDeleteObjects(
)
{

}

#endif