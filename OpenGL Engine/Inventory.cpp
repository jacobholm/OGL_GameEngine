/********** Includes ****************************************/

#include <vector>

#include "GLEngine.hpp"
#include "Math.hpp"
#include "Structs.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Item.hpp"


#include "Inventory.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

enum EquipmentSlot
{
  OUTSIDE,
  HEAD,
  TORSO,
  RIGHTHAND,
  LEFTHAND
};

Inventory::Inventory(
)
{
  m_pTexture = new Texture("inventory.tga", "Inventory");

  m_pEquipmentHead = m_pEquipmentTorso = m_pEquipmentRightHand = m_pEquipmentLeftHand = m_pItemInCursor = NULL;

  m_iSlots = 16;
  m_slotItems.resize(m_iSlots, NULL);
  m_pos.vSet(0, 128, 0);
}

Inventory::~Inventory(
)
{
  if(m_pTexture != NULL)
    delete m_pTexture;

  // Delete slot items
  for(unsigned int i = 0; i < m_slotItems.size(); i++)
    if(m_slotItems[i] != NULL)
      delete m_slotItems[i];

  // Delete equipped items
  if(m_pEquipmentHead != NULL)
    delete m_pEquipmentHead;
  if(m_pEquipmentTorso != NULL)
    delete m_pEquipmentTorso;
  if(m_pEquipmentRightHand != NULL)
    delete m_pEquipmentRightHand;
  if(m_pEquipmentLeftHand != NULL)
    delete m_pEquipmentLeftHand;
}

/************************************************************/

void Inventory::vDropIntoSlot(
  int iMousePosX,
  int iMousePosY
)
{
  int
    iSelectedSlot = iSlotClicked(iMousePosX, iMousePosY);

  // Put item into an inventory slot
  if(boInsideInventory(iMousePosX, iMousePosY) && m_slotItems[iSelectedSlot] == NULL)
  {
    // Drop current item in cursor into the given inventory slot
    m_slotItems[iSelectedSlot] = m_pItemInCursor;
    m_pItemInCursor = NULL;
  }
  else if(boInsideEquipment(iMousePosX, iMousePosY)) // Equip item
  {
    EquipmentSlot
      eqSlot = equipmentSlotClicked(iMousePosX, iMousePosY);

    // Where to put it?
    switch(eqSlot)
    {
    case HEAD:
      if(m_pEquipmentHead == NULL)
      {
        m_pEquipmentHead = m_pItemInCursor;
        m_pItemInCursor = NULL;
      }
      break;

    case TORSO:
      if(m_pEquipmentTorso == NULL)
      {
        m_pEquipmentTorso = m_pItemInCursor;
        m_pItemInCursor = NULL;
      }
      break;

    case LEFTHAND:
      if(m_pEquipmentLeftHand == NULL)
      {
        m_pEquipmentLeftHand = m_pItemInCursor;
        m_pItemInCursor = NULL;
      }
      break;

    case RIGHTHAND:
      if(m_pEquipmentRightHand == NULL)
      {
        m_pEquipmentRightHand = m_pItemInCursor;
        m_pItemInCursor = NULL;
      }
      break;
    }
  }

  
}

/************************************************************/

void Inventory::vPickUpItem(
  int iMousePosX,
  int iMousePosY
)
{
  int
    iSelectedSlot = iSlotClicked(iMousePosX, iMousePosY);

  // If inside inventory, check if we are to pick up or drop an item
  if(boInsideInventory(iMousePosX, iMousePosY) && m_slotItems[iSelectedSlot] != NULL)
  {
    // Set current item in cursor
    m_pItemInCursor = m_slotItems[iSelectedSlot];
    m_slotItems[iSelectedSlot] = NULL;
  }
  else if(boInsideEquipment(iMousePosX, iMousePosY))
  {
    switch(equipmentSlotClicked(iMousePosX, iMousePosY))
    {
    case HEAD:
      m_pItemInCursor = m_pEquipmentHead;
      m_pEquipmentHead = NULL;
      break;

    case TORSO:
      m_pItemInCursor = m_pEquipmentTorso;
      m_pEquipmentTorso = NULL;
      break;

    case LEFTHAND:
      m_pItemInCursor = m_pEquipmentLeftHand;
      m_pEquipmentLeftHand = NULL;
      break;

    case RIGHTHAND:
      m_pItemInCursor = m_pEquipmentRightHand;
      m_pEquipmentRightHand = NULL;
      break;
    }
  }

  
}

/************************************************************/

Item *Inventory::pHandleClick(
  int iMousePosX,
  int iMousePosY
)
{
  if(m_pItemInCursor == NULL)                         // Pick up
    vPickUpItem(iMousePosX, iMousePosY);
  else if(!boInsideInventory(iMousePosX, iMousePosY) && !boInsideEquipment(iMousePosX, iMousePosY)) // Drop on the ground
  {
    Item
      *pItem = m_pItemInCursor;
    m_pItemInCursor = NULL;
    return pItem;
  }
  else
    vDropIntoSlot(iMousePosX, iMousePosY);            // Drop into slot (char or inventory)

  return NULL;
}

/************************************************************/

bool Inventory::boHandleInventory(
  int iMousePosX,
  int iMousePosY
) const
{
  // If inside inventory, check if we are to pick up or drop an item
  if( boInsideInventory(iMousePosX, iMousePosY) || boInsideEquipment(iMousePosX, iMousePosY) || m_pItemInCursor != NULL )
    return true;

  return false;
}

