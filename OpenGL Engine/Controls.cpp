//********** Includes ****************************************/

#include <list>
#include <vector>

#include "GLEngine.hpp"
#include "Controls.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

std::list<Control*>
  Control::s_controlsVec;

/************************************************************/

Control *pAddControl(
  Control *pControl
)
/*
  Written: 20 Mar. 2010: JH
  Purpose: Takes in a new control and positions it vertically based on the previous one
*/
{
  static int
    s_iLastX = 5,
    s_iLastY = 25;

  pControl->vPositionSet(s_iLastX, s_iLastY);
  s_iLastY += pControl->iHeightGet() +5;

  return pControl;
}

/************************************************************/

Control::Control(
  int iPosX,
  int iPosY,
  int iWidth,
  int iHeight
)
/*
  Written: 20 Mar. 2010: JH
  Purpose: 
*/
{
  s_controlsVec.push_back(this);  // Add this object to the list

  m_iPosX = iPosX;
  m_iPosY = iPosY;
  m_iWidth = iWidth;
  m_iHeight = iHeight;
}

Control::~Control(
)
/*
  Written: 20 Mar. 2010: JH
  Purpose: 
*/
{
  s_controlsVec.remove(this); // Remove this object from the list
}

/************************************************************/

bool Control::boUpdateControls(
  MouseState &state
)
/*
  Written: 20 Mar. 2010: JH
  Purpose: Check if the mouse is over/inside a control
*/
{
  m_boInside = false;

  if(state.iPosX >= m_iPosX && state.iPosX <= m_iPosX + m_iWidth &&
     state.iPosY >= m_iPosY && state.iPosY <= m_iPosY + m_iHeight)
     m_boInside = true;

  return false; // WTF?? What is the point in this returning bool??
}

/************************************************************/
/************************************************************/
/************************************************************/

Button::Button(
  std::string sLabel,
  int iPosX,
  int iPosY,
  int iWidth,
  int iHeight
) : Control(iPosX, iPosY, iWidth, iHeight)
/*
  Written: 23 Mar. 2010: JH
  Purpose: 
*/
{
  m_sLabel = sLabel;
  m_boDepressed = false;
}

/************************************************************/

bool Button::boUpdateControls(
  MouseState &state
)
/*
  Written: 24 Mar. 2010: JH
  Purpose: 
*/
{
  Control::boUpdateControls(state); // Call parent to decide if the mouse is inside the button or not

  if(m_boInside)
  {
    if(state.iLeftBtnDown)
      m_boDepressed = true;
    else if(m_boDepressed)
    {
      m_boDepressed = false;
      return true;  // Event happened
    }
  }

  return false;
}

/************************************************************/

void Button::vDrawControl(
)
/*
  Written: 24 Mar. 2010: JH
  Purpose: 
*/
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_TEXTURE_2D);

  // Draw button
  glColor4f(0.7f, 0.7f, 0.7f, 0.8f);
  glBegin(GL_QUADS);
    glVertex2d(m_iPosX, m_iPosY);
    glVertex2d(m_iPosX + m_iWidth, m_iPosY);
    glVertex2d(m_iPosX + m_iWidth, m_iPosY + m_iHeight);
    glVertex2d(m_iPosX, m_iPosY + m_iHeight);
  glEnd();

  // Draw button outline
  if(m_boInside)  // If we are inside the button we want a thick line and a low transparency
  {
    glColor4f(0.7f, 0.7f, 0.7f, 0.8f);
    glLineWidth(2.0f);
  }
  else            // If we are outside the button we want a thin line and a high transparency
  {
    glColor4f(0.7f, 0.7f, 0.7f, 0.5f);
    glLineWidth(1.0f);
  }

  glBegin(GL_LINE_STRIP);
    glVertex2d(m_iPosX, m_iPosY);
    glVertex2d(m_iPosX + m_iWidth, m_iPosY);
    glVertex2d(m_iPosX + m_iWidth, m_iPosY + m_iHeight);
    glVertex2d(m_iPosX, m_iPosY + m_iHeight);
    glVertex2d(m_iPosX, m_iPosY);
  glEnd();

  // Draw the button text
  int // Text position
    iTextX = m_iPosX + (m_iWidth - Engine->iTextWidthGet(m_sLabel.data())) / 2 ,
    iTextY = m_iPosY + (m_iHeight - Engine->iTextHeightGet()) / 2;

  if(m_boInside && m_boDepressed) // Move text when the button is depressed to indicate it is being pressed
  {
    iTextX += 2;
    iTextY += 2;
  }

  Engine->vDrawText(iTextX, iTextY, m_sLabel.data());
}

/************************************************************/

std::string Button::sTypeGet(
)
/*
  Written: 24 Mar. 2010: JH
  Purpose: 
*/
{
  return "Standard Button";
}

