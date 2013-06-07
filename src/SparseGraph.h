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
  int AddNode(Nodetype node);
  void RemoveNode(int node);	/* remove by seting its index to invalidIndex */

  void AddEdge(EdgeType edge);
  void RemoveEdge(int src, int dst);
  void SetEdgeCost(int src, int dst, double cost);

  int GetNumNodes() const { return m_nodes.size(); }

  int GetNumActiveNodes() const {
    int count = 0;
    for(unsigned int n = 0; n < m_nodes.size(); ++n)
      if(m_nodes[n].Index() != INVALID_NODE_INDEX)
	++count;
    return count;
  }

  int GetNumEdges() const{
    int tot = 0;
    for(EdgeListVector::const_iterator curEdge = m_edges.begin();
	curEdge != m_edges.end();
	++curEdge){
      tot += curEdge->size();
    }
    return tot;
  }

  bool IsDigraph() const { return m_digraph; }
  bool IsEmpty() const { return m_nodes.empty(); }
  bool IsNodePresent(int nd)const;
  bool IsEdgePresent(int src, int dst) const;

  bool Save(const char *filename) const;
  bool Save(std::ofstream &stream) const;

  bool Load(const char *filename);
  bool Load(std::ifstream &stream);

  void Clear(){
    m_nextNodeIndex = 0;
    m_nodes.clear();
    m_edges.clear();
  }

  void RemoveEdges(){
    for(EdgeListVector::iterator it = m_edges.begin(); it != m_edges.end(); ++it){
      it->clear();
    }
  }

  class EdgeIterator{

  private:
    typename EdgeList::iterator curEdge;
    SparseGraph<node_type, edge_type> &G;
    const int m_nodeIndex;

  public:
  EdgeIterator(SparseGraph<node_type, edge_type> &graph, int node):
    G(graph), m_nodeIndex(node){

      curEdge = G.m_edges[m_nodeIndex].begin();
    }

    EdgeType *begin(){
      curEdge = G.m_edges[m_nodeIndex].begin();
      return &(*curEdge);
    }

    EdgeType *next(){
      ++curEdge;
      if(end())
	return NULL;
      return &(*curEdge);
    }

    bool end(){
      return (curEdge == G.m_edges[m_nodeIndex].end());
    }
  };


#endif	/* __SPARSEGRAPH_H__ */
