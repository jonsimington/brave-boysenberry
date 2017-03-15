#pragma once
#include "state.h"
#include <cfloat>
#include <algorithm>

action MinMaxSearch(const state & s, const int depth);
float max_value(const state & s, const int depth);
float min_value(const state & s, const int depth);

action IDDLMS(const state & s, const int & maxDepth)
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

action MinMaxSearch(const state & s, const int depth)
{
  std::vector<action> sameScore;
  auto allActions = s.possibleActionsF();
  float bestActionScore = FLT_MAX * -1;
  for(const auto & a: allActions)
  {
    float value = min_value(s + a, depth - 1);
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

float max_value(const state & s, const int depth)
{
  if(depth == 0 || s.terminal())
  {
   return s.getValue();
  }
  float value = FLT_MAX * -1;
  auto allActions = s.possibleActionsF();
  if(allActions.size() == 0 && !s.inCheck(s.m_friendlyPieces))
  {
    return 0;
  }
  for(const auto & a: allActions)
  {
    value = std::max(value, min_value(s + a, depth - 1));
  }
  return value;
}

float min_value(const state & s, const int depth)
{
  if(depth == 0 || s.terminal())
  {
    return s.getValue();
  }
  float value = FLT_MAX;
  auto allActions = s.possibleActionsE();
  if(allActions.size() == 0 && !s.inCheck(s.m_enemyPieces))
  {
    return 0;
  }
  for(const auto & a: allActions)
  {
    value = std::min(value, max_value(s + a, depth - 1));
  }
  return value;
}