/************************************************************/

bool Inventory::boInsideInventory(
  int iMousePosX,
  int iMousePosY
) const
{
  // If inside inventory, check if we are to pick up or drop an item
  if( iMousePosX >= m_pos[X] && iMousePosX <= m_pos[X] + 256 &&
      iMousePosY >= m_pos[Y] + 256 && iMousePosY <= m_pos[Y] + 512
    )
  {
    return true;
  }

  return false;
}

/************************************************************/

bool Inventory::boInsideEquipment(
  int iMousePosX,
  int iMousePosY
) const
{
  if( iMousePosX >= m_pos[X] && iMousePosX <= m_pos[X] + 256 &&
      iMousePosY >= m_pos[Y] && iMousePosY <= m_pos[Y] + 256
    )
  {
    return true;
  }

  return false;
}

/************************************************************/

void Inventory::vDraw(
  int iMousePosX,
  int iMousePosY
) const
{
  glPushMatrix();
  glLoadIdentity();

  // Draw inventory
  glBindTexture(GL_TEXTURE_2D, m_pTexture->iTexIDGet()); // Select Our Texture

  glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(m_pos[X], m_pos[Y], 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(m_pos[X], m_pos[Y] + 512.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(m_pos[X] + 256.0f, m_pos[Y] + 512.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(m_pos[X] + 256.0f, m_pos[Y], 0.0f);

  glEnd();

  int
    iRow = -1,
    iCol;

  // Draw all item icons in the inventory
  for(unsigned int i = 0; i < m_slotItems.size(); i++)
  {
    if(i % 4 == 0)
    {
      ++iRow;
      iCol = 0;
    }

    glLoadIdentity();
    glTranslatef(m_pos[X] + iCol * 64, m_pos[Y] + iRow * 64 + 256, 0);

    if(m_slotItems[i] != NULL)
      m_slotItems[i]->vDrawIcon();

    ++iCol;
  }

  // Draw equipped items
  if(m_pEquipmentHead != NULL)
  {
    glLoadIdentity();
    glTranslatef(m_pos[X] + 96, m_pos[Y] + 25, 0);

    m_pEquipmentHead->vDrawIcon();
  }
  if(m_pEquipmentTorso != NULL)
  {
    glLoadIdentity();
    glTranslatef(m_pos[X] + 96, m_pos[Y] + 103, 0);

    m_pEquipmentTorso->vDrawIcon();
  }
  if(m_pEquipmentRightHand != NULL)
  {
    glLoadIdentity();
    glTranslatef(m_pos[X] + 20, m_pos[Y] + 118, 0);

    m_pEquipmentRightHand->vDrawIcon();
  }
  if(m_pEquipmentLeftHand != NULL)
  {
    glLoadIdentity();
    glTranslatef(m_pos[X] + 172, m_pos[Y] + 118, 0);

    m_pEquipmentLeftHand->vDrawIcon();
  }

  // Draw the item in the cursor, if any
  if(m_pItemInCursor != NULL)
  {
    glLoadIdentity();
    glTranslatef((GLfloat)iMousePosX - 32, (GLfloat)iMousePosY - 32, 0);

    m_pItemInCursor->vDrawIcon();

  }

  glPopMatrix();
}

/************************************************************/

int Inventory::iSlotClicked(
  int iMousePosX,
  int iMousePosY
) const
{
  int
    iSelectedRow = 1,
    iSelectedColumn = 1,
    iSelectedSlot = 0;

  // Column
  for(int i = 64; i <= 256; i += 64, ++iSelectedColumn)
    if(iMousePosX <= m_pos[X] + i)
      break;

  // Row
  for(int i = 64 + 256; i <= 512; i += 64, ++iSelectedRow)
    if(iMousePosY <= m_pos[Y] + i)
      break;

  return ((iSelectedRow - 1) * 4 + iSelectedColumn) - 1;
}

/************************************************************/

EquipmentSlot Inventory::equipmentSlotClicked(
  int iMousePosX,
  int iMousePosY
) const
{
  if( iMousePosX >= m_pos[X] + 96 && iMousePosX <= m_pos[X] + 160 &&
      iMousePosY >= m_pos[Y] + 25 && iMousePosY <= m_pos[Y] + 89
    )       // Head
  {
    return HEAD;
  }
  else if( iMousePosX >= m_pos[X] + 96 && iMousePosX <= m_pos[X] + 160 &&
           iMousePosY >= m_pos[Y] + 103 && iMousePosY <= m_pos[Y] + 231
         )  // Torso
  {
    return TORSO;
  }
  else if( iMousePosX >= m_pos[X] + 20 && iMousePosX <= m_pos[X] + 84 &&
           iMousePosY >= m_pos[Y] + 118 && iMousePosY <= m_pos[Y] + 182
         )  // Right hand
  {
    return RIGHTHAND;
  }
  else if( iMousePosX >= m_pos[X] + 172 && iMousePosX <= m_pos[X] + 236 &&
           iMousePosY >= m_pos[Y] + 118 && iMousePosY <= m_pos[Y] + 182
         )  // Left hand
  {
    return LEFTHAND;
  }

  return OUTSIDE;
}