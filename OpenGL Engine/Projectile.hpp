/*
  Written: 31 Jul 2011: JH
  Comment: Projectile base class
*/

#ifndef PROJECTILE_H
#define PROJECTILE_H

/********** Includes ****************************************/

/********** Local Defines ***********************************/

/************************************************************/

class Projectile
/*
  Purpose: 
  Written: 31 Jul 2011: JH
*/
{

//---------- Member Variables --------------------------------

  Point
    m_pos;
  Vector3f
    m_velocity; // Speed and direction
  float
    m_fDamage;

//---------- Ctor/Dtor ---------------------------------------

public:

  Projectile(
    Point pos,
    Vector3f velocity,
    float fDamage
  ) : m_pos(pos), m_velocity(velocity), m_fDamage(fDamage)
  {

  }

  ~Projectile(
  );

//---------- Set/Get Member Variables ------------------------

  Point pos(
  )
  {
    return m_pos;
  }

//---------- Public Functions --------------------------------

  void vDraw(
  );

  //----------------------------------------------------------

  void vUpdatePosition(
    long diffTime
  )
  {
    m_pos[X] += m_velocity[X] * diffTime;
    m_pos[Y] += m_velocity[Y] * diffTime;
    m_pos[Z] += m_velocity[Z] * diffTime;
  }

  //----------------------------------------------------------

  float fDamage(
  )
  {
    return m_fDamage;
  }

//---------- Private Functions -------------------------------

private:

};

#endif