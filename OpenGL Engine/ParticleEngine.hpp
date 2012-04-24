/*
  Written: 13 Jun 2010: JH
  Comment: Classes for the particle engine
*/

#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

/********** Includes ****************************************/

#include "GLEngine.hpp"
#include "Math.hpp"
#include <list>

/********** Local Defines ***********************************/

/************************************************************/

using std::list;

class Particle
/*
  Purpose: 
  Written: 13 Jun 2010: JH
*/
{

//---------- Member Variables --------------------------------

  int
    m_iID;
  float
    m_fTotalLife,
    m_fLife,
    m_fAlpha,
    m_fSize,
    m_fBounciness;
  bool
    m_boActive;

public:

  Vector3f
    m_color3,
    m_position3,
    m_velocity3,
    m_acceleration3,
    m_rotation3;

//---------- Ctor/Dtor ---------------------------------------

public:

  Particle(
    int iID
  );

  ~Particle(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  void vUpdate(
    long time
  );

//---------- Private Functions -------------------------------

private:

};

//----------------------------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------


class Emitter
/*
  Purpose: Particle emitter
  Written: 13 Jun 2010: JH
*/
{

//---------- Member Variables --------------------------------

  list<Particle*>
    m_listParticles;
  Texture
    *m_pTexture;
  float
    m_fEmissionRate,
    m_fEmissionRadius,
    m_fLife,
    m_fLifeRange,
    m_fSize,
    m_fSizeRange,
    m_fSaturation,
    m_fAlpha,
    m_fSpread,
    m_fGravity;
  long
    m_lastTime;
  Vector3f
    m_position3,
    m_wind3,
    m_rotation3;

//---------- Ctor/Dtor ---------------------------------------

public:

  Emitter(
  );

  ~Emitter(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  void vUpdate(
    long time
  );

  //----------------------------------------------------------

  void vSetTexture(
    Texture *pTexture
  );

//---------- Protected Functions -----------------------------

  void vAddParticle(
  );

//---------- Private Functions -------------------------------

private:

};

#endif