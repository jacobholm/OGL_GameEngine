/*
  Written: 03 Sep 2011: JH
  Comment: 
*/

#ifndef INVENTORY_H
#define INVENTORY_H

/********** Includes ****************************************/

/********** Local Defines ***********************************/

/************************************************************/

enum EquipmentSlot;

class Inventory
/*
  Purpose: 
  Written: 03 Sep 2011: JH
*/
{

//---------- Member Variables --------------------------------

  Point
    m_pos;
  Texture
    *m_pTexture;
  int
    m_iSlots;
  std::vector<Item*>
    m_slotItems;
  Item
    *m_pItemInCursor, // The picked up item currently in cursor, if any
    *m_pEquipmentHead,
    *m_pEquipmentTorso,
    *m_pEquipmentRightHand,
    *m_pEquipmentLeftHand;

//---------- Ctor/Dtor ---------------------------------------

public:

  Inventory(
  );

  ~Inventory(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  Item *pHandleClick( // Returns false if click was not inside inventory
    int iMousePosX,
    int iMousePosY
  );

  //----------------------------------------------------------

  void vDraw(
    int iMousePosX, // So that we know where to draw the picked up item in the cursor, if any
    int iMousePosY
  ) const;

  //----------------------------------------------------------

  void vAddItem(
    Item *pItem
  )
  {
    for(unsigned int i = 0; i < m_slotItems.size(); i++)
      if(m_slotItems[i] == NULL)
      {
        pItem->vPosSet(Point(0, 0, 0));
        m_slotItems[i] = pItem;
        break;
      }
  }

  //----------------------------------------------------------

  bool boHandleInventory(
    int iMousePosX,
    int iMousePosY
  ) const;

//---------- Private Functions -------------------------------

private:

  void vDropIntoSlot(
    int iMousePosX,
    int iMousePosY
  );

  //----------------------------------------------------------

  void vPickUpItem(
    int iMousePosX,
    int iMousePosY
  );

  //----------------------------------------------------------

  bool boInsideInventory(
    int iMousePosX,
    int iMousePosY
  ) const;

  //----------------------------------------------------------

  bool boInsideEquipment(
    int iMousePosX,
    int iMousePosY
  ) const;

  //----------------------------------------------------------

  int iSlotClicked(
    int iMousePosX,
    int iMousePosY
  ) const;

  //----------------------------------------------------------

  EquipmentSlot equipmentSlotClicked(
    int iMousePosX,
    int iMousePosY
  ) const;

};

#endif