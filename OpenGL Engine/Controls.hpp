/*
  Written: 06 Jun 2010: JH
  Comment: A grouping of all the control classes
*/

#ifndef CONTROLS_H
#define CONTROLS_H

/********** Includes ****************************************/

//#include "GLEngine.hpp"
//#include <string>

/********** Local Defines ***********************************/

/************************************************************/

struct MouseState
{
  int
    iLeftBtnDown,
    iMiddleBtnDown,
    iRightBtnDown,
    iPosX,
    iPosY;

  MouseState(
  )
  {
    iLeftBtnDown    = 0;
    iMiddleBtnDown  = 0;
    iRightBtnDown   = 0;
    iPosX = 0;
    iPosY = 0;
  }
};

class Control
/*
  Purpose: Abstract class from which to create controls
  Written: 20 Mar. 2010: JH
*/
{

//---------- Member Variables --------------------------------

  static std::list<Control*>
    s_controlsVec;

protected:
  
  bool
    m_boInside; // Are we currently "inside"/on top of the control
  int
    m_iPosX,
    m_iPosY,
    m_iWidth,
    m_iHeight;

//---------- Ctor/Dtor ---------------------------------------

public:

  Control(
    int iPosX,
    int iPosY,
    int iWidth,
    int iHeight
  );

  virtual ~Control( // Virtual so that constructors of children are called in the right order
  );

//---------- Set/Get Member Variables ------------------------

  void vPositionSet(
    int iPosX,
    int iPosY
  )
  {
    m_iPosX = iPosX;
    m_iPosY = iPosY;
  }

  //----------------------------------------------------------

  void vSizeSet(
    int iWidth,
    int iHeight
  )
  {
    m_iWidth = iWidth;
    m_iHeight = iHeight;
  }

  //----------------------------------------------------------

  int iWidthGet(
  )
  {
    return m_iWidth;
  }

  //----------------------------------------------------------

  int iHeightGet(
  )
  {
    return m_iHeight;
  }

//---------- Public Functions --------------------------------

  static std::list<Control*> &s_controlsListGet(
  )
  {
    return s_controlsVec;
  }

  //----------------------------------------------------------

  virtual bool boUpdateControls(  // Check for events, e.g. if we press a button
    MouseState &state
  );

  //----------------------------------------------------------

  virtual void vDrawControl( // OpenGL calls to draw the control
  ) = 0;

  //----------------------------------------------------------

  virtual std::string sTypeGet(  // The type of control e.g. "Button", "Slider" etc..
  ) = 0;

//---------- Private Functions -------------------------------

private:

};

Control *pAddControl(
  Control *pControl
);

/************************************************************/

class Button  : public Control
/*
  Written: 23 Mar. 2010: JH
  Purpose: 
*/
{

//---------- Member Variables --------------------------------

protected:

  bool
    m_boDepressed;  // Is the button currently pressed down?
  std::string
    m_sLabel;       // The button label

//---------- Ctor/Dtor ---------------------------------------

public:

  Button(
    std::string sLabel,
    int iPosX,
    int iPosY,
    int iWidth,
    int iHeight
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  virtual bool boUpdateControls(  // See Control.hpp
    MouseState &state
  );

  //----------------------------------------------------------

  virtual void vDrawControl( // See Control.hpp
  );

  //----------------------------------------------------------

  virtual std::string sTypeGet(  // See Control.hpp
  );

//---------- Private Functions -------------------------------

private:

};

/************************************************************/

class ListBox : public Control
/*
  Written: 5 Apr. 2010: JH
  Purpose: A typical listbox with selectable items
*/
{

//---------- Member Variables --------------------------------

  int
    m_iCurrItem,    // The currently selected item(index)
    m_iItemHeight;  // The height of the items in the list
  std::vector<std::string>
    m_itemsVec;     // A list of all the items in the listbox

//---------- Ctor/Dtor ---------------------------------------

public:

  ListBox(
    int iPosX,
    int iPosY,
    int iWidth,
    int iHeight
  );

  ~ListBox(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  void vAddItem(
    std::string sItem
  );

  //----------------------------------------------------------

  void vRemoveItem(
    int iIndex
  );

  //----------------------------------------------------------

  void vSetCurrent(  // Set the currently selected item
    int iIndex
  );

  //----------------------------------------------------------

  int iGetCurrent(  // Get the currently selected item
  );

  //----------------------------------------------------------

  int iGetCount(  // The number of items in the list
  );

  //----------------------------------------------------------

  virtual bool boUpdateControls(  // See Control.hpp
    MouseState &state
  );

  //----------------------------------------------------------

  virtual void vDrawControl( // See Control.hpp
  );

  //----------------------------------------------------------

  virtual std::string sTypeGet(  // See Control.hpp
  );

//---------- Private Functions -------------------------------

private:

};

/************************************************************/

class Slider : public Control
/*
  Purpose: 
  Written: 06 Jun 2010: JH
*/
{

//---------- Member Variables --------------------------------

  float
    m_fDefaultValue,
    m_fMinValue,
    m_fMaxValue,
    *m_fCurrentValue; // Pointer to get direct access to variable from the outside
  int
    m_iTickSize;
  std::string
    m_sLabel;
  bool
    m_boDragging;     // Are we currently dragging the slider

  
//---------- Ctor/Dtor ---------------------------------------

public:

  Slider(
    std::string sLabel,    // Label for slider
    float fMinValue,  // Minimum value for slider
    float fMaxValue,  // Maximum value for slider
    int iPosX,
    int iPosY,
    int iWidth,
    int iHeight
  );

  ~Slider(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  void vSetValue(
    float *fValue
  );

	float fGetValue(
	);

  //----------------------------------------------------------

  bool boUpdateControls(  // See Control
    MouseState &state
  );

  //----------------------------------------------------------

  void vDrawControl( // See Control
  );

  //----------------------------------------------------------

  std::string sTypeGet(  // See Control
  );

//---------- Private Functions -------------------------------

private:

};

#endif