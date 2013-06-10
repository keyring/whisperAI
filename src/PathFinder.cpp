/*****************************************************************************
 *
 *    PathFinder.cpp by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                    --code with Emacs :)
 ****************************************************************************/

#include "PathFinder.h"
#include "Wpgdi.h"
#include "Constants.h"
#include "GraphUtils.h"
#include "PrecisionTimer.h"
#include "AStarHeuristicPolicies.h"
#include "StreamUtils.h"

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
  m_cyClient = rect.bottom - abs(rectToolbar.bottom - rectToolbar.top) - INFOWINDOWHEIGHT;

  m_terrainType.assign( cellsUp * cellsAcross, NORMAL );

  m_numCellsX = cellsAcross;
  m_numCellsY = cellsUp;
  m_cellWidth = (double)m_cxClient / (double)cellsAcross;
  m_cellHeight = (double)m_cyClient / (double)cellsUp;

  delete m_graph;	//delete any old graph

  m_graph = new NavGraph(false);	//not a digraph

  GraphHelper_CreateGrid( *m_graph, m_cxClient, m_cyClient, cellsUp, cellsAcross );

  PointToIndex(VectorToPOINTS(Vector2D(m_cxClient/2, m_cellHeight*2)), m_targetCell);
  PointToIndex(VectorToPOINTS(Vector2D(m_cxClient/2, m_cyClient - m_cellHeight*2)), m_sourceCell);

  m_path.clear();
  m_subTree.clear();

  m_currentAlgorithm = NONE;
  m_timeTaken = 0;
}

void PathFinder::Render(){
  
  wpgdi->TransparentText();
  
  // render all the cells
  for(int i = 0; i < m_graph->GetNumNodes(); ++i){
    int left = (int)(m_graph->GetNode(i).GetPosition().x - m_cellWidth/2.0);
    int top = (int)(m_graph->GetNode(i).GetPosition().y - m_cellHeight/2.0);
    int right = (int)(1 + m_graph->GetNode(i).GetPosition().x + m_cellWidth/2.0);
    int bottom = (int)(1 + m_graph->GetNode(i).GetPosition().y + m_cellHeight/2.0);
    
    wpgdi->GreyPen();
    
    switch(m_terrainType[i]){
    case 0:
      wpgdi->WhiteBrush();
      if(!m_showTiles) wpgdi->WhitePen();
      break;
      
    case 1:
      wpgdi->BlackBrush();
      if(!m_showTiles) wpgdi->BlackPen();
      break;
      
    case 2:
      wpgdi->LightBlueBrush();
      if(!m_showTiles) wpgdi->LightBluePen();
      break;
      
    case 3:
      wpgdi->BrownBrush();
      if(!m_showTiles) wpgdi->BrownPen();
      break;
      
    default:
      wpgdi->WhiteBrush();
      if(!m_showTiles) wpgdi->WhitePen();
      break;
      
    } // switch
    
    if( i == m_targetCell){
      wpgdi->RedBrush();
      if(!m_showTiles) wpgdi->RedPen();
    }

    if( i == m_sourceCell){
      wpgdi->GreenBrush();
      if(!m_showTiles) wpgdi->GreenPen();
    }

    wpgdi->Rect(left, top, right, bottom);

    if( i == m_targetCell){
      wpgdi->ThickBlackPen();
      wpgdi->Cross(Vector2D(m_graph->GetNode(i).GetPosition().x - 1,
			    m_graph->GetNode(i).GetPosition().y - 1),
		   (int)((m_cellWidth *0.6) / 2.0));
    }

    if( i == m_sourceCell){
      wpgdi->ThickBlackPen();
      wpgdi->HollowBrush();
      wpgdi->Rect(left+7, top+7, right-6, bottom-6);
    }

    // render dots at the corners of the cells
    wpgdi->DrawDot(left, top, RGB(0,0,0));
    wpgdi->DrawDot(right-1, top, RGB(0,0,0));
    wpgdi->DrawDot(left, bottom-1, RGB(0,0,0));
    wpgdi->DrawDot(right-1, bottom-1, RGB(0,0,0));
  }

  // draw the graph nodes and edges if required.
  if(m_showGraph){
    // false means do not draw node IDs
    GraphHelper_DrawUsingGDI<NavGraph>(*m_graph, Wpgdi::LIGHT_GREY, false);
  }

  // draw any tree retrieved from the algorithms
  wpgdi->RedPen();
  for(unsigned int e = 0; e < m_subTree.size(); ++e){
    if(m_subTree[e]){
      Vector2D src = m_graph->GetNode(m_subTree[e]->GetSrc()).GetPosition();
      Vector2D dst = m_graph->GetNode(m_subTree[e]->GetDst()).GetPosition();

      wpgdi->Line(src, dst);
    }
  }

  // draw the path
  if(m_path.size() > 0){
    wpgdi->ThickBluePen();

    std::list<int>::iterator it = m_path.begin();
    std::list<int>::iterator nxt = it;
    ++nxt;

    for(it; nxt != m_path.end(); ++it, ++nxt){
      wpgdi->Line(m_graph->GetNode(*it).GetPosition(),
		  m_graph->GetNode(*nxt).GetPosition());
    }
  }

  if(m_timeTaken){
    // draw time taken to complete algorithm
    string time = ttos(m_timeTaken, 8);
    string s = "Time Elapsed for " + GetNameOfCurrentSearchAlgorithm() + " is " + time;
    wpgdi->TextAtPos(1, m_cyClient+1, s);
  }

  // display the tota cost if appropriate
  if(m_currentAlgorithm == ASTAR || m_currentAlgorithm == DIJKSTRA){
    wpgdi->TextAtPos(m_cxClient-110, m_cyClient+1, "Cost is " + ttos(m_costToTarget));
  }
}

