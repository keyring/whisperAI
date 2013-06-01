/*****************************************************************************
 *
 *    PathFinder.cpp by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                    --code with Emacs :)
 ****************************************************************************/

#include <iostream>

#include "PathFinder.h"

using namespace std;

extern const char *g_applicationName;
extern const char *g_windowClassName;

extern HWND g_hwndToolbar;

void PathFinder::CreateGraph( int cellsUp, int cellsAcross ){

  RECT rectToolbar;
  GetWindowRect( g_hwndToolbar, &rectToolbar );

  HWND hwndMainWindow = FindWindow( g_windowClassName, g_applicationName );

  RECT rect;
  GetClientRect( hwndMainWindow, &rect );
  m_cxClient = rect.right;
  m_cyClient = rect.bottom - abs(rectToolbar.bottom - rectToolbar.top) - InfoWindowHeight;

  m_terrainType.assign( cellsUp * cellsAcross, NORMAL );

  m_numCellX = cellsAcross;
  m_numCellY = cellsUp;
  m_cellWidth = (double)m_cxClient / (double)cellsAcross;
  m_cellHeight = (double)m_cyClient / (double)cellsUp;

  delete m_graph;

  m_graph = new NavGraph(false);

  GraphHelper_CreateGrid( *m_graph, m_cxClient, m_cyClient, cellsUp, cellsAcross );

  PointToIndex(VectorToPOINTS(Vector2D(m_cxClient/2, m_cellHeight*2)), m_targetCell);
  PointToIndex(VectorToPOINTS(Vector2D(m_cxClient/2, m_cyClient - m_cellHeight*2)), m_sourceCell);

  m_path.clear();
  m_subTree.clear();

  m_currentAlgorithm = NONE;
  m_timeTaken = 0;
}

void PathFinder::Render(){

}

void PathFinder::PaintTerrain( POINTS p ){

  int x = (int)((double)(p.x)/m_cellWidth);
  int y = (int)((double)(p.y)/m_cellHeight);

  if( (x>m_numCellX) || (y>m_numCellY) ) return;

  m_subTree.clear();
  m_path.clear();

  if( (m_currentTerrainBrush == SOURCE) || (m_currentTerrainBrush == TARGET) ){
    switch(m_currentTerrainBrush){
    case SOURCE:
      m_sourceCell = y * m_numCellX + x;    break;
    case TARGET:
      m_targetCell = y * m_numCellX + x;    break;
    }
  }

  else{
    UpdateGraphFromBrush(m_currentTerrainBrush, y * m_numCellX + x);
  }

  UpdateAlgorithm();
}

double PathFinder::GetTerrainCost( const BRUSH_TYPE brush ){

}


void PathFinder::UpdateGraphFromBrush( int brush, int cellIndex ){

}

void PathFinder::UpdateAlgorithm(){

}

void PathFinder::CreatePathDFS(){

}

void PathFinder::CreatePathBFS(){

}

void PathFinder::CreatePathAStar(){

}

bool PathFinder::PointToIndex( POINTS p, int &nodeIndex ){


}

std::string PathFinder::GetNameOfCurrentSearchAlgorithm() const {

  switch(m_currentAlgorithm){
  case NONE: return " ";
  case ASTAR: return "A Star";
  case BFS: return "Breadth First";
  case DFS: return "Depth First";
  case DIJKSTRA: return "Dijkstra";
  default: return "UNKNOWN!";
  }
}

void PathFinder::Save( char *filename ){

  ofstream save(filename);
  assert(save && "PathFinder::Save< bad file >");

  save << m_numCellX << endl;
  save << m_numCellY << endl;

  for(unsigned int t = 0; t < m_terrainType.size(); ++t){
    if(t == m_sourceCell)
      save << SOURCE << endl;
    else if(t == m_targetCell)
      save << TARGET << endl;
    else
      save << m_terrainType[t] << endl;
  }
}

void PathFinder::Load( char *filename ){

  ifstream load(filename);
  assert(load && "PathFinder::Load< bad file >");

  load >> m_numCellX;
  load >> m_numCellY;

  CreateGraph(m_numCellY, numCellX);

  int terrain;

  for(int t = 0; t < m_numCellX * numCellY; ++t){
    load >> terrain;
    if(terrain == SOURCE)
      m_sourceCell = t;
    else if(terrain == TARGET)
      m_targetCell = t;
    else{
      m_terrainType[t] = terrain;
      UpdateGraphFromBrush(terrain, t);
    }
  }
}


