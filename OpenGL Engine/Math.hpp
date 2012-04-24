/*
  Written: 23 Nov 2010: JH
  Comment:
*/

#ifndef MATH_H
#define MATH_H

/********** Includes ****************************************/

#include <math.h>

/********** Defines *****************************************/

#define X 0
#define Y 1
#define Z 2

#define DegreesToRads(degrees) ((degrees)*(PI/180.0f))
#define RadsToDegrees(degrees) ((degrees)*(180.0f/PI))
#define RoundOff(num, deci)													\
                    {																\
                    int op;												\
                    op = (num > 0) ? 1 : (-1);		\
                    num = abs(num);								\
                    num = (num*deci+0.5f);	      \
                    num = (floor(num));						\
                    num = (num/deci);							\
                    num *= op;										\
                    }

#define PI 3.14159265f

#define Dot(vec1, vec2) (vec1[X] * vec2[X])  + (vec1[Y] * vec2[Y]) + (vec1[Z] * vec2[Z])

/************************************************************/

class Point
/*
  Purpose:
  Written: 07 Dec 2010: JH
*/
{

//---------- Member Variables --------------------------------

  float
    m_afPoint[3];

//---------- Ctor/Dtor ---------------------------------------

public:

  Point(
    float fX,
    float fY,
    float fZ
  )
  {
    m_afPoint[X] = fX;
    m_afPoint[Y] = fY;
    m_afPoint[Z] = fZ;
  }

  Point(
  )
  {
    Point(0.0f, 0.0f, 0.0f);
  }

  ~Point(
  )
  {}

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  float &operator[](
    int i
  )
  {
    return m_afPoint[i];
  }

  const float &operator[](
    int i
  ) const
  {
    return m_afPoint[i];
  }

  Point operator+(
    Point p
  )
  {
    return Point(m_afPoint[X] + p[X], m_afPoint[Y] + p[Y], m_afPoint[Z] + p[Z]);
  }

  Point operator+(
    const Point p
  ) const
  {
    return Point(m_afPoint[X] + p[X], m_afPoint[Y] + p[Y], m_afPoint[Z] + p[Z]);
  }

  Point operator-(
    Point p
  )
  {
    return Point(m_afPoint[X] - p[X], m_afPoint[Y] - p[Y], m_afPoint[Z] - p[Z]);
  }

  Point operator-(
    const Point p
  ) const
  {
    return Point(m_afPoint[X] - p[X], m_afPoint[Y] - p[Y], m_afPoint[Z] - p[Z]);
  }

  Point operator*(
    float fValue
  )
  {
    return Point(m_afPoint[X] * fValue, m_afPoint[Y] * fValue, m_afPoint[Z] * fValue);
  }

  void operator=(
    Point &p
  )
  {
    m_afPoint[X] = p[X];
    m_afPoint[Y] = p[Y];
    m_afPoint[Z] = p[Z];
  }

  //----------------------------------------------------------

  void vSet(
    float fX,
    float fY,
    float fZ
  )
  {
    m_afPoint[X] = fX;
    m_afPoint[Y] = fY;
    m_afPoint[Z] = fZ;
  }
//---------- Private Functions -------------------------------

private:

};

/************************************************************/

