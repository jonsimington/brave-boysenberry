#pragma once
#include "state.h"
#include <cfloat>
#include <algorithm>

action MinMaxSearch(state & s, const int depth);
float max_value(state & s, float alpha, float beta, const int depth);
float min_value(state & s, float alpha, float beta, const int depth);

//Iterative deepening depth limited min max search
action IDDLMS(state & s, const int & maxDepth)
{
  int currentDepth = 1;
  action a;
  while(currentDepth <= maxDepth)
  {
    std::cout << "DepthStart: " << currentDepth << std::endl;
    a = MinMaxSearch(s, currentDepth);
    std::cout << "Depthend: " << currentDepth << std::endl;
    currentDepth++;
  }
  return a;
}
//Minmax search of set depth
action MinMaxSearch(state & s, const int depth)
{
  /*contains actions that have the same hueristic value
  one random one is returned at the end of the function*/
  std::vector<action> sameScore;
  float alpha = FLT_MAX * -1;
  float beta = FLT_MAX;
  auto allActions = s.possibleActionsF();
  float bestActionScore = FLT_MAX * -1;
  for(const auto & a: allActions)
  {
    s.applyAction(a);
    float value = min_value(s, alpha, beta, depth - 1);
    s.reverseAction(a);
    if((value > bestActionScore))
    {
      bestActionScore = value;
      sameScore.clear();
      sameScore.push_back(a);
    }
    else if(value == bestActionScore)
    {
      sameScore.push_back(a);
    }
  }
  return sameScore[rand() % sameScore.size()];
}

float max_value(state & s, float alpha, float beta, const int depth)
{
  if(depth == 0 || s.terminal())
  {
   return s.getValue();
  }
  float value = FLT_MAX * -1;
  auto allActions = s.possibleActionsF();
  if(allActions.size() == 0)
  {
    if(s.inCheck(s.m_friendlyPieces))
    {
      return -10000; 
    }
    else//if they're not in check and there's no move's it's a draw
    {
      return 0;
    }
  }
  for(const auto & a: allActions)
  {
    s.applyAction(a);
    value = std::max(value, min_value(s, alpha, beta, depth - 1));
    s.reverseAction(a);
    if(value >= beta)
      return value;
    alpha = std::max(alpha, value);
  }
  return value;
}

float min_value(state & s, float alpha, float beta, const int depth)
{
  if(depth == 0 || s.terminal())
  {
    return s.getValue();
  }
  float value = FLT_MAX;
  auto allActions = s.possibleActionsE();
  if(allActions.size() == 0)
  {
    if(s.inCheck(s.m_enemyPieces))
    {
      return 10000; 
    }
    else//if they're not in check and there's no move its a draw
    {
      return 0;
    }
  }
  for(const auto & a: allActions)
  {
    s.applyAction(a);
    value = std::min(value, max_value(s, alpha, beta, depth - 1));
    s.reverseAction(a);
    if(value <= alpha)
      return value;
    beta = std::min(beta,value);
  }
  return value;
}