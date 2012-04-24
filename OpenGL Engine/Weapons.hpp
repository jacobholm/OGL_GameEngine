/*
  Written: 04 Aug 2011: JH
  Comment: Ranged and melee weapon classes
*/

#ifndef WEAPONS_H
#define WEAPONS_H

/********** Includes ****************************************/

/********** Local Defines ***********************************/

/************************************************************/

class Weapon : public Item
/*
  Purpose: Abstract class for ranged and melee
  Written: 04 Aug 2011: JH
*/
{

//---------- Member Variables --------------------------------

protected:  // Have to be protected for derived classes to be able to access

  float
    m_fDamage,
    m_fSpeed,
    m_fRange;

//---------- Ctor/Dtor ---------------------------------------

public:

  Weapon(
    float fDamage,
    float fSpeed,
    float fRange,
    Model *pModel,
    std::string sName,
    Point pos,
    Texture *pIcon
  ) : Item(sName, pos, pModel, 100.0f, 100.0f, 5, pIcon), m_fDamage(fDamage), m_fSpeed(fSpeed), m_fRange(fRange)
  {

  }

//---------- Set/Get Member Variables ------------------------

   virtual float fSpeed(
   )
   {
     return m_fSpeed;
   }

   //----------------------------------------------------------

   virtual void vNameSet(
     std::string sName
   )
   {
     Item::vNameSet(sName);
   }

   virtual std::string sName(
   )
   {
     return Item::sName();
   }

   //----------------------------------------------------------

   virtual Model *pModel(
   )
   {
     return Item::pModel();
   }

   //----------------------------------------------------------

   virtual void vPosSet(
     Point pos
   )
   {
     Item::vPosSet(pos);
   }

   virtual Point pos(
   )
   {
     return Item::pos();
   }

   //----------------------------------------------------------

   virtual void vLevelReqSet(
     int iReq
   )
   {
     Item::vLevelReqSet(iReq);
   }

   virtual int iLevelReq(
   )
   {
     return Item::iLevelReq();
   }

   //----------------------------------------------------------

   virtual void vDurabilitySet(
     float fDurability
   )
   {
     Item::vDurabilitySet(fDurability);
   }

   virtual float fDurability(
   )
   {
     return Item::fDurability();
   }

   //----------------------------------------------------------

   virtual void vPriceSet(
     float fPrice
   )
   {
     Item::vPriceSet(fPrice);
   }

   virtual float fPrice(
   )
   {
     return Item::fPrice();
   }

//---------- Public Functions --------------------------------

  virtual Projectile *pAttack(
    Point pos,
    Vector3f targetVector
  ) = 0;

//---------- Private Functions -------------------------------

private:

};

/************************************************************/

class Projectile;

class Ranged : public Weapon
/*
  Purpose: All ranged weapons; bows, guns, grenades (?) etc...
  Written: 04 Aug 2011: JH
*/
{

//---------- Member Variables --------------------------------

  float
    m_fProjectileSpeed;

//---------- Ctor/Dtor ---------------------------------------

public:

  Ranged(
    float fDamage,
    float fSpeed,
    float fRange,
    float fProjectileSpeed,
    Model *pModel = NULL,
    std::string sName = "",
    Point pos = Point(0, 0, 0),
    Texture *pIcon = NULL
  ) : Weapon(fDamage, fSpeed, fRange, pModel, sName, pos, pIcon), m_fProjectileSpeed(fProjectileSpeed)
  {

  }

//---------- Set/Get Member Variables ------------------------

  virtual void vNameSet(
    std::string sName
  ) override
  {
    Weapon::vNameSet(sName);
  }

  virtual std::string sName(
  ) override
  {
    return Weapon::sName();
  }

  //----------------------------------------------------------

  virtual Model *pModel(
  ) override
  {
    return Weapon::pModel();
  }

  //----------------------------------------------------------

  virtual void vPosSet(
    Point pos
  ) override
  {
    Weapon::vPosSet(pos);
  }

  virtual Point pos(
  ) override
  {
    return Weapon::pos();
  }

  //----------------------------------------------------------

  virtual void vLevelReqSet(
    int iReq
  ) override
  {
    Weapon::vLevelReqSet(iReq);
  }

  virtual int iLevelReq(
  ) override
  {
    return Weapon::iLevelReq();
  }

  //----------------------------------------------------------

  virtual void vDurabilitySet(
    float fDurability
  ) override
  {
    Weapon::vDurabilitySet(fDurability);
  }

  virtual float fDurability(
  ) override
  {
    return Weapon::fDurability();
  }

  //----------------------------------------------------------

  virtual void vPriceSet(
    float fPrice
  ) override
  {
    Weapon::vPriceSet(fPrice);
  }

  virtual float fPrice(
  ) override
  {
    return Weapon::fPrice();
  }

//---------- Public Functions --------------------------------

  virtual Projectile *pAttack(
    Point pos,
    Vector3f targetVector
  ) override
  {
    return new Projectile(pos, targetVector * m_fProjectileSpeed, m_fDamage);
  }

  //----------------------------------------------------------

  virtual float fSpeed(
  ) override
  {
    return m_fSpeed;
  }
//---------- Private Functions -------------------------------

private:

};

/************************************************************/

class Melee //: public Weapon
/*
  Purpose: Currently no difference from Weapon class, but its own class because
           there will probably be in the future
  Written: 04 Aug 2011: JH
*/
{

//---------- Member Variables --------------------------------

//---------- Ctor/Dtor ---------------------------------------

public:

//   Melee(
//   )
//   {
// 
//   }
// 
//   ~Melee(
//   )
//   {
// 
//   }

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

//---------- Private Functions -------------------------------

private:

};

#endif