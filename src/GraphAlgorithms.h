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



};


template <class graph_type>
bool Graph_SearchDFS<graph_type>::Search(){

}


template <class graph_type>
std::list<int> Graph_SearchDFS<graph_type>::GetPathToTarget() const {


}


/* Graph_SearchBFS */

template <class graph_type>
class Graph_SearchBFS{


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
