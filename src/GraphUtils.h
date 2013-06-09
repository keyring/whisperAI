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
      GraphHelper_AddAllNeighboursToGridNode(graph, row, col, numCellsX, numCellsY);
    }

}







#endif	/* __GRAPHUTILES_H__ */
