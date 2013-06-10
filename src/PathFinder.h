/*****************************************************************************
 *
 *    PathFinder.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                     --code with Emacs :)
 ****************************************************************************/

#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#pragma warning (disable:4786)

#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <list>


#include "Vector2D.h"
#include "Utils.h"
#include "SparseGraph.h"
#include "GraphEdge.h"
#include "GraphNode.h"
#include "GraphAlgorithms.h"


class PathFinder{

public :
  
  enum BRUSH_TYPE{
    NORMAL = 0,
    OBSTACLE,
    WATER,
    MUD,
    SOURCE,
    TARGET
  };

  enum ALGORITHM_TYPE{
    NONE,
    ASTAR,
    BFS,
    DFS,
    DIJKSTRA
  };

 private:
  std::vector<int> m_terrainType;
  std::list<int> m_path;
  
  typedef SparseGraph<NavGraphNode<void*>, GraphEdge> NavGraph;
  NavGraph *m_graph;
  
  std::vector<const GraphEdge*> m_subTree;

  double m_costToTarget;
  ALGORITHM_TYPE m_currentAlgorithm;
  BRUSH_TYPE m_currentTerrainBrush;

  double m_cellWidth;
  double m_cellHeight;

  int m_numCellsX;
  int m_numCellsY;

  //local record of the client area
  int m_cxClient;
  int m_cyClient;

  int m_sourceCell;
  int m_targetCell;

  //flags to indicate if the start and finish points have been added
  bool m_start;
  bool m_finish;

  //should the graph(nodes and edges) and tile outlines be rendered?
  bool m_showGraph;
  bool m_showTiles;

  //holds the time taken for the currently used algorithm to complete
  double m_timeTaken;

  void UpdateAlgorithm();
  void UpdateGraphFromBrush( int  brush, int cellIndex );

  std::string GetNameOfCurrentSearchAlgorithm() const;

public:
  PathFinder():m_start(false),
	       m_finish(false),
	       m_showGraph(false),
	       m_showTiles(true),
	       m_cellWidth(0.0),
	       m_cellHeight(0.0),
	       m_numCellsX(0),
	       m_numCellsY(0),
	       m_timeTaken(0.0),
	       m_currentTerrainBrush(NORMAL),
	       m_sourceCell(0),
	       m_targetCell(0),
	       m_cxClient(0),
	       m_cyClient(0),
	       m_costToTarget(0.0),
		   m_graph(NULL){ 
		   
    // empty
}

  ~PathFinder(){ delete m_graph; }

  void CreateGraph( int cellsUp, int cellsAcross );
  void Render();
  void PaintTerrain( POINTS p );

  /* all algorithm */
  void CreatePathDFS();
  void CreatePathBFS();
  void CreatePathDijkstra();
  void CreatePathAStar();
  void MinSpanningTree();
  
  void ToggleShowGraph(){ m_showGraph = !m_showGraph; }
  void SwitchGraphOn(){ m_showGraph = true; }
  void SwitchGraphOff(){ m_showGraph = false; }
  bool IsShowGraphOn() const { return m_showGraph; }

  void ToggleShowTiles(){ m_showTiles = !m_showTiles; }
  void SwitchTilesOn(){ m_showTiles = true; }
  void SwitchTilesOff(){ m_showTiles = false; }
  bool IsShowTilesOn() const { return m_showTiles; }

  void ChangeBrush( const BRUSH_TYPE value ){ m_currentTerrainBrush = value; }
  void ChangeSource( const int value ){ m_sourceCell = value; }
  void ChnageTarget( const int value ){ m_targetCell = value; }

  bool PointToIndex( POINTS p, int &NodeIndex );

  double GetTerrainCost( BRUSH_TYPE brush );

  void Save( char *filename );
  void Load( char *filename );
};

#endif	/* __PATHFINDER_H__ */
