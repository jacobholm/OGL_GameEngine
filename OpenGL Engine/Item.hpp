/*
  Written: 04 Aug 2011: JH
  Comment:
*/

#ifndef ITEM_H
#define ITEM_H

/********** Includes ****************************************/

/********** Local Defines ***********************************/

/************************************************************/

class Item abstract
/*
  Purpose: Base class for all items
  Written: 04 Aug 2011: JH
*/
{

//---------- Member Variables --------------------------------

protected:

  std::string
    m_sName;
  Point
    m_pos;
  Vector3f
    m_rotation;
  Model
    *m_pModel;
  float
    m_fDurability,
    m_fPrice;
  int
    m_iLevelReq;
  Texture
    *m_pIcon; // An icon representing the item, used in inventory
  /*
    m_attributes;
  */

//---------- Ctor/Dtor ---------------------------------------

public:

  Item(
  )
  {
    // Init vars
    // NB! C++ does not support calling one ctor from another, just creates a local object
  }

  Item(
    std::string sName,
    Point pos,
    Model *pModel,
    float fDurability,
    float fPrice,
    int iLevelReq,
    Texture *pIcon
  ) : m_sName(sName), m_pos(pos), m_rotation(0, 0, 0), m_pModel(pModel), m_fDurability(fDurability), m_fPrice(fPrice), m_iLevelReq(iLevelReq), m_pIcon(pIcon)
  {

  }

  virtual ~Item(
  )
  {
    if(m_pModel != NULL)
      delete m_pModel;

    if(m_pIcon != NULL)
      delete m_pIcon;
  }

//---------- Set/Get Member Variables ------------------------

  virtual void vNameSet(
    std::string sName
  )
  {
    m_sName = sName;
  }

  virtual std::string sName(
  )
  {
    return m_sName;
  }

  //----------------------------------------------------------

  virtual Model *pModel(
  )
  {
    return m_pModel;
  }

  //----------------------------------------------------------

  virtual void vPosSet(
    Point pos
  )
  {
    m_pos = pos;
  }

  virtual Point pos(
  )
  {
    return m_pos;
  }

  //----------------------------------------------------------

  virtual void vRotSet(
    Vector3f rot
  )
  {
    m_rotation = rot;
  }

  virtual Vector3f rot(
  )
  {
    return m_rotation;
  }

  //----------------------------------------------------------

  virtual void vLevelReqSet(
    int iReq
  )
  {
    m_iLevelReq = iReq;
  }

  virtual int iLevelReq(
  )
  {
    return m_iLevelReq;
  }

  //----------------------------------------------------------

  virtual void vDurabilitySet(
    float fDurability
  )
  {
    m_fDurability = fDurability;
  }

  virtual float fDurability(
  )
  {
    return m_fDurability;
  }

  //----------------------------------------------------------

  virtual void vPriceSet(
    float fPrice
  )
  {
    m_fPrice = fPrice;
  }

  virtual float fPrice(
  )
  {
    return m_fPrice;
  }

//---------- Public Functions --------------------------------

  virtual void vDraw(
  )
  {
    m_pModel->vDrawModel(m_pos, m_rotation);
  }

  //----------------------------------------------------------

  virtual void vDrawIcon(
  )
  {
    glBindTexture(GL_TEXTURE_2D, m_pIcon->iTexIDGet()); // Select Our Texture

    glBegin(GL_QUADS);
      glColor3f(1.0f, 1.0f, 1.0f);

      glNormal3f(0.0f, 1.0f, 0.0f);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(m_pos[X], m_pos[Y], 0.0f);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(m_pos[X], m_pos[Y] + 64.0f, 0.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex3f(m_pos[X] + 64.0f, m_pos[Y] + 64.0f, 0.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(m_pos[X] + 64.0f, m_pos[Y], 0.0f);

    glEnd();
  }

  //----------------------------------------------------------

  virtual lineSegment colBox(
  )
  {
    return m_pModel->getCollisionBox();
  }

//---------- Private Functions -------------------------------

private:

};

#endif