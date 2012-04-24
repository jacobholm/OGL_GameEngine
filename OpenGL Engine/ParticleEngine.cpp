#if 0 // @@@ On hold for now

/********** Includes ****************************************/

#include "ParticleEngine.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

Emitter::Emitter(
)
{
  m_pTexture = NULL;
  m_fEmissionRate = 30.0f;
  m_fEmissionRadius = 0.0f;
  m_fLife = 2.0f;
  m_fLifeRange = 0.5f;
  m_fSize = 5.0f;
  m_fSizeRange = 2.0f;
  m_fSaturation = 1.0f;
  m_fAlpha = 0.5f;
  m_fSpread = 1.0f;
  m_fGravity = 0.0f;
}

Emitter::~Emitter(
)
{
  for(list<Particle*>::iterator it = m_listParticles.begin(); it != m_listParticles.end(); it++)
    delete (*it);
}


/************************************************************/

void Emitter::vUpdate(
  long time
)
{
  if(m_pTexture = NULL)
    return;

  // Make sure no particles are emitted on the very first update(iNumEmission will equal 0)
  if(m_lastTime == -1)
    m_lastTime = time;

  // Calculate how many particles to emit based on how much time has passed
  int
    iNumEmission = (int)((float)(time - m_lastTime) / 1000.0f * m_fEmissionRate);

  // Add each particle
  for(int i = 0; i < iNumEmission; i++)
    vAddParticle();

  // Update last time if there are any active particles
  if(iNumEmission > 0)
    m_lastTime = time;

  // Lighting and depth testing isn't necessary and would cause problems
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(m_position3.X, m_position3.Y, m_position3.Z);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, m_pTexture->iTexIDGet());

  for(list<Particle*>::iterator it = m_listParticles.begin(); it != m_listParticles.end(); it++)
  {
    Particle
      *pParticle = (*it);

    pParticle->m_acceleration3.Y = -m_fGravity;
    pParticle->m_acceleration3 += m_wind3;
    pParticle->m_rotation3 = m_rotation3;
    pParticle->vAlphaSet(m_fAlpha);

    pParticle->vUpdate(time);

    // Delete the particle if it is inactive, then erase the index where it was stored
    if(!pParticle->boActive())
    {
      delete pParticle;
      m_listParticles.erase(it);
    }
  }

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

/************************************************************/

void Emitter::vSetTexture(
  Texture *pTexture
)
{
  m_pTexture = pTexture;
}

/************************************************************/

void Emitter::vAddParticle(
)
{

}

#endif