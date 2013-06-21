/****************************************************************************
 *
 *    GraphEdge.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 *
 ***************************************************************************/

#ifndef __GRAPHEDGE_H__
#define __GRAPHEDGE_H__

#include <ostream>
#include <fstream>

#include "NodeTypeEnum.h"

class GraphEdge{

 protected:
  int m_src, m_dst;
  double m_cost;

 public:
 GraphEdge( int src, int dst, double cost ): m_src(src), m_dst(dst), m_cost(cost) {}
 GraphEdge(int src, int dst ):m_src(src), m_dst(dst), m_cost(1.0) {}
 GraphEdge():m_src(INVALID_NODE_INDEX), m_dst(INVALID_NODE_INDEX), m_cost(1.0) {}

  GraphEdge(std::ifstream &stream){
    char buffer[50];
    stream >> buffer >> m_src >> buffer >> m_dst >> buffer >> m_cost;
  }

  virtual ~GraphEdge() {}

  int GetSrc() const { return m_src; }
  void SetSrc(int value){ m_src = value; }

  int GetDst() const { return m_dst; }
  void SetDst(int value){ m_dst = value; }

  double GetCost() const { return m_cost; }
  void SetCost(double value){ m_cost = value; }

  bool operator==(const GraphEdge &g){

    return g.m_src == this->m_src &&
	     g.m_dst == this->m_dst &&
	     g.m_cost == this->m_cost;
  }

  bool operator!=(const GraphEdge &g){

    return !(*this == g);
  }

  friend std::ostream &operator<<(std::ostream &os, const GraphEdge &e){
    os << "m_src: " << e.m_src << "m_dst: " << e.m_dst << "m_cost: " << e.m_cost << std::endl;
    return os;
  }
};

class NavGraphEdge : public GraphEdge{

 public:
  enum{
    NORMAL = 0,
    SWIM = 1 << 0,
    CRAWL = 1 << 1,
    CREEP = 1 << 2,
    JUMP = 1 << 3,
    FLY = 1 << 4,
    GRAPPLE = 1 << 5,
    GOES_THROUGH_DOOR = 1 << 6
  };

 protected:
  int m_flags;
  int m_IDofInterEntity;	/* if this edge intersects with an object( such as a door or lift), then this is that object's ID. */

 public:

 NavGraphEdge( int src, int dst, double cost, int flags = 0, int id = -1 ):
  GraphEdge( src, dst, cost ), m_flags(flags), m_IDofInterEntity(id) {}

  NavGraphEdge(std::ifstream &stream){
    char buffer[50];
    stream >> buffer >> m_src >> buffer >> m_dst >> buffer >> m_cost;
    stream >> buffer >> m_flags >> buffer >> m_IDofInterEntity;
  }

  int GetFlags() const { return m_flags; }
  void SetFlags(int value){ m_flags = value; }

  int GetId() const { return m_IDofInterEntity; }
  void SetId(int value){ m_IDofInterEntity = value; }

  friend std::ostream &operator<<(std::ostream &os, const NavGraphEdge &n){
    os << "m_src: " << n.m_src << "m_dst: " << n.m_dst
       << "m_cost: " << n.m_cost << "m_flags: " << n.m_flags
       << "ID: " << n.m_IDofInterEntity << std::endl;

    return os;
  }
};

#endif /* __GRAPHEDGE_H__ */
