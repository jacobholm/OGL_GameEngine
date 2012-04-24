#if 0

/*
  Written: 29 Aug 2010: JH
  Comment: 
*/

#ifndef PLANE_H
#define PLANE_H

/********** Includes ****************************************/

#include "Primitive.hpp"

/********** Local Defines ***********************************/

/************************************************************/

class Plane : public Primitive
/*
  Purpose:
  Written: 29 Aug 2010: JH
*/
{

//---------- Member Variables --------------------------------

protected:

  float
    m_fWidth,
    m_fHeight;
  int
    m_iDivisions;

//---------- Ctor/Dtor ---------------------------------------

public:

  void vSetSize(
    float fWidth,
    float fHeight
  );

  //----------------------------------------------------------

  void vSetDivisions( // How many faces should the plane be made up of
    int iDivisions
  );

  //----------------------------------------------------------

  virtual void vCreatePrimitive(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

//---------- Private Functions -------------------------------

private:

};

#endif

#endif