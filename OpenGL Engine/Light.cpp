/*
  Written: 09 Mar 2010: JH
  Comment: 
*/

/********** Includes ****************************************/

#include <vector>

#include "GLEngine.hpp"
#include "Light.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

int
  Light::s_iMaxNumLights = 0;
std::vector<int>
  Light::s_vecAvailableLights;
std::vector<Light*>
  Light::s_vecLights;

/************************************************************/

Light::Light(
  LIGHT_TYPE lightType
)
/*
  Written: 09 Mar 2010: JH
  Purpose: 
*/
{
  s_vecLights.push_back(this);  // Put this light in the list

  // If there are lights available assign a number to this light
  if(!s_vecAvailableLights.empty())
  {
    m_iLightNum = *s_vecAvailableLights.begin();               // Assign the first available light number to this light
    s_vecAvailableLights.erase(s_vecAvailableLights.begin()); // The light is now in use and no longer available, erase it
    vLightTypeSet(lightType);                                 // Set the light type passed to us

    // Initialize with default values
    vPositionSet(0, 0, 0);
    vSpotDirectionSet(0, -1, 0);
    vCutoffSet(45);
    vExponentSet(12);
    vAmbientSet(0, 0, 0, 1);
    vDiffuseSet(1, 1, 1, 1);
    vSpecularitySet(1, 1, 1, 1);

    vVisibleSet(true);  // Activate the light

    vUpdateLight();
  }
  else  // No lights are available
  {
    m_iLightNum = 0;  // Light number 0 does not exist, so using this light does nothing
    vVisibleSet(false); // Deactivate light
  }
}

Light::~Light(
)
/*
  Written: 09 Mar 2010: JH
  Purpose: 
*/
{
  if(m_iLightNum != 0)  // If the light was initialized correctly upon creation..
    s_vecAvailableLights.push_back(m_iLightNum);  // ..make the light number available again

  // Find _this_ light in the global list and delete it
  for(std::vector<Light*>::iterator it = s_vecLights.begin(); it != s_vecLights.end(); it++)
    if((*it) == this)
      s_vecLights.erase(it);
}

/************************************************************/

void Light::vVisibleSet(
  bool boVisible
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  m_boVisible = boVisible;

  if(m_boVisible)
    glEnable(m_iLightNum);
  else
    glDisable(m_iLightNum);
}

/************************************************************/

void Light::vDiffuseSet(
  float fRed,
  float fGreen,
  float fBlue,
  float fAlpha	// Not in use by GL_DIFFUSE call?! Default = 1.0f
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  m_fDiffuse[0] = fRed;
  m_fDiffuse[1] = fGreen;
  m_fDiffuse[2] = fBlue;
  m_fDiffuse[3] = fAlpha;
	
  glLightfv(m_iLightNum, GL_DIFFUSE, m_fDiffuse); // Pass the diffuse value to the light in question
}

float *Light::afDiffuseGet(
)
/*
  Written: 11 Sep 2010: JH
  Purpose: 
*/
{
  return m_fDiffuse;
}

/************************************************************/

void Light::vAmbientSet(
  float fRed,
  float fGreen,
  float fBlue,
  float fAlpha
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  m_fAmbient[0] = fRed;
  m_fAmbient[1] = fGreen;
  m_fAmbient[2] = fBlue;
  m_fAmbient[3] = fAlpha;

  glLightfv(m_iLightNum, GL_AMBIENT, m_fAmbient); // Pass the ambient value to the light in question
}

float *Light::afAmbientGet(
)
/*
  Written: 11 Sep 2010: JH
  Purpose: 
*/
{
	return m_fAmbient;
}

/************************************************************/

void Light::vSpecularitySet(
  float fRed,
  float fGreen,
  float fBlue,
  float fAlpha
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  m_fSpecularity[0] = fRed;
  m_fSpecularity[1] = fGreen;
  m_fSpecularity[2] = fBlue;
  m_fSpecularity[3] = fAlpha;

  glLightfv(m_iLightNum, GL_SPECULAR, m_fSpecularity); // Pass the specularity value to the light in question
}