void PathFinder::PaintTerrain( POINTS p ){
  
  int x = (int)((double)(p.x)/m_cellWidth);
  int y = (int)((double)(p.y)/m_cellHeight);
  
  if( (x>m_numCellsX) || (y>(m_numCellsY-1)) ) return;
  
  m_subTree.clear();
  m_path.clear();
  
  if( (m_currentTerrainBrush == SOURCE) || (m_currentTerrainBrush == TARGET) ){
    switch(m_currentTerrainBrush){
    case SOURCE:
      m_sourceCell = y * m_numCellsX + x;    break;
    case TARGET:
      m_targetCell = y * m_numCellsX + x;    break;
    }
  }

  else{
    UpdateGraphFromBrush(m_currentTerrainBrush, y * m_numCellsX + x);
  }

  UpdateAlgorithm();
}

double PathFinder::GetTerrainCost( const BRUSH_TYPE brush ){

  const double cost_normal = 1.0;
  const double cost_water = 2.0;
  const double cost_mud = 1.5;
  const double cost_default = MaxDouble;

  switch(brush){
  case NORMAL: return cost_normal;
  case WATER: return cost_water;
  case MUD: return cost_mud;
  default: return cost_default;
  }
}


void PathFinder::UpdateGraphFromBrush( int brush, int cellIndex ){

  m_terrainType[cellIndex] = brush;

  if(brush == 1)
    m_graph->RemoveNode(cellIndex);
  else{
    if(!m_graph->IsNodePresent(cellIndex)){
      int y = cellIndex / m_numCellsY;
      int x = cellIndex - (y * m_numCellsY);

      m_graph->AddNode(NavGraph::NodeType(cellIndex, Vector2D(x*m_cellWidth + m_cellWidth/2.0, y*m_cellHeight + m_cellHeight/2.0)));

      GraphHelper_AddAllNeighboursToGridNode( *m_graph, y, x, m_numCellsX, m_numCellsY );
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

  //do the search
  Graph_SearchDFS<NavGraph> dfs( *m_graph, m_sourceCell, m_targetCell );

  m_timeTaken = timer.TimeElapsed();

  if(dfs.Found()){
    m_path = dfs.GetPathToTarget();
  }

  m_subTree = dfs.GetSearchTree();

  m_costToTarget = 0.0;
}

void PathFinder::CreatePathBFS(){

  m_currentAlgorithm = BFS;

  m_path.clear();
  m_subTree.clear();

  PrecisionTimer timer;
  timer.Start();

  Graph_SearchBFS<NavGraph> bfs( *m_graph, m_sourceCell, m_targetCell );

  m_timeTaken = timer.TimeElapsed();

  if(bfs.Found()){
    m_path = bfs.GetPathToTarget();
  }

  m_subTree = bfs.GetSearchTree();

  m_costToTarget = 0.0;
}

void PathFinder::CreatePathDijkstra(){

  m_currentAlgorithm = DIJKSTRA;
  
  PrecisionTimer timer;
  timer.Start();
  
  Graph_SearchDijkstra<NavGraph> djk( *m_graph, m_sourceCell, m_targetCell );
  
  m_timeTaken = timer.TimeElapsed();
  
  m_path = djk.GetPathToTarget();
  
  m_subTree = djk.GetSPT();
  
  m_costToTarget = djk.GetCostToTarget();
}

void PathFinder::CreatePathAStar(){

  m_currentAlgorithm = ASTAR;

  PrecisionTimer timer;
  timer.Start();

  Graph_SearchAStar<NavGraph, Heuristic_Euclid> AStar( *m_graph, m_sourceCell, m_targetCell );

  m_timeTaken = timer.TimeElapsed();

  m_path = AStar.GetPathToTarget();

  m_subTree = AStar.GetSPT();

  m_costToTarget = AStar.GetCostToTarget();
}

bool PathFinder::PointToIndex( POINTS p, int &nodeIndex ){

  int x = (int)((double)(p.x) / m_cellWidth);
  int y = (int)((double)(p.y) / m_cellHeight);

  if((x > m_numCellsX) || (y > m_numCellsY)){
    nodeIndex = -1;
    return false;
  }

  nodeIndex = y * m_numCellsX + x;

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

  save << m_numCellsX << endl;
  save << m_numCellsY << endl;

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

  load >> m_numCellsX;
  load >> m_numCellsY;

  CreateGraph(m_numCellsY, m_numCellsX);

  int terrain;

  for(int t = 0; t < m_numCellsX * m_numCellsY; ++t){
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


