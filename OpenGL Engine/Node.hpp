/*
  Written: 29 Aug 2010: JH
  Comment: Scene graph
*/

#ifndef NODE_H
#define NODE_H

/********** Includes ****************************************/

#include <list>

/********** Local Defines ***********************************/

/************************************************************/

using std::list;

class Node
/*
  Purpose: The base class for our scene graph
  Written: 29 Aug 2010: JH
*/
{

//---------- Member Variables --------------------------------

public:

  static list<Node*>
    s_listNodes;  // To keep track of all nodes ever created, easier to draw etc..

protected:

  list<Node*>
    m_listChildren; // All the children of THIS node
  Node
    *m_pParent; // The parent of THIS node

public:

  
//---------- Ctor/Dtor ---------------------------------------

public:

  Node(
  );

  virtual ~Node(  // Virtual since a lot of other classes will inherit from this, so that the correct destructor is called
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

  void vSetParent(
    Node *pParent
  );

  Node *pGetParent(
  );

  //----------------------------------------------------------

  list<Node*> &getListChildren(
  );

  //----------------------------------------------------------

  static list<Node*> &getListNodes(
  );

//---------- Private Functions -------------------------------

private:

};

#endif