float *Light::afSpecularityGet(
)
/*
  Written: 11 Sep 2010: JH
  Purpose: 
*/
{
	return m_fSpecularity;
}

/************************************************************/

void Light::vLightTypeSet(
  LIGHT_TYPE lightType
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  m_iLightType = lightType;

  if(m_iLightType == LIGHT_SPOT)
  {
    m_fPosition[3] = 1.0f;  // The fourth element decides what kind of light this is
  }
  else if(m_iLightType == LIGHT_POINT)
  {
    m_fPosition[3] = 1.0f;
    vCutoffSet(180.0f); // It's a point light and should emit light in a 180 degree radius
  }
  else if(m_iLightType == LIGHT_DIRECTIONAL)
    m_fPosition[3] = 0.0f;

  vUpdateLight();
}

/************************************************************/

void Light::vPositionSet(
  float fX,
  float fY,
  float fZ
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  m_fPosition[0] = fX;
  m_fPosition[1] = fY;
  m_fPosition[2] = fZ;

  glLightfv(m_iLightNum, GL_POSITION, m_fPosition); // Pass the position value to the light in question
}

float *Light::afPositionGet(
)
{
	return m_fPosition;
}

/************************************************************/

void Light::vSpotDirectionSet(
  float fX,
  float fY,
  float fZ
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  m_fSpotDirection[0] = fX;
  m_fSpotDirection[1] = fY;
  m_fSpotDirection[2] = fZ;

  glLightfv(m_iLightNum, GL_SPOT_DIRECTION, m_fSpotDirection); // Pass the spot direction value to the light in question
}

float *Light::afSpotDirectionGet(
)
/*
  Written: 11 Sep 2010: JH
  Purpose: 
*/
{
  return m_fSpotDirection;
}

/************************************************************/

void Light::vCutoffSet(
  float fCutoff
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  m_fCutoff = fCutoff;

  glLightf(m_iLightNum, GL_SPOT_CUTOFF, m_fCutoff); // Pass the spot cutoff value to the light in question
}

float &Light::fCutoffGet(
)
/*
  Written: 11 Sep 2010: JH
  Purpose: 
*/
{
  return m_fCutoff;
}

/************************************************************/

void Light::vExponentSet(
  float fExponent
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  m_fExponent = fExponent;

  glLightf(m_iLightNum, GL_SPOT_EXPONENT, m_fExponent); // Pass the spot exponent value to the light in question
}

float &Light::fExponentGet(
)
/*
  Written: 11 Sep 2010: JH
  Purpose: 
*/
{
  return m_fExponent;
}

/************************************************************/

void Light::vAttenuationSet(
  float fConstant,
  float fLinear,
  float fQuadratic
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
	m_fAttenuation[0] = fConstant;
	m_fAttenuation[1] = fLinear;
	m_fAttenuation[2] = fQuadratic;

  // Set the attenuation/falloff of the light
  glLightf(m_iLightNum, GL_CONSTANT_ATTENUATION, m_fAttenuation[0]);
  glLightf(m_iLightNum, GL_LINEAR_ATTENUATION, m_fAttenuation[1]);
  glLightf(m_iLightNum, GL_QUADRATIC_ATTENUATION, m_fAttenuation[2]);
}

float *Light::afAttenuationGet(
)
/*
  Written: 11 Sep 2010: JH
  Purpose: 
*/
{
	// Return the attenuation/falloff of the light
	return m_fAttenuation;
}

/************************************************************/

void Light::vUpdateLight(
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  glLightfv(m_iLightNum, GL_POSITION, m_fPosition);            // Update light position
  glLightfv(m_iLightNum, GL_SPOT_DIRECTION, m_fSpotDirection); // Update light direction
}

/************************************************************/

void Light::s_vInitAvailableLights(
)
/*
  Written: 10 Mar 2010: JH
  Purpose: 
*/
{
  glGetIntegerv(GL_MAX_LIGHTS, &Light::s_iMaxNumLights);  // Get the maximum number of lights supported by the graphics card

  for(int i = 0; i < Light::s_iMaxNumLights; i++)
    Light::s_vecAvailableLights.push_back(GL_LIGHT0 + i); // Set each light to be available
}