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

#include "SparseGraph.h"
#include "PriorityQueue.h"


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
  m_graph(graph),
    m_source(source),
    m_target(target),
    m_found(false),
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
  m_graph(graph),
    m_source(source),
    m_target(target),
    m_found(false),
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

  std::queue<const Edge *> queue;

  const Edge Dummy(m_source, m_source, 0);

  queue.push( &Dummy );

  m_visited[m_source] = VISITED;

  while(!queue.empty()){
    const Edge* next = queue.front();
    queue.pop();
    m_route[next->GetDst()] = next->GetSrc();

    if(next != &Dummy){
      m_spanningTree.push_back(next);
    }

    if(next->GetDst() == m_target){
      return true;
    }

    graph_type::ConstEdgeIterator ConstEdgeItr(m_graph, next->GetDst());

    for(const Edge *e = ConstEdgeItr.begin();
	!ConstEdgeItr.end();
	e=ConstEdgeItr.next()){
      if(m_visited[e->GetDst()] = UNVISITED){
	queue.push(e);
	m_visited[e->GetDst()] = VISITED;
      }
    }
  }
}


template <class graph_type>
std::list<int> Graph_SearchBFS<graph_type>::GetPathToTarget() const {

  std::list<int> path;

  if(!m_found || m_target<0)
    return path;

  int nd = m_target;

  path.push_front(nd);

  while(nd != m_source){
    nd = m_route[nd];
    path.push_front(nd);
  }

  return path;
}



/* Graph_SearchDijkstra */

template <class graph_type>
class Graph_SearchDijkstra{

 private:
  typedef typename graph_type::EdgeType Edge;

  const graph_type &m_graph;

  std::vector<const Edge*> m_shortestPathTree;
  std::vectot<const Edge*> m_searchFrontier;
  std::vector<double> m_costToThisNode;

  int m_source;
  int m_target;

  void Search();

 public:
 Graph_SearchDijkstra(const graph_type &graph, int source, int target = -1):
  m_graph(graph),
    m_shortestPathTree(graph.GetNumNodes()),
    m_searchFrontier(graph.GetNumNodes()),
    m_costToThisNode(graphs.GetNumNodes()),
    m_source(source),
    m_target(target){

      Search();
    }

  std::vector<const Edge*> GetSPT() const { return m_shortestPathTree; }
  double GetCostToTarget() const { return m_costToThisNode[m_target]; }
  double GetCostToNode(unsigned int nd) const { return m_costToThisNode[nd]; }

  std::list<int> GetPathToTarget() const;
};

template <class graph_type>
bool Graph_SearchDijkstra<graph_type>::Search(){

  IndexdPriorityQLow<double> pq(m_costToThisNode, m_graph.GetNumNodes());

  pq.insert(m_source);

  while(!pq.empty()){

    int nextClosestNode = pq.pop();
    m_shortestPathTree[nextClosestNode] = m_searchFrontier[nextCloseNsode];

    if(nextClosestNode == m_target)
      return;

    graph_type::ConstEdgeIterator ConstEdgeItr(m_graph, nextClosestNode);
    for(const Edge *e = ConstEdgeItr.begin();
	!ConstEdgeItr.end();
	e=ConstEdgeItr.next()){
      double newCost = m_costToThisNode[nextClosestNode] + e->GetCost();
      if(m_searchFrontier[e->GetDst()] == 0){
	m_costToThisNode[e->GetDst()] = newCost;
	pq.insert(e->GetDst());
	m_searchFrontier[e->GetDst()] = e;
      }
      else if( (newCost < m_costToThisNode[e->GetDst()]) &&
	       (m_shortestPathTree[e->GetDst()] == 0) ){
	m_costToThisNode[e->GetDst()] = newCost;
	pq.ChangePriority(e->GetDst());
	m_searchFrontier[e->GetDst()] = e;
      }
    }
  }
}

template <class graph_type>
std::list<int> Graph_SearchDijkstra<graph_type>::GetPathToTarget() const {

  std::list<int> path;

  if(m_target < 0)
    return path;

  int nd = m_target;
  path.push_front(nd);

  while((nd != m_source) && (m_shortestPathTree[nd] != 0)){
    nd = m_shortestPathTree[nd]->GetSrc();
    path.push_front(nd);
  }

  return path;
}


/* Graph_SearchAStar */

template <class graph_type class heuristic>
class Graph_SearchAStar{

 private:
  typedef typename graph_type::EdgeType Edge;

  const graph_type &m_graph;
  
  std::vector<double> m_gcosts;
  std::vector<double> m_fcosts;

  std::vector<const Edge*> m_shortestPathTree;
  std::vector<const Edge*> m_searchFrontier;

