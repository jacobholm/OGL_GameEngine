/********** Includes ****************************************/

#include "Transform.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

Transform::Transform(
) : Node()
{
		m_vecScale = Vector3f(1.0f, 1.0f, 1.0f);
}

Transform::~Transform(
)
{

}

/************************************************************/


void Transform::vSetTranslation(
		float fX,
		float fY,
		float fZ
)
{
		m_vecTranslation[X] = fX;
		m_vecTranslation[Y] = fY;
		m_vecTranslation[Z] = fZ;
}

Vector3f &Transform::vecGetTranslation(
)
{
		return m_vecTranslation;
}

/************************************************************/

void Transform::vSetRotation(
		float fX,
		float fY,
		float fZ
)
{
		m_vecRotation[X] = fX;
		m_vecRotation[Y] = fY;
		m_vecRotation[Z] = fZ;
}

Vector3f &Transform::vecGetRotation(
)
{
		return m_vecRotation;
}

/************************************************************/


void Transform::vSetScale(
		float fX,
		float fY,
		float fZ
)
{
		m_vecScale[X] = fX;
		m_vecScale[Y] = fY;
		m_vecScale[Z] = fZ;
}

Vector3f &Transform::vecGetScale(
)
{
		return m_vecScale;
}