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

enum{
  INVALID_NODE_INDEX = -1;
};

class GraphEdge{

 protected:
  int m_src, m_dst;
  double m_cost;

 public:
 GraphEdge( int src, int dst, double cost ) : m_src(src), m_dst(dst), m_cost(cost) {}
 GraphEdge(int src, int dst ):m_src(src), m_dst(dst), m_cost(1.0) {}
 GraphEdge():m_src(INVALID_NODE_INDEX), m_dst(INVALID_NODE_INDEX), m_cost(1.0){}

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

    return ( g.m_src == this.m_src &&
	     g.m_dst == this.m_dst &&
	     g.m_cost == this.m_cost );
  }

  bool operator!=(const GraphEdge &g){

    return !(*this == g);
  }

  friend std::ostream &operator<<(std::ostream &os, const GraphEdge &g){
    os << "m_src: " << m_src << "m_dst: " << m_dst << "m_cost: " << m_cost << std::endl;
    return os;
  }
};


#endif /* __GRAPHEDGE_H__ */
