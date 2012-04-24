/********** Includes ****************************************/

#include <vector>

#include "GLEngine.hpp"
#include "Math.hpp"
#include "Structs.hpp"
#include "Projectile.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Item.hpp"
#include "Weapons.hpp"
#include <string>
#include "Inventory.hpp"

#include "Player.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

Player::Player(
  const char *sName,
  Point pos,
  const char *sModel
) : m_rotation(0.0f, 0.0f, 0.0f), m_targetVector(0.0f, 0.0f, 0.0f)
{
  m_pModel = new Model(sModel);
  strcpy_s(m_sName, sizeof(m_sName), sName);

  m_pCurrWeapon = new Ranged(10.0f, 2.0f, 5.0f, 0.015f);

  m_pInventory = new Inventory();

//   m_pInventory->vAddItem(new Ranged(10.0f, 2.0f, 5.0f, 0.015f, new Model("bearBox.3ds"), "", Point(0, 0, 0), new Texture("itemicon.tga", "Item Icon")));
//   m_pInventory->vAddItem(new Ranged(10.0f, 2.0f, 5.0f, 0.015f, new Model("bearBox.3ds"), "", Point(0, 0, 0), new Texture("itemicon2.tga", "Item Icon")));
//   m_pInventory->vAddItem(new Ranged(10.0f, 2.0f, 5.0f, 0.015f, new Model("bearBox.3ds"), "", Point(0, 0, 0), new Texture("itemicon3.tga", "Item Icon")));
//   m_pInventory->vAddItem(new Ranged(10.0f, 2.0f, 5.0f, 0.015f, new Model("bearBox.3ds"), "", Point(0, 0, 0), new Texture("itemicon4.tga", "Item Icon")));
//   m_pInventory->vAddItem(new Ranged(10.0f, 2.0f, 5.0f, 0.015f, new Model("bearBox.3ds"), "", Point(0, 0, 0), new Texture("itemicon5.tga", "Item Icon")));
//   m_pInventory->vAddItem(new Ranged(10.0f, 2.0f, 5.0f, 0.015f, new Model("bearBox.3ds"), "", Point(0, 0, 0), new Texture("itemicon6.tga", "Item Icon")));

  m_pos = pos;
  m_targetPos = pos;
  m_fHealth = 100.0f;

  m_lastTime = 0;
}

Player::~Player(
)
{
  if(m_pModel != NULL)
    delete m_pModel;

  if(m_pCurrWeapon != NULL)
    delete m_pCurrWeapon;

  if(m_pInventory != NULL)
    delete m_pInventory;
}

/************************************************************/

void Player::vTargetMove(
  Point &target
)
/*
  Purpose: Set target point to move to and update rotation based on new direction
  Written: 31 Jul 2011: JH
*/
{
  // Set target position and update the rotation
  m_targetPos = target;

  Vector3f
    targetVector(m_pos, m_targetPos);
  targetVector.vNormalize();

  m_targetVector = targetVector;

  const float
    fTmp = acos(m_targetVector[X]/m_targetVector.fMagnitude());

  m_rotation[Y] = s_fVectorDegrees(m_targetVector);
}

/************************************************************/

void Player::vRotate(
  float degree,
  int axis
)
{
  switch(axis)
  {
  case X:
    m_rotation[X] = degree;
    break;

  case Y:
    m_rotation[Y] = degree;
    break;

  case Z:
    m_rotation[Z] = degree;
    break;
  }
}

/************************************************************/

void Player::vDraw(
)
{
  m_pModel->vDrawModel(m_pos, m_rotation);
}

/************************************************************/

void Player::vDrawInventory(
  int iMousePosX,
  int iMousePosY
) const
{
  m_pInventory->vDraw(iMousePosX, iMousePosY);
}

/************************************************************/

void Player::vPosSet(
  Point pos
)
{
  m_pos = pos;
}

/************************************************************/

Projectile *Player::pShoot(
  Point target
)
{
  // Stop player when shooting
  m_targetPos = m_pos;

  Vector3f
    targetVector(m_pos, target);

  targetVector.vNormalize();

  // Set player rotation in the direction of the shot
  m_rotation[Y] = s_fVectorDegrees(targetVector);

  Projectile
    *pProj = m_pCurrWeapon->pAttack(m_pos, targetVector);
  return pProj;
}

/************************************************************/

bool Player::boCanAttack(
  const long currTime
)
{
  // Speed decides nr of shots/attacks pr second
  const long
    diffTime = (long)m_pCurrWeapon->fSpeed() * (currTime - m_lastTime);
  bool
    boRet = diffTime > 1000;

  if(boRet)
    m_lastTime = currTime;

  return boRet;
}

/************************************************************/

void Player::vAddItem(
  Item* pItem
)
{
  m_pInventory->vAddItem(pItem);
}

/************************************************************/

bool Player::boHandleInventory(
  int iMousePosX,
  int iMousePosY
)
{
  return m_pInventory->boHandleInventory(iMousePosX, iMousePosY);
}

/************************************************************/

Item *Player::pClickInventory(
  int iMousePosX,
  int iMousePosY
)
{
  return m_pInventory->pHandleClick(iMousePosX, iMousePosY);
}