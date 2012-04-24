/*
  Written: 05 Dec 2010: JH
  Comment:
*/

#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

/********** Includes ****************************************/

//#include "Math.hpp"
//#include "Model.hpp"

/********** Local Defines ***********************************/

/************************************************************/

class CollisionEngine
/*
  Purpose: Solves collisions between models using separating axis testing
  Written: 05 Dec 2010: JH
*/
{

//---------- Member Variables --------------------------------


//---------- Ctor/Dtor ---------------------------------------

public:

  CollisionEngine(
  );

  ~CollisionEngine(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------
#if 0
  bool boSpanIntersect( // Check if the span of the models along the given SAT axis intersect
    Vector3f &SATAxis,
    Model *pModel,1
    Model *pModel2
  );

  //----------------------------------------------------------

  bool boPolyhedraIntersect(  // Check if the models intersect
    Model *pModel1,
    Model *pModel2
  );
#endif
  //----------------------------------------------------------

  bool boIntersectCircleSegment(
    const Point &c,         // center
    const float r,          // radius
    const lineSegment &line // segment start and end
  ) const;

  //----------------------------------------------------------

  bool boCircleCollision(
    Point fPos1,
    float fRadius1,
    Point fPos2,
    float fRadius2
  );

  //----------------------------------------------------------
#if 1
  bool boRayBoxIntersection(
    const lineSegment ray,
    const lineSegment bounds
  ) const;
#endif
//---------- Private Functions -------------------------------

private:

};

#endif