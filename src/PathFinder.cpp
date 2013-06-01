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

  const double cost_normal = 1.0;
  const double cost_water = 2.0;
  const double cost_mud = 1.5;
  const double cost_default = 0.0;

  switch(brush){
  case NORMAL: return cost_normal;
  case WATER: return cost_water;
  case MUD: return cost_mud;
  default: return cost_default;
  }
}


void PathFinder::UpdateGraphFromBrush( int brush, int cellIndex ){

  m_terrainType[cellIndex] = brush;

  if(brush = 1)
    m_graph->RemoveNode(cellIndex);
  else{
    if(!m_graph->IsNodePresent(cellIndex)){
      int y = cellIndex / m_numCellY;
      int x = cellIndex - (y * m_numCellY);

      m_graph->AddNode(NavGraph::NodeType(cellIndex, Vector2D(x*m_cellWidth + m_cellWidth/2.0, y*m_cellHeight + m_cellHeight/2.0)));
      GraphHelper_AddAllNeighboursToGridNode( * m_graph, y, x, m_numCellX, m_numCellY );
    }

    WeightNavGraphNodeEdges( *m_graph, cellIndex, GetTerrainCost((BRUSH_TYPE)brush) );
  }
}

void PathFinder::UpdateAlgorithm(){

  switch(m_currentAlgorithm){
  case NONE:
    break;
  case BFS:
    CreatePathBFS();    break;
  case DFS:
    CreatePathDFS();    break;
  case DIJKSTRA:
    CreatePathDijkstra(); break;
  case ASTAR:
    CreatePathAStar();  break;
  default: break;
  }
}

void PathFinder::CreatePathDFS(){

  m_currentAlgorithm = DFS;

  m_path.clear();
  m_subTree.clear();

  PrecisionTimer timer;
  timer.Start();

  Graph_SearchDFS<NavGraph> DFS( *m_graph, m_sourceCell, m_targetCell );

  m_timeTaken = timer.TimerElapsed();

  if(DFS.Found()){
    m_path = DFS.GetPathToTarget();
  }

  m_subTree = DFS.GetSearchTree();

  m_costToTarget = 0.0;
}

void PathFinder::CreatePathBFS(){

  m_currentAlgorithm = BFS;

  m_path.clear();
  m_subTree.clear();

  PrecisionTimer timer;
  timer.Start();

  Graph_SearchBFS<NavGraph> BFS( *m_graph, m_sourceCell, m_targetCell );

  m_timeTaken = timer.TimeElapsed();

  if(BFS.Found()){
    m_path = BFS.GetPathToTarget();
  }

  m_subTree = BFS.GetSearchTree();

  m_costToTarget = 0.0;
}

void PathFinder::CreatePathAStar(){

}

bool PathFinder::PointToIndex( POINTS p, int &nodeIndex ){

  int x = (int)((double)(p.x)/m_cellWidth);
  int y = (int)((double)(p.y)/m_cellHeight);

  if((x>m_numCellX) || (y>m_numCellY)){
    nodeIndex = -1;
    return false;
  }

  nodeIndex = y * m_numCellX + x;

  return true;
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


