/*****************************************************************************
 *
 *    PathFinder.cpp by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                    --code with Emacs :)
 ****************************************************************************/

#include <iostream>

#include "PathFinder.cpp"

using namespace std;

extern const char *g_applicationName;
extern const char *g_windowClassName;

void PathFinder::CreateGraph( int cellsUp, int cellsAcross ){


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


