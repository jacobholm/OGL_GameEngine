/*
  Written: 05 Dec 2010: JH
  Comment: 
*/

/********** Includes ****************************************/

// Struct and math included in main at the top
//#include <vector>
#include <math.h>
#include "Math.hpp" // Point, dot etc
#include "Structs.hpp"
//#include "Model.hpp"
#include "CollisionEngine.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

CollisionEngine::CollisionEngine(
)
/*
  Written: 05 Dec 2010: JH
*/
{
}

CollisionEngine::~CollisionEngine(
)
/*
  Written: 05 Dec 2010: JH
*/
{
}

/**********************************************************/
#if 0
bool CollisionEngine::boSpanIntersect(
  Vector3f &SATAxis,
  Model *pModel1,
  Model *pModel2
)
/*
  Written: 05 Dec 2010: JH
*/
{
  float
    fMinModel1, fMaxModel1,
    fMinModel2, fMaxModel2;

  pModel1->getCollisionBox().boCalculateInterval(SATAxis, fMinModel1, fMaxModel1);
  pModel2->getCollisionBox().boCalculateInterval(SATAxis, fMinModel2, fMaxModel2);

  if(fMinModel1 > fMaxModel2 || fMinModel2 > fMaxModel1)
    return false;

  return true;
}

/**********************************************************/

bool CollisionEngine::boPolyhedraIntersect(
  Model *pModel1,
  Model *pModel2
)
/*
  Written: 05 Dec 2010: JH
*/
{
  Vector3f
    SATAxis;
  int
    iModel1NumFaces = pModel1->getCollisionBox().iGetNumSATFaces(),
    iModel2NumFaces = pModel2->getCollisionBox().iGetNumSATFaces(),
    iModel1NumEdges = pModel1->getCollisionBox().iGetNumSATEdges(),
    iModel2NumEdges = pModel2->getCollisionBox().iGetNumSATEdges();

  // If the models do not intersect on all axes, they do not intersect, return false
  for(int i = 0; i < iModel1NumFaces; i++)
  {
    SATAxis = pModel1->getCollisionBox().GetSATFaceNormal(i);

    if (!boSpanIntersect(SATAxis, pModel1, pModel2))
      return false;
  }

  for(int i = 0; i < iModel2NumFaces; i++)
  {
    SATAxis = pModel2->getCollisionBox().GetSATFaceNormal(i);

    if (!boSpanIntersect(SATAxis, pModel1, pModel2))
      return false;
  }


  for(int i = 0; i < iModel1NumEdges; i++)
  {
    for(int j = 0; j < iModel2NumEdges; j++)
    {
      Vector3f
        edgeDir1,
        edgeDir2;
      edgeDir1 = pModel1->getCollisionBox().GetSATEdgeDirection(i);
      edgeDir2 = pModel2->getCollisionBox().GetSATEdgeDirection(j);

      SATAxis[X] = (edgeDir1[1]*edgeDir2[2] - edgeDir1[2]*edgeDir2[1]);
      SATAxis[Y] = (edgeDir1[2]*edgeDir2[0] - edgeDir1[0]*edgeDir2[2]);
      SATAxis[Z] = (edgeDir1[0]*edgeDir2[1] - edgeDir1[1]*edgeDir2[0]);

    if (!SATAxis.boIsZero() && !boSpanIntersect(SATAxis, pModel1, pModel2))
      return false;

    }
  }

  return true;  // The models intersect
}
#endif

/************************************************************/

bool CollisionEngine::boIntersectCircleSegment(
  const Point &c,         // center
  const float r,          // radius
  const lineSegment &line // segment start and end
) const
{
  Point
    dir = line.m_p2 - line.m_p1,
    diff = c - line.m_p1;
  float
    t1 = Dot(diff, dir),
    t2 = Dot(dir, dir),
    t = t1 / t2;

  if (t < 0.0f)
    t = 0.0f;
  if (t > 1.0f)
    t = 1.0f;

  Point
    closest = line.m_p1 + (dir * t),
    d = c - closest;
  float
    distsqr = Dot(d, d);

  return distsqr <= r * r;
}

/************************************************************/

bool CollisionEngine::boCircleCollision(
  Point fPos1,
  float fRadius1,
  Point fPos2,
  float fRadius2
)
{
  Vector3f
    distance(fPos1, fPos2);

  return distance.fMagnitude() < (fRadius1 + fRadius2);
}

/************************************************************/

bool CollisionEngine::boRayBoxIntersection(
  const lineSegment ray,
  const lineSegment bounds
) const
{
  Vector3f
    rayDirection;
  rayDirection[X] = ray.m_p2[X] - ray.m_p1[X];
  rayDirection[Y] = ray.m_p2[Y] - ray.m_p1[Y];
  rayDirection[Z] = ray.m_p2[Z] - ray.m_p1[Z];

  float
    tmin,
    tmax,
    tymin,
    tymax,
    tzmin,
    tzmax,
    t0 = 0,
    t1 = rayDirection.fMagnitude();

  if (rayDirection[X] >= 0) {
    tmin = (bounds.m_p1[X] - ray.m_p1[X]) / rayDirection[X];
    tmax = (bounds.m_p2[X] - ray.m_p1[X]) / rayDirection[X];
  }
  else {
    tmin = (bounds.m_p2[X] - ray.m_p1[X]) / rayDirection[X];
    tmax = (bounds.m_p1[X] - ray.m_p1[X]) / rayDirection[X];
  }
  if (rayDirection[Y] >= 0) {
    tymin = (bounds.m_p1[Y] - ray.m_p1[Y]) / rayDirection[Y];
    tymax = (bounds.m_p2[Y] - ray.m_p1[Y]) / rayDirection[Y];
  }
  else {
    tymin = (bounds.m_p2[Y] - ray.m_p1[Y]) / rayDirection[Y];
    tymax = (bounds.m_p1[Y] - ray.m_p1[Y]) / rayDirection[Y];
  }
  if ( (tmin > tymax) || (tymin > tmax) )
    return false;
  if (tymin > tmin)
    tmin = tymin;
  if (tymax < tmax)
    tmax = tymax;
  if (rayDirection[Z] >= 0) {
    tzmin = (bounds.m_p1[Z] - ray.m_p1[Z]) / rayDirection[Z];
    tzmax = (bounds.m_p2[Z] - ray.m_p1[Z]) / rayDirection[Z];
  }
  else {
    tzmin = (bounds.m_p2[Z] - ray.m_p1[Z]) / rayDirection[Z];
    tzmax = (bounds.m_p1[Z] - ray.m_p1[Z]) / rayDirection[Z];
  }
  if ( (tmin > tzmax) || (tzmin > tmax) )
    return false;
  if (tzmin > tmin)
    tmin = tzmin;
  if (tzmax < tmax)
    tmax = tzmax;
  return ( (tmin < t1) && (tmax > t0) );

}