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

  friend class EdgeIterator;

  class NodeIterator{

  private:
    typename NodeVector::iterator curNode;
    SparseGraph<node_type, edge_type> &G;

    void GetNextValidNode(typename NodeVector::iterator &it){

      if(curNode == G.m_nodes.end() || it->Index() != INVALID_NODE_INDEX)
	return;
      while((it->Index() == INVALID_NODE_INDEX)){
	++it;
	if(curNode == G.m_nodes.end())
	  break;
      }
    }

  public:
  NodeIterator(SparseGraph<node_type, edge_type> &graph):G(graph){
      curNode = G.m_nodes.begin();
    }

    NodeType *begin(){
      curNode = G.m_nodes.begin();
      GetNextValidNode(curNode);
      return &(*curNode);
    }

    NodeType *next(){
      ++curNode;
      if(end())
	return NULL;
      GetNextValidNode(curNode);
      return &(*curNode);
    }

    bool end(){
      return (curNode == G.m_nodes.end());
    }
  };

  friend class NodeIterator;

};


/* Implement Functions */

template <class node_type, class edge_type>
  bool SparseGraph<node_type, edge_type>::IsNodePresent(int nd) const{

      if((nd >= (int)m_nodes.size() || (m_nodes[nd].Index() == INVALID_NODE_INDEX))){
	return false;
      }
      else
	return true;
    }

    template <class node_type, class edge_type>
  bool SparseGraph<node_type, edge_type>::IsEdgePresent(int src, int dst)const{

      if(IsNodePresent(src) && IsNodePresent(dst)){
	for(EdgeList::const_iterator curEdge = m_edges[src].begin();
	    curEdge != m_edges[src].end();
	    ++curEdge){
	  if(curEdge->GetDst() == dst)
	    return true;
	}
	return false;
      }
      else
	return false;
    }

template <class node_type, class edge_type>
      const NodeType &SparseGraph<node_type, edge_type>::GetNode(int index)const{

  assert((index < (int)m_nodes.size()) && (index >= 0) &&
	 "<SparseGraph::<GetNode>: invalid index");

  return m_nodes[index];
}

template <class node_type, class edge_type>
  NodeType &SparseGraph<node_type, edge_type>::GetNode(int index){

  assert((index < (int)m_nodes.size()) && (index >= 0) &&
	 "<SparseGraph::<GetNode>: invalid index");

  return m_nodes[index];
}

template <class node_type, class edge_type>
  const EdgeType &SparseGraph<node_type, edge_type>::GetEdge(int src, int dst)const{

  assert((src < m_nodes.size()) && (src >= 0) &&
	 m_nodes[src].Index != INVALID_NODE_INDEX &&
	 "<SparseGraph::GetEdge>: invalid 'src' index");
  assert((dst < m_nodes.size()) && (dst >= 0) &&
	 m_nodes[dst].Index != INVALID_NODE_INDEX &&
	 "<SparseGraph::GetEdge>: invalid 'dst' index");

  for(EdgeList::const_iterator curEdge = m_edges[src].begin();
      curEdge != m_edges[src].end();
      ++curEdge){
    if(curEdge->GetDst() == dst)
      return *curEdge;
  }

  assert(0 && "<SparseGraph::GetEdge>: edge does not exist");
}


template <class node_type, class edge_type>
  EdgeType &SparseGraph<node_type, edge_type>::GetEdge(int src, int dst){

  assert((src < m_nodes.size()) && (src >= 0) &&
	 m_nodes[src].Index != INVALID_NODE_INDEX &&
	 "<SparseGraph::GetEdge>: invalid 'src' index");
  assert((dst < m_nodes.size()) && (dst >= 0) &&
	 m_nodes[dst].Index != INVALID_NODE_INDEX &&
	 "<SparseGraph::GetEdge>: invalid 'dst' index");

  for(EdgeList::const_iterator curEdge = m_edges[src].begin();
      curEdge != m_edges[src].end();
      ++curEdge){
    if(curEdge->GetDst() == dst)
      return *curEdge;
  }

  assert(0 && "<SparseGraph::GetEdge>: edge does not exist");
}

template <class node_type, class edge_type>
  int SparseGraph<node_type, edge_type>::AddNode(NodeType node){

}

template <class node_type, class edge_type>
  void SparseGraph<node_type, edge_type>::RemoveNode(int node){

}

template <class node_type, class edge_type>
  void SparseGraph<node_type, edge_type>::AddEdge(EdgeType edge){

}

template <class node_type, class edge_type>
  void SparseGraph<node_type, edge_type>::SetEdgeCost(int src, int dst, double cost){

}

template <class node_type, class edge_type>
  bool SparseGraph<node_type, edge_type>::Save(const char *filename) const {

}

template <class node_type, class edge_type>
  bool SparseGraph<node_type, edge_type>::Save(std::ofstream &stream) const {

}

template <class node_type, class edge_type>
  bool SparseGraph<node_type, edge_type>::Load(const char *filename){

}

template <class node_type, class edge_type>
  bool SparseGraph<node_type, edge_type>::Load(std::ifstream &stream){

}



#endif	/* __SPARSEGRAPH_H__ */
