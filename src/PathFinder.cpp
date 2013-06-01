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

}

void PathFinder::Save( char *filename ){

}

void PathFinder::Load( char *filename ){

}