/************************************************************/
/************************************************************/
/************************************************************/

ListBox::ListBox(
  int iPosX,
  int iPosY,
  int iWidth,
  int iHeight
) : Control(iPosX, iPosY, iWidth, iHeight)
/*
  Written: 31 May. 2010: JH
  Purpose: 
*/
{
  m_iCurrItem = 0;
  m_iItemHeight = 18;
}

ListBox::~ListBox(
)
{
}

/************************************************************/

void ListBox::vAddItem(
  std::string sItem
)
/*
  Written: 31 May. 2010: JH
  Purpose: 
*/
{
  m_itemsVec.push_back(sItem);
}

/************************************************************/

void ListBox::vRemoveItem(
  int iIndex
)
/*
  Written: 31 May. 2010: JH
  Purpose: 
*/
{
  int
    iCounter = 0;

  for(std::vector<std::string>::iterator it = m_itemsVec.begin(); it != m_itemsVec.end(); it++)
    if(iCounter == m_iCurrItem)
    {
      m_itemsVec.erase(it);
      break;
    }
    else
      iCounter++;

  // If the very last item was removed, m_iCurrItem will be pointing to an invalid index
  if(m_iCurrItem >= (int)m_itemsVec.size())
    m_iCurrItem = m_itemsVec.size() - 1;
}

/************************************************************/

void ListBox::vSetCurrent(
  int iIndex
)
/*
  Written: 31 May. 2010: JH
  Purpose: 
*/
{
  m_iCurrItem = iIndex;
}

/************************************************************/

int ListBox::iGetCurrent(
)
/*
  Written: 31 May. 2010: JH
  Purpose: 
*/
{
  return m_iCurrItem;
}

/************************************************************/

int ListBox::iGetCount(
)
/*
  Written: 31 May. 2010: JH
  Purpose: 
*/
{
  return m_itemsVec.size();
}

/************************************************************/

bool ListBox::boUpdateControls(
  MouseState &state
)
/*
  Written: 31 May. 2010: JH
  Purpose: 
*/
{
  Control::boUpdateControls(state); // Let parent set up state

  if(m_boInside && state.iLeftBtnDown)  // We have clicked on something inside the listbox
  {
    int
      iSelectedIndex = (state.iPosY - m_iPosY) / m_iItemHeight;

    if(iSelectedIndex >= 0 && iSelectedIndex < (int)m_itemsVec.size()) // Did we click on an item or an empty space in the list
    {
      m_iCurrItem = iSelectedIndex;
      return true;
    }
  }

  return false;
}

/************************************************************/

void ListBox::vDrawControl(
)
/*
  Written: 31 May. 2010: JH
  Purpose: 
*/
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_TEXTURE_2D);

  // Draw button
  glColor4f(0.7f, 0.7f, 0.7f, 0.8f);
  glBegin(GL_QUADS);
    glVertex2d(m_iPosX, m_iPosY);
    glVertex2d(m_iPosX + m_iWidth, m_iPosY);
    glVertex2d(m_iPosX + m_iWidth, m_iPosY + m_iHeight);
    glVertex2d(m_iPosX, m_iPosY + m_iHeight);
  glEnd();

  // Draw button outline
  if(m_boInside)  // If we are inside the button we want a thick line and a low transparency
  {
    glColor4f(0.7f, 0.7f, 0.7f, 0.8f);
    glLineWidth(2.0f);
  }
  else            // If we are outside the button we want a thin line and a high transparency
  {
    glColor4f(0.7f, 0.7f, 0.7f, 0.5f);
    glLineWidth(1.0f);
  }

  glBegin(GL_LINE_STRIP);
    glVertex2d(m_iPosX, m_iPosY);
    glVertex2d(m_iPosX + m_iWidth, m_iPosY);
    glVertex2d(m_iPosX + m_iWidth, m_iPosY + m_iHeight);
    glVertex2d(m_iPosX, m_iPosY + m_iHeight);
    glVertex2d(m_iPosX, m_iPosY);
  glEnd();

  // Highlight selected index
  if(m_iCurrItem >= 0)
  {
    glColor4f(0.3f, 0.3f, 0.3f, 0.5f);

    int
      iIndexPosY = m_iPosY + m_iCurrItem * m_iItemHeight;

    glBegin(GL_QUADS);
      glVertex2d(m_iPosX, iIndexPosY);
      glVertex2d(m_iPosX + m_iWidth, iIndexPosY);
      glVertex2d(m_iPosX + m_iWidth, iIndexPosY + m_iItemHeight);
      glVertex2d(m_iPosX, iIndexPosY + m_iItemHeight);
    glEnd();
  }

  // Draw item text
  glColor4f(0.7f, 0.7f, 0.7f, 1.0f);

  for(int i = 0; i < (int)m_itemsVec.size(); i++)
    Engine->vDrawText(m_iPosX + 2, m_iPosY + 2 + i * m_iItemHeight, m_itemsVec[i].data());
}

