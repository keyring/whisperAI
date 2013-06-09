/****************************************************************************
 *
 *    GraphAlgorithms.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 *
 *    DESC: Classes to implement graph algorithms, include DFS, BFS,
 *          Dijkstra, A* etc.
 *          Any graphs passed to these functions must conform to the
 *          same interface used by the SparseGraph.
 ***************************************************************************/

#ifndef __GRAPHALGORITHMS_H__
#define __GRAPHALGORITHMS_H__

#include <vector>
#include <list>
#include <queue>
#include <stack>

#include "SparseGraph"


/* Graph_SearchDFS */

template <class graph_type>
class Graph_SearchDFS{

 private:
  enum{
    VISITED,
    UNVISITED,
    NO_PARENT_ASSIGNED
  };

  typedef typename graph_type::EdgeType Edge;
  typedef typename graph_type::NodeType Node;

  const graph_type &m_graph;
  std::vector<int> m_visited;	/* record the index of all visted nodes */
  std::vector<int> m_route;	/* hold the route taken to the target */

  /* Hold all edges the algorithm has examined. 
   * IT IS HERE NOT NECESSARY FOR SEARCH, 
   * JUST PROVIDE THE USER SOME VISUAL EFFECT 
   */
  std::vector<const Edge*> m_spanningTree;

  int m_source;
  int m_target;

  bool m_found;

  bool Search();

 public:
 Graph_SearchDFS(const graph_type &gaph, int source, int target = -1):
  m_graph(graph), m_source(source), m_target(target), m_found(false),
    m_visited(m_graph.GetNumNodes(), UNVISITED),
    m_route(m_graph.GetNumNodes(), NO_PARENT_ASSIGNED){

    m_found = Search();
  }

  std::vector<const Edge*> GetSearchTree() const { return m_spanningTree; }
  bool Found() const { return m_found; }
  std::list<int> GetPathToTarget() const;

};


template <class graph_type>
bool Graph_SearchDFS<graph_type>::Search(){

  std::stack<const Edge*> stack;

  Edge Dummy(m_source, m_source, 0.0);

  stack.push( &Dummy );

  while(!stack.empty()){
    /* while there are edges in the stack keep searching */

    const Edge* next = stack.top();
    stack.pop();
    m_route[next->GetDst()] = next->GetSrc();

    if(next != &Dummy){
      m_spanningTree.push_back(next);
    }

    m_visited[next->GetDst()] = VISITED;

    if(next->GetDst() == m_target){
      return true;
    }

    graph_type::ConstEdgeIterator constEdgeItr(m_graph, next->GetDst());

    for(const Edge* e = constEdgeItr.begin();
	!constEdgeItr.end();
	e = constEdgeItr.next()){
      if(m_visited[e.GetDst()] == UNVISITED){
	stack.push(e);
      }
    }
  }

  return false;			/* no path to target */
}


template <class graph_type>
std::list<int> Graph_SearchDFS<graph_type>::GetPathToTarget() const {

  std::list<int> path;

  if(!m_found || m_target<0)
    return path;

  int nd = m_target;
  while(nd != m_source){
    nd = m_route[nd];
    path.push_front(nd);
  }

  return path;
}


/* Graph_SearchBFS */

template <class graph_type>
class Graph_SearchBFS{

 private:
  enum{
    VISITED,
    UNVISITED,
    NO_PARENT_ASSIGNED
  };

  typedef typename graph_type::EdgeType Edge;

 private:
  const graph_type &m_graph;
  std::vector<int> m_visited;
  std::vector<int> m_route;
  std::vector<const Edge *> m_spanningTree;

  int m_source;
  int m_target;

  bool m_found;

  bool Search();       	/* BFS is similar to DFS but using QUEUE not STACK */

 public:
 Graph_SearchBFS(const graph_type &graph, int source, int target-1):
  m_graph(graph), m_source(source), m_target(target), m_found(false),
    m_visited(m_graph.GetNumNodes(), UNVISITED),
    m_route(m_graph.GetNumNodes(), NO_PARENT_ASSIGNED){

    m_found = Search();
  }

  bool Found() const { return m_found; }

  std::vector<const Edge *> GetSearchTree() const { return m_spanningTree; }

  std::list<int> GetPathToTarget() const;
};

template <class graph_type>
bool Graph_SearchBFS<graph_type>::Search(){


}

template <class graph_type>
std::list<int> Graph_SearchBFS<graph_type>::GetPathToTarget() const {

}



/* Graph_SearchDijkstra */

template <class graph_type>
class Graph_SearchDijkstra{


};

template <class graph_type>
bool Graph_SearchDijkstra<graph_type>::Search(){

}

template <class graph_type>
std::list<int> Graph_SearchDijkstra<graph_type>::GetPathToTarget() const {


}


/* Graph_SearchAStar */

template <class graph_type>
class Graph_SearchAStar{


};

template <class graph_type>
bool Graph_SearchAStar<graph_type>::Search(){

}

template <class graph_type>
std::list<int> Graph_SearchAStar<graph_type>::GetPathToTarget() const {

}



#endif	/* __GRAPHALGORITHMS_H__ */
