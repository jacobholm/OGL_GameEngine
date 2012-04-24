/*
  Written: 29 Aug 2010: JH
  Comment: 
*/

#ifndef TRANSFORM_H
#define TRANSFORM_H

/********** Includes ****************************************/

#include "Node.hpp"
#include "Math.hpp"

/********** Local Defines ***********************************/

/************************************************************/

class Transform : public Node
/*
  Purpose: Manage transformations on our node
  Written: 29 Aug 2010: JH
*/
{

//---------- Member Variables --------------------------------

  Vector3f
    m_vecTranslation,
    m_vecRotation,
    m_vecScale;

//---------- Ctor/Dtor ---------------------------------------

public:

  Transform(
  );

  virtual ~Transform(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  void vSetTranslation(
    float fX,
    float fY,
    float fZ
  );

  Vector3f &vecGetTranslation(
  );

  //----------------------------------------------------------

  void vSetRotation(
    float fX,
    float fY,
    float fZ
  );

  Vector3f &vecGetRotation(
  );

  //----------------------------------------------------------

  void vSetScale(
    float fX,
    float fY,
    float fZ
  );

  Vector3f &vecGetScale(
  );

//---------- Private Functions -------------------------------

private:

};

#endif