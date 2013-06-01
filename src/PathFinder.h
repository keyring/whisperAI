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
#include <vector>
#include <fstream>
#include <string>
#include <list>


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

  double m_costToTarget;
  ALGORITHM_TYPE m_currentAlgorithm;
  BRUSH_TYPE m_currentTerrainBrush;

  double m_cellWidth;
  double m_cellHeight;

  int m_numCellX;
  int m_numCellY;

  int m_cxClient;
  int m_cyClient;

  int m_sourceCell;
  int m_targetCell;

  bool m_start;
  bool m_finish;

  bool m_showGraph;
  bool m_showTiles;

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
	       m_numCellX(0),
	       m_numCellY(0),
	       m_timeTaken(0.0),
	       m_currentTerrainBrush(NORMAL),
	       m_sourceCell(0),
	       m_targetCell(0),
	       m_cxClient(0),
	       m_cyClient(0),
	       m_costToTarget(0.0){ // need init graph....

    // empty

}
  ~PathFinder(){		// delete graph...
}

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
