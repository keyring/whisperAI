/****************************************************************************
 *
 *    GraphNode.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 *
 ***************************************************************************/

#ifndef __GRAPHNODE_H__
#define __GRAPHNODE_H__

#include <list>
#include <ostream>
#include <fstream>

#include "Vector2D.h"

enum {
  INVALID_NODE_INDEX = -1
};

class GraphNode{

 protected:
  int m_index;

 public:
 GraphNode(): m_index(INVALID_NODE_INDEX) {}
 GraphNode(int index): m_index(index) {}
  GraphNode(std::ifstream &stream) { char buffer[50]; stream >> buffer >>m_index; }

  virtual ~GraphNode(){}

  int GetIndex() const { return m_index; }
  void SetIndex(int value){ m_index = value; }

  friend std::ostream &operator<<(std::ostream &os, const GraphNode &n){
    os << "Index: " << n.m_index << std::endl;
    return os;
  }
};

template <class extra_info = void*>
  class NavGraphNode : public GraphNode{

 protected:
 Vector2D m_position;
 extra_info m_extraInfo;

 public:
 NavGraphNode(): m_extraInfo(extra_info()) {}
 NavGraphNode( int index, Vector2D pos ): GraphNode(index), m_position(pos), m_extraInfo(extra_info()) {}

 NavGraphNode(std::ifstream &stream) : m_extraInfo(extra_info()){
   char buffer[50];
   stream >> buffer >> m_index >> buffer >>m_position.x >> buffer >>m_position.y;
 }

 virtual ~NavGraphNode() {}

 Vector2D GetPosition() const { return m_position; }
 void SetPosition(Vector2D value) { m_position = value; }

 extra_info GetExtraInfo() const { return m_extraInfo; }
 void SetExtraInfo(extra_info value){ m_extraInfo = value; }

 friend std::ostream &operator<<(std::ostream &os, const NavGraphNode &n){
   os << "Index: " << n.m_index << "PosX: " << n.m_position.x << "PosY: " << n.m_position.y << std::endl;
   return os;
 }
};

#endif	/* __GRAPHNODE_H__ */
