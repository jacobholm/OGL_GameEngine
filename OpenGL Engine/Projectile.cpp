/********** Includes ****************************************/
#include <math.h>

#include "GLEngine.hpp"
#include "Math.hpp"
#include "Projectile.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

Projectile::~Projectile(
)
{

}

/************************************************************/

void Projectile::vDraw(
)
{
  GLfloat
    radians,
    fCosVal,
    fSinVal,
    fRadius = 0.5f;

  glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex3f(m_pos[X], 0, m_pos[Z]);

    for(int i = 0; i <= 360; i++)
    {
      radians = DegreesToRads(i);

      fCosVal = cos(radians);
      fSinVal = sin(radians);
      if(i%8 == 0)
        glVertex3f(m_pos[X] + (fCosVal*fRadius), 0, m_pos[Z] + (fSinVal*fRadius));
    }
  glEnd();

  glEnable(GL_TEXTURE_2D);
}