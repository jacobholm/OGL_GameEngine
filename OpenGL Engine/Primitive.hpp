#if 0

/*
  Written: 29 Aug 2010: JH
  Comment: 
*/

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

/********** Includes ****************************************/

#include "Mesh.hpp"

/********** Local Defines ***********************************/

/************************************************************/

class Primitive : public Mesh
/*
  Purpose: All our primitives
  Written: 29 Aug 2010: JH
*/
{

//---------- Member Variables --------------------------------

//---------- Ctor/Dtor ---------------------------------------

public:

  virtual void vCreatePrimitive(
  ) = 0;

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

//---------- Private Functions -------------------------------

private:

};

#endif

#endif