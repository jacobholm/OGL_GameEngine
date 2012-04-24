/********** Includes ****************************************/

#include "Node.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

list<Node*>
  Node::s_listNodes;

/************************************************************/

Node::Node(
)
{
  m_pParent = NULL;
  s_listNodes.push_back(this);  // Add this node to the list of all nod
}

/************************************************************/

Node::~Node(
)
{
  s_listNodes.remove(this);
}

/************************************************************/

void Node::vSetParent(
  Node *pParent
)
/*
  Purpose: Set our parent
  Written: 29 Aug 2010: JH
*/
{
  if(pParent == NULL && m_pParent != NULL)  // No parent was passed and we also have a current parent(meaning we want to "unparent" this node)
  {
    m_pParent->m_listChildren.remove(this); // Remove ourselves from our parent
    m_pParent = NULL; // We no longer have a parent
  }
  else if(pParent->pGetParent() != this)  // Make sure the parent passed to us does not have THIS node as parent
  {
    m_pParent = pParent;
    m_pParent->m_listChildren.push_back(this);  // Add ourselves as a child to our new parent
  }
}

/************************************************************/

Node* Node::pGetParent(
)
{
  return m_pParent;
}

/************************************************************/

list<Node*>& Node::getListChildren(
)
{
  return m_listChildren;
}

/************************************************************/

list<Node*>& Node::getListNodes(
)
{
  return s_listNodes;
}