/*
  Written: 09 Mar 2010: JH
  Comment: 
*/

#ifndef LIGHT_H
#define LIGHT_H

/********** Includes ****************************************/

//#include <vector>
//#include "Math.hpp"

/********** Local Defines ***********************************/

/************************************************************/

enum LIGHT_TYPE // Helper struct for setting up parameters based on type of light wanted
{
  LIGHT_SPOT,
  LIGHT_POINT,
  LIGHT_DIRECTIONAL
};

class Light
/*
  Written: 09 Mar. 2010: JH
  Purpose: 
*/
{

//---------- Member Variables --------------------------------

  static int
    s_iMaxNumLights;      // The maximum number of lights the graphics card can handle
  static std::vector<int>
    s_vecAvailableLights; // All the lights that are available to us
  static std::vector<Light*>
    s_vecLights;          // Vector3f of all the lights currently in use

  float
    m_fPosition[4],
    m_fDiffuse[4],
    m_fAmbient[4],
    m_fSpecularity[4],
    m_fSpotDirection[4],
		m_fAttenuation[4],
    m_fCutoff,
    m_fExponent;
  bool
    m_boVisible;  // Is the light active or not
  int
    m_iLightType, // The type of light, based on the LIGHT_TYPE enum
    m_iLightNum;  // Which light is this

//---------- Ctor/Dtor ---------------------------------------

public:

  Light(
    LIGHT_TYPE lightType
  );

  ~Light(
  );

//---------- Set/Get Member Variables ------------------------

  static std::vector<Light*> &s_vecLightsGet(
  )
  {
    return s_vecLights;
  }

  //----------------------------------------------------------

  void vVisibleSet(
    bool boVisible = true
  );

  //----------------------------------------------------------

  void vDiffuseSet(
    float fRed,
    float fGreen,
    float fBlue,
    float fAlpha = 1.0f
  );

	float *afDiffuseGet(
	);

  //----------------------------------------------------------

  void vAmbientSet(
    float fRed,
    float fGreen,
    float fBlue,
    float fAlpha
  );

	float *afAmbientGet(
	);

  //----------------------------------------------------------

  void vSpecularitySet(
    float fRed,
    float fGreen,
    float fBlue,
    float fAlpha
  );

	float *afSpecularityGet(
	);

  //----------------------------------------------------------
  
  void vLightTypeSet(
    LIGHT_TYPE lightType
  );

  //----------------------------------------------------------

  void vPositionSet(
    float fX,
    float fY,
    float fZ
  );

	float *afPositionGet(
	);

  //----------------------------------------------------------

  void vSpotDirectionSet(
    float fX,
    float fY,
    float fZ
  );

	float *afSpotDirectionGet(
	);

  //----------------------------------------------------------

  void vCutoffSet(
    float fCutoff
  );

	float &fCutoffGet(
	);

  //----------------------------------------------------------

  void vExponentSet(
    float fExponent
  );

	float &fExponentGet(
	);

  //----------------------------------------------------------

  void vAttenuationSet(
    float fConstant,
    float fLinear,
    float fQuadratic
  );

	float *afAttenuationGet(
	);

  //----------------------------------------------------------

  int iLightNumGet(
  )
  {
    return m_iLightNum;
  }

//---------- Public Functions --------------------------------

  void vUpdateLight(
  );

  //----------------------------------------------------------

  static void s_vInitAvailableLights(
  );

//---------- Private Functions -------------------------------

private:

};

#endif