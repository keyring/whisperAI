/****************************************************************************
 *
 *    SparseGraph.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 *
 *    DESC: Graph class using the adjacency list representation.
 ***************************************************************************/

#ifndef __SPARSEGRAPH_H__
#define __SPARSEGRAPH_H__

#pragma warning (disable:4786)

#include <vector>
#include <list>
#include <cassert>
#include <string>
#include <iostream>

#include "Vector2D.h"
#include "Utils.h"


template <class node_type, class edge_type>
  class SparseGraph{

 public:
  typedef edge_type EdgeType;
  typedef node_type NodeType;

  typedef std::vector<node_type> NodeVector;
  typedef std::list<edge_type> EdgeList;
  typedef std::vector<EdgeList> EdgeListVector;

 private:
  NodeVector m_nodes;
  EdgeListVector m_edges;
  bool m_digraph;
  int m_nextNodeIndex;

  bool IsUniqueEdge( int src, int dst ) const;
  void CullInvalidEdges();

 public:
 SparseGraph(bool digraph) : m_nextNodeIndex(0), m_digraph(digraph) {}

  const NodeType &GetNode(int index) const;
  NodeType &GetNode(int index);

  const EdgeType &GetEdge(int src, int dst) const;
  EdgeType &GetEdge(int src, int dst);

  int GetNextFreeNodeIndex() const { return m_nextNodeIndex; }
  int AddNode(node_type node);
  void RemoveNode(int node);	/* remove by seting its index to invalidIndex */





#endif	/* __SPARSEGRAPH_H__ */