class Vector3f
/*
  Purpose: Custom Vector3f class
  Written: 13 Jun 2010: JH
*/
{

//---------- Member Variables --------------------------------

  float
    m_afVector3f[3];

//---------- Ctor/Dtor ---------------------------------------
public:
  Vector3f(
    float fX,
    float fY,
    float fZ
  )
  {
    m_afVector3f[X] = fX;
    m_afVector3f[Y] = fY;
    m_afVector3f[Z] = fZ;
  }

  Vector3f(
    Point p1,
    Point p2
  )
  {
    m_afVector3f[X] = p2[X] - p1[X];
    m_afVector3f[Y] = p2[Y] - p1[Y];
    m_afVector3f[Z] = p2[Z] - p1[Z];
  }

  Vector3f(
  )
  {Vector3f(0.0f, 0.0f, 0.0f);}

  //---------- Public Functions --------------------------------

  void vWallVectorSet(
    Point &p1,
    Point &p2
  )
  {
    m_afVector3f[X] = p2[X] - p1[X];
    m_afVector3f[Y] = p2[Y] - p1[Y];
    m_afVector3f[Z] = p2[Z] - p1[Z];
  }

  //----------------------------------------------------------

  float& operator[](
    int i
  )
  {
    return m_afVector3f[i];
  }

  const float& operator[](
    int i
  ) const
  {
    return m_afVector3f[i];
  }

  //------------------------------------------------------------

  Vector3f& operator+(
    const Vector3f vec
  )
  {
    m_afVector3f[X] += vec[X];
    m_afVector3f[Y] += vec[Y];
    m_afVector3f[Z] += vec[Z];

    return *this;
  }

  Vector3f& operator+=(
    const Vector3f vec
  )
  {
    return *this + vec;
  }

  Vector3f operator+(
    float fValue
  )
  {
    Vector3f
      ret;

    ret[X] = m_afVector3f[X] + fValue;
    ret[Y] = m_afVector3f[Y] + fValue;
    ret[Z] = m_afVector3f[Z] + fValue;

    return ret;
  }

  void operator+=(
    float fValue
  )
  {
    m_afVector3f[X] += fValue;
    m_afVector3f[Y] += fValue;
    m_afVector3f[Z] += fValue;
  }

  //----------------------------------------------------------

  Vector3f& operator-(
    const Vector3f vec
  )
  {
    m_afVector3f[X] -= vec[X];
    m_afVector3f[Y] -= vec[Y];
    m_afVector3f[Z] -= vec[Z];

    return *this;
  }
  
  //----------------------------------------------------------

  Vector3f operator-(
  )
  {
    Vector3f
      vecReturn;
    vecReturn[X] = -m_afVector3f[X];
    vecReturn[Y] = -m_afVector3f[Y];
    vecReturn[Z] = -m_afVector3f[Z];

    return vecReturn;
  }

  //----------------------------------------------------------

  Vector3f& operator/(
    const Vector3f vec
  )
  {
    m_afVector3f[X] /= vec[X];
    m_afVector3f[Y] /= vec[Y];
    m_afVector3f[Z] /= vec[Z];

    return *this;
  }

  Vector3f& operator/=(
    const Vector3f vec
  )
  {
    return *this / vec;
  }

  Vector3f& operator/(
    const int i
  )
  {
    m_afVector3f[X] /= i;
    m_afVector3f[Y] /= i;
    m_afVector3f[Z] /= i;

    return *this;
  }

  Vector3f& operator/=(
    const int i
  )
  {
    return *this / i;
  }

  //----------------------------------------------------------

  Vector3f operator*(
    float fValue
  )
  {
    Vector3f
      ret;

    ret[X] = m_afVector3f[X] * fValue;
    ret[Y] = m_afVector3f[Y] * fValue;
    ret[Z] = m_afVector3f[Z] * fValue;

    return ret;
  }

  Vector3f& operator*(
    const Vector3f vec
  )
  {
    m_afVector3f[X] *= vec[X];
    m_afVector3f[Y] *= vec[Y];
    m_afVector3f[Z] *= vec[Z];

    return *this;
  }

  //----------------------------------------------------------

  bool boIsZero(
  )
  {
    if(m_afVector3f[X] == 0 && m_afVector3f[Y] == 0 && m_afVector3f[Z] == 0)
      return true;
    return false;
  }

  //----------------------------------------------------------

  float fMagnitude(
  ) const
  {
    return sqrt(m_afVector3f[X] * m_afVector3f[X] + m_afVector3f[Y] * m_afVector3f[Y] + m_afVector3f[Z] * m_afVector3f[Z]);
  }

  //----------------------------------------------------------

  void vNormalize(
  )
  {
    float
      fLength = fMagnitude();

    if(fLength == 0)  // ERROR
      return;

    m_afVector3f[X] /= fLength;
    m_afVector3f[Y] /= fLength;
    m_afVector3f[Z] /= fLength;
  }

  //----------------------------------------------------------

  bool operator==(
    Vector3f vec
  )
  {
    return vec[X] == m_afVector3f[X] && vec[Y] == m_afVector3f[Y] && vec[Z] == m_afVector3f[Z];
  }

//---------- Private Functions -------------------------------

private:

};

static float s_fVectorDegrees(
  const Vector3f &vec
)
{
  const float
    fRotationRad = acos(vec[X]/vec.fMagnitude());

  if( !((vec[X] > 0 && vec[Z] > 0) || (vec[X] <= 0 && vec[Z] > 0)) )
    return RadsToDegrees((2*PI) - fRotationRad);
  else
    return RadsToDegrees(fRotationRad);
}

#endif