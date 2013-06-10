/****************************************************************************
 *
 *    GraphUtile.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 *
 *    DESC: Some useful functions to graph. For the function templates, 
 *          make sure your graph interface complies with the 
 *          SparseGraph class.
 ***************************************************************************/

#ifndef __GRAPHUTILES_H__
#define __GRAPHUTILES_H__

#include <iostream>

#include "Wpgdi.h"
#include "Utils.h"
#include "StreamUtils.h"
#include "GraphAlgorithms.h"


template <class graph_type>
bool ValidNeighbour(int x, int y, int numCellsX, int numCellsY){

  return !((x < 0) || (x >= numCellsX) || (y < 0) || (y >= numCellsY));
}

template <class graph_type>
void GraphHelper_AddAllNeighboursToGridNode(graph_type &graph,
					    int row, 
					    int col,
					    int numCellsX,
					    int numCellsY){
  /* use to add the eight neighboring edges of a graph node that is  
   * positioned in a grid layout
   */
  
  for(int i = -1; i < 2; ++i){
    for(int j = 1; j < 2; ++j){
      int nodeX = col + j;
      int nodeY = row + i;

      if((i == 0) && (j == 0))
	continue;

      if(ValidNeighbour(nodeX, nodeY, numCellsX, numCellsY)){
	Vector2D posNode = graph.GetNode(row*numCellsX+col).GetPosition();
	Vector2D posNeighbor = graph.GetNode(nodeY*numCellsX+nodeX).GetPosition();

	double dist = posNode.Distance(posNeighbor);

	graph_type::EdgeType newEdge(row*numCellsX+col,
				     nodeY*numCellsX+nodeX,
				     dist);
	graph.AddEdge(newEdge);

	/* 
	 * if graph is not a diagraph then an edge needs to be added going
	 * in the other direction
	 */
	if(!graph.IsDigraph()){
	  graph_type::EdgeType newEdge(nodeY*numCellsX+nodeX,
				       row*numCellsX+col,
				       dist);
	  graph.AddEdge(newEdge);
	}
      }
    }
  }
}
	

template <class graph_type>
void GraphHelper_CreateGrid(graph_type &graph,
			    int cySize, 
			    int cxSize,
			    int numCellsY,
			    int numCellsX){
  /* Create a graph based on a grid layout. This function requires the
   * dimesions of the environment and the number of cells required 
   * horizontally and vertically
   */

  double cellWidth = (double)cySize / (double)numCellsX;
  double cellHeight = (double)cxSize /  (double)numCellsY;

  double midX = cellWidth / 2;
  double midY = cellHeight / 2;

  /* first create all the nodes */
  for(int row = 0; row < numCellsY; ++row)
    for(int col = 0; col < numCellsX; ++col){
      graph.AddNode(NavGraphNode<>(graph.GetNextFreeNodeIndex(),
				   Vector2D(midX + (col * cellWidth),
					    midY + (row * cellHeight))));
    }

  /* now to calculate the edges. */
  for(int row = 0; row < numCellsY; ++row)
    for(int col = 0; col < numCellsX; ++col){
      GraphHelper_AddAllNeighboursToGridNode(graph, row, col, 
					     numCellsX, numCellsY);
    }

}


template <class graph_type>
void WeightNavGraphNodeEdges(graph_type &graph, int node, double weight){

  /* 
   * give a cost value and an index to a valid node this function examines
   * all a node's edges, calculates their length, and multiplies the
   * value with the weight. Useful for setting terrain costs.
   */
  assert(node < graph.GetNumNodes());

  graph_type::ConstEdgeIterator ConstEdgeItr(graph, node);
  for(const graph_type::EdgeType *e = ConstEdgeItr.begin();
      !ConstEdgeItr.end();
      e=ConstEdgeItr.next()){

    double dist = Vec2DDistance(graph.GetNode(e->GetSrc()).GetPosition(),
				graph.GetNode(e->GetDst()).GetPosition());

    graph.SetEdgeCost(e->GetSrc(), e->GetDst(), dist * weight);

    if(!graph.IsDigraph()){
      graph.SetEdgeCost(e->GetDst(), e->GetSrc(), dist * weight);
    }
  }
}

template <class graph_type>
void GraphHelper_DrawUsingGDI(const graph_type &graph, int color, bool drawNodeIDs = false){

  if(graph.GetNumNodes() == 0)
    return;

  wpgdi->SetPenColor(color);

  /* draw the nodes */
  graph_type::ConstNodeIterator nodeItr(graph);
  for(const graph_type::NodeType *n = nodeItr.begin();
      !nodeItr.end();
      n = nodeItr.next()){
    wpgdi->Circle(n->GetPosition(), 2);
    if(drawNodeIDs){
      wpgdi->TextColor(200, 200, 200);
      wpgdi->TextAtPos((int)n->GetPosition().x+5, (int)n->GetPosition().y-5,
		       ttos(n->GetIndex()));
    }

    graph_type::ConstEdgeIterator edgeItr(graph, n->GetIndex());
    for(const graph_type::EdgeType *e = edgeItr.begin();
	!edgeItr.end();
	e = edgeItr.next()){
      wpgdi->Line(n->GetPosition(), graph.GetNode(e->GetDst()).GetPosition());
    }
  }
}


#endif	/* __GRAPHUTILES_H__ */
