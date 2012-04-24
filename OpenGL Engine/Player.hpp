/*
  Written: 31 Jul 2011: JH
  Comment: The player class holding attributes, models etc
*/

#ifndef PLAYER_H
#define PLAYER_H

/********** Includes ****************************************/

/********** Local Defines ***********************************/

/************************************************************/

class Item;
class Weapon;
class Projectile;
class Inventory;

class Player
/*
  Purpose: 
  Written: 31 Jul 2011: JH
*/
{

//---------- Member Variables --------------------------------

  char
    m_sName[10];
  Model
    *m_pModel;
  Point
    m_pos,
    m_targetPos;    // What position to move to after user clicked
  Vector3f
    m_targetVector, // Vector between model position and target
    m_rotation;     // XYZ Rotation  
  float
    m_fHealth;
  long
    m_lastTime;     // Can you place this outside Player class?
  Inventory
    *m_pInventory;
  Weapon
    *m_pCurrWeapon;

//---------- Ctor/Dtor ---------------------------------------

public:

  Player(
    const char *sName,
    Point pos,
    const char *sModel
  );

  ~Player(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  //----------------------------------------------------------

  void vRotate(
    float degree,
    int axis
  );

  //----------------------------------------------------------

  Point &targetPos(
  )
  {
    return m_targetPos;
  }

  void vTargetMove(
    Point &target
  );

  //-------------------------------------

  bool boMovingToTarget(
  )
  {
    Vector3f
      targetVector(m_pos, m_targetPos);
    targetVector.vNormalize();

    return Dot(targetVector, m_targetVector) > 0;
  }

  //----------------------------------------------------------

  float fCollCircleRadius(
  )
  {
    return m_pModel->fCollCircleRadius();
  }

  void vDraw(
  );

  void vDrawInventory(
    int iMousePosX,
    int iMousePosY
  ) const;

  //----------------------------------------------------------

  const Point &posGet(
  ) const
  {
    return m_pos;
  }

  void vPosSet(
    Point pos
  );

  //---------------------------------

  const float &fRotXGet(
  ) const
  {
    return m_rotation[X];
  }

  //-----------------------------

  const float &fRotYGet(
  ) const
  {
    return m_rotation[Y];
  }

  //----------------------------------------------------------

  Projectile *pShoot(
    Point target
  );

  //----------------------------------------------------------

  bool boCanAttack(
    const long diffTime
  );

  //----------------------------------------------------------

  void vHealthSet(
    float fHealth
  )
  {
    m_fHealth = fHealth;
  }

  float fHealth(
  )
  {
    return m_fHealth;
  }

  //----------------------------------------------------------

  lineSegment colBoxGet(
  )
  {
    return m_pModel->getCollisionBox();
  }

  //----------------------------------------------------------

  void vAddItem(
    Item* pItem
  );

  //----------------------------------------------------------

  bool boHandleInventory(
    int iMousePosX,
    int iMousePosY
  );

  //----------------------------------------------------------

  Item *pClickInventory(
    int iMousePosX,
    int iMousePosY
  );

//---------- Private Functions -------------------------------

private:

};

#endif