/****************************************************************************
 *
 *    AStarHeuristicPolicies.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 *
 *    DESC: Class templates defining a heuristic policy for use with
 *          the A* search algorithm.
 ***************************************************************************/

#ifndef __ASTARHEURISTICPOLICIES_H__
#define __ASTARHEURISTICPOLICIES_H__


#include "Utils.h"

class Heuristic_Euclid{
 public:
  Heuristic_Euclid(){ }

template <class graph_type>
  static double Calculate(const graph_type &g, int nd1, int nd2){

  return Vec2DDistance(g.GetNode(nd1).GetPosition(), g.GetNode(nd2).GetPosition());
 }
};

class Heuristic_Noisy_Euclidian{
 public:
  Heuristic_Noisy_Euclidian(){ }

template <class graph_type>
  static double Calculate(const graph_type &g, int nd1, int nd2){

  return Vec2DDistance(g.GetNode(nd1).GetPosition(), g.GetNode().GePosition()) * RandInRange(0.9f, 1.1f);
 }
};

class Heuristic_Dijkstra{
  /* you can use this class to turn the A* into Dijkstra. */
 public:
template <class graph_type>
  static double Calculate(const graph_type &g, int nd1, int nd2){
  return 0;
 }
};


#endif	/* __ASTARHEURISTICPOLICIES_H__ */