/************************************************************/

std::string ListBox::sTypeGet(
)
/*
  Written: 31 May. 2010: JH
  Purpose: 
*/
{
  return "Listbox";
}

/************************************************************/
/************************************************************/
/************************************************************/

Slider::Slider(
  std::string sLabel,
  float fMinValue,
  float fMaxValue,
  int iPosX,
  int iPosY,
  int iWidth,
  int iHeight
) : Control(iPosX, iPosY, iWidth, iHeight)
/*
  Purpose: 
  Written: 06 Jun 2010: JH
*/
{
  m_fCurrentValue = NULL;
  m_sLabel = sLabel;
  m_fMinValue = fMinValue;
  m_fMaxValue = fMaxValue;
  m_iTickSize = 5;
}

Slider::~Slider(
)
/*
  Purpose: 
  Written: 06 Jun 2010: JH
*/
{

}

/************************************************************/

void Slider::vSetValue(
  float *fValue
)
/*
  Purpose: 
  Written: 06 Jun 2010: JH
*/
{
  m_fCurrentValue = fValue;

  // If the pointer parameter passed to us was not NULL use it as default value
  if(m_fCurrentValue != NULL)
    m_fDefaultValue = *m_fCurrentValue;
}

float Slider::fGetValue(
)
{
	return *m_fCurrentValue;
}

/************************************************************/

bool Slider::boUpdateControls(
  MouseState &state
)
/*
  Purpose: 
  Written: 06 Jun 2010: JH
*/
{
  Control::boUpdateControls(state);

  if(m_boInside)
  {
    if(state.iLeftBtnDown)
      m_boDragging = true;

    if(state.iRightBtnDown)
      *m_fCurrentValue = m_fDefaultValue;
  }

  if(!state.iLeftBtnDown)
    m_boDragging = false;

  if(m_boDragging)
    *m_fCurrentValue = (state.iPosX - m_iPosX) / (float)m_iWidth * (m_fMaxValue - m_fMinValue) + m_fMinValue;

  // Don't let slider go outside control boundaries
  if(*m_fCurrentValue > m_fMaxValue)
    *m_fCurrentValue = m_fMaxValue;

  if(*m_fCurrentValue < m_fMinValue)
    *m_fCurrentValue = m_fMinValue;

  return m_boDragging;
}

/************************************************************/

void Slider::vDrawControl(
)
/*
  Purpose: 
  Written: 06 Jun 2010: JH
*/
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_TEXTURE_2D);

  // Draw control
  glColor4f(0.7f, 0.7f, 0.7f, 0.8f);
  glBegin(GL_QUADS);
  glVertex2d(m_iPosX, m_iPosY);
  glVertex2d(m_iPosX + m_iWidth, m_iPosY);
  glVertex2d(m_iPosX + m_iWidth, m_iPosY + m_iHeight);
  glVertex2d(m_iPosX, m_iPosY + m_iHeight);
  glEnd();

  // Draw control outline
  if(m_boInside)  // If we are inside the control we want a thick line and a low transparency
  {
    glColor4f(0.7f, 0.7f, 0.7f, 0.8f);
    glLineWidth(2.0f);
  }
  else            // If we are outside the control we want a thin line and a high transparency
  {
    glColor4f(0.7f, 0.7f, 0.7f, 0.5f);
    glLineWidth(1.0f);
  }

  glBegin(GL_LINE_STRIP);
  glVertex2d(m_iPosX, m_iPosY);
  glVertex2d(m_iPosX + m_iWidth, m_iPosY);
  glVertex2d(m_iPosX + m_iWidth, m_iPosY + m_iHeight);
  glVertex2d(m_iPosX, m_iPosY + m_iHeight);
  glVertex2d(m_iPosX, m_iPosY);
  glEnd();

  int
    iCurrX = (int)((*m_fCurrentValue - m_fMinValue) / (m_fMaxValue - m_fMinValue) * (m_iWidth - m_iTickSize) + m_iPosX);

  // Draw slider tick
  glColor4f(0.3f, 0.3f, 1.0f, 0.5f);
  glBegin(GL_QUADS);
  glVertex2d(iCurrX, m_iPosY);
  glVertex2d(iCurrX + m_iTickSize, m_iPosY);
  glVertex2d(iCurrX + m_iTickSize, m_iPosY + m_iHeight);
  glVertex2d(iCurrX, m_iPosY + m_iHeight);
  glEnd();

  // Draw text
  glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
  Engine->vDrawText(m_iPosX + 2, m_iPosY + 2, m_sLabel.data());
}

/************************************************************/

std::string Slider::sTypeGet(
)
/*
  Purpose: 
  Written: 06 Jun 2010: JH
*/
{
  return "Slider";
}