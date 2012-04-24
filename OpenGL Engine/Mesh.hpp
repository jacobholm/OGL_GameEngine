#if 0

#ifndef MESH_H
#define MESH_H

#include <fbxsdk.h>
#include "Texture.hpp"
#include <string>

//using namespace FBXSDK_NAMESPACE;

struct FbxMaterial
{
  float
    m_fKa[4],
    m_fKd[4],
    m_fKs[4],
    m_fKe[4],
    m_fShininess,
    m_fAlpha,
    m_fIllumination;
  Texture
    *m_pDiffuseMap;
  std::string
    m_sName;

  FbxMaterial(
  )
  {
    float
      fDefaultAmbient[4]  = {0.0f, 0.0f, 0.0f, 1.0f},
      fDefaultDiffuse[4]  = {1.0f, 1.0f, 1.0f, 1.0f},
      fDefaultSpecular[4] = {0.0f, 0.0f, 0.0f, 1.0f},
      fDefaultEmission[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    // Copy to member variables
    memcpy(m_fKa, fDefaultAmbient, sizeof(float) * 4);
    memcpy(m_fKd, fDefaultDiffuse, sizeof(float) * 4);
    memcpy(m_fKs, fDefaultSpecular, sizeof(float) * 4);
    memcpy(m_fKe, fDefaultEmission, sizeof(float) * 4);

    // Set the rest
    m_fShininess = 2.0f;
    m_fAlpha = 1.0f;
    m_fIllumination = 1.0f;
    m_pDiffuseMap = NULL;
  }
};

struct FbxFace
{
  int
    m_aiVertices[3],
    m_aiNormals[3],
    m_aiUVs[3];
  FbxMaterial
    *m_pMaterial;
  Vector3f
    m_faceCenter,
    m_faceNormal;

  FbxFace(
    int iX, int iY, int iZ,
    int iN1, int iN2, int iN3,
    int iUV1, int iUV2, int iUV3,
    Vector3f *pVectors
  )
  {
    m_aiVertices[X] = iX;
    m_aiVertices[Y] = iY;
    m_aiVertices[Z] = iZ;

    m_aiNormals[X] = iN1;
    m_aiNormals[Y] = iN2;
    m_aiNormals[Z] = iN3;

    m_aiUVs[X] = iUV1;
    m_aiUVs[Y] = iUV2;
    m_aiUVs[Z] = iUV3;

    // Find face center
    for(int i = 0; i < 3; i++)
      m_faceCenter += pVectors[ m_aiVertices[i] ];  // WTF is happening here?

    m_faceCenter /= 3;

    // Find face normal
    pVectors[X].vNormalize();
    pVectors[Y].vNormalize();
    pVectors[Z].vNormalize();
    m_faceNormal = (pVectors[X] - pVectors[Y]) * (pVectors[X] - pVectors[Z]);

    m_pMaterial = NULL;
  }
};

struct FbxFrame
{
  KFbxXMatrix
    *m_pBones;
  double
    m_dWeights;
};

class FbxMesh
/*
  Purpose: Holds the mesh bone transformations, vertex weights etc..
  Written: 05 Mar 2011: JH
*/
{
  Vector3f
    *m_pVertices,
    *m_pNormals,
    *m_pUVs;
  int
    m_iNumVertices;
  std::vector<FbxFace*>
    m_faces;
  std::string
    m_sName;
  float
    m_fFirstFrame,
    m_fLastFrame,
    m_fCurrentFrame;

public:

  FbxMesh(
    std::string sName = ""
  );

  virtual ~FbxMesh(
  );

  //----------------------------------------------------------

  bool boDrawMesh(
    Vector3f *pTransformedVerts
  );

  //----------------------------------------------------------

  std::vector<FbxFace*> &getFaces(
  );

  //----------------------------------------------------------

  Vector3f *pGetVertices(
  );

  //----------------------------------------------------------

  Vector3f *pGetNormals(
  );

  //----------------------------------------------------------

  Vector3f *pGetUVs(
  );

  //----------------------------------------------------------

  void vAddFace(
    int iV1, int iV2, int iV3,
    int iN1, int iN2, int iN3,
    int iUV1, int iUV2, int iUV3,
    FbxMaterial *pMaterial
  );

  void vAddFace(
    FbxFace *pFace
  );

private:

  void vDeleteObjects(
  );
};

#endif

#endif