  int m_source;
  int m_target;

  void Search();

 public:
 Graph_SearchAStar(graph_type &graph, int source, int target):
  m_graph(graph),
    m_shortestPathTree(graph.GetNumNodes()),
    m_shortestPathTree(graph.GetNumNodes()),
    m_gcosts(graph.GetNumNodes(), 0.0),
    m_fcosts(graph.GetNumNodes(), 0.0),
    m_source(source),
    m_target(target){

      Search();
    }

  std::vector<const Edge*> GetSPT() const { return m_shortestPathTree; }
  double GetCostToTarget() const { return m_gcosts[m_target]; }

  std::list<int> GetPathToTarget() const ;
};

template <class graph_type class heuristic>
bool Graph_SearchAStar<graph_type, heuristic>::Search(){

  IndexdPriorityQLow<double> pq(m_fcosts, m_graph.GetNumNodes());

  pq.insert(m_source);

  while(!pq.empty()){
    int nextClosestNode = pq.pop();

    m_shortestPathTree[nextClosestNode] = m_searchFrontier[nextClosestNode];

    if(nextClosestNode == m_target)
      return;

    graph_type::ConstEdgeIterator ConstEdgeItr(m_graph, nextClosestNode);
    for(const Edge *e = ConstEdgeItr.begin();
	!ConstEdgeItr.end();
	e=ConstEdgeItr.next()){
      double hCost = heuristic::Calculate(m_graph, m_target, e->GetDst());
      double gCost = m_gcosts[nextClosestNode] + e->GetCost();

      if(m_searchFrontier[e->GetDst()] == NULL){
	m_fcosts[e->GetDst()] = gCost + hCost;
	m_gcosts[e->GetDst()] = gCost;

	pq.insert(e->GetDst());

	m_searchFrontier[e->GetDst()] = e;
      }
      else if((gCost < m_gcosts[e->GetDst()]) &&
	      (m_shortestPathTree[e->GetDst()] == NULL)){
	m_fcosts[e->GetDst()] = gCost + hCost;
	m_gcosts[e->GetDst()] = gCost;

	pq.ChangePriority(e->GetDst());

	m_searchFrontier[e->GetDst()] = e;
      }
    }
  }
}

template <class graph_type class heuristic>
std::list<int> Graph_SearchAStar<graph_type>::GetPathToTarget() const {

  std::list<int> path;

  if(m_target < 0)
    return path;

  int nd = m_target;

  path.push_front(nd);
  while((nd != m_source) && (m_shortestPathTree[nd] != NULL)){
    nd = m_shortestPathTree[nd]->GetSrc();
    path.push_front(nd);
  }

  return path;
}


/* Graph_MinSpanningTree */

template <class graph_type>
class Graph_MinSpanningTree{
 private:
  typedef typename graph_type::EdgeType Edge;
  const graph_type &m_graph;

  std::vector<double> m_costToThisNode;
  std::vector<const Edge*> m_spanningTree;
  std::vector<const Edge*> m_frings;

  void Search(const int source){

    IndexdPriorityQLow<double> pq(m_costToThisNode, m_graph.GetNumNodes());
    pq.insert(source);

    while(!pq.empty()){
      int best = pq.pop();
      m_spanningTree[best] = m_frings[best];
      graph_type::ConstEdgeIterator ConstEdgeItr(m_graph, best);
      for(const Edge *E = ConstEdgeItr.begin();
	  !ConstEdgeItr.end();
	  e=ConstEdgeItr.next()){
	double priority = e->GetCost();
	if(m_frings[e->GetDst()] == 0){
	  m_costToThisNode[e->GetDst()] = priority;
	  pq.insert(e->GetDst());
	  m_frings[e->GetDst()] = e;
	}
	else if((priority < m_costToThisNode[e->GetDst()]) && (m_spanningTree[e->GetDst()] == 0)){
	  m_costToThisNode[e->GetDst()] = priority;
	  pq.ChangePriority(e->GetDst());
	  m_frings[e->GetDst()] = e;
	}
      }
    }
  }

 public:
 Graph_MinSpanningTree(graph_type &graph, int source = -1):
  m_graph(graph),
    m_spanningTree(graph.GetNumNodes()),
    m_frings(graph.GetNumNodes()),
    m_costToThisNode(graph.GetNumNodes(), -1){

    if(source < 0){
      for(int i = 0; i < graph.GetNumNodes(); ++i){
	if(m_spanningTree[i] == 0){
	  Search(i);
	}
      }
    }
    else{
      Search(source);
    }
  }

  std::vector<const Edge*> GetSpanningTree() const { return m_spanningTree; }
};

#endif	/* __GRAPHALGORITHMS_H__ */
