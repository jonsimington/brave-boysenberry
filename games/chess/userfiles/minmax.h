#pragma once
#include "state.h"
#include <climits>
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
  auto allActions = s.possibleActionsF();
  action bestAction;
  auto bestActionScore = FLT_MIN;
  for(const auto & a: allActions)
  {
    auto value = min_value(s + a, depth - 1);
    if((value > bestActionScore) || (value == bestActionScore && std::rand() % 2))
    {
      bestAction = a;
      bestActionScore = value;
    }
  }
  return bestAction;
}

float max_value(const state & s, const int depth)
{
  if(s.isDraw())
  {
    return 0;
  }
  if(depth == 0 || s.terminal())
  {
    auto value = s.getValue();
    return value;
  }
  float value = FLT_MIN;
  auto allActions = s.possibleActionsF();
  if(allActions.size() == 0)
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
  if(s.isDraw())
  {
    return 0;
  }
  if(depth == 0 || s.terminal())
  {
    auto value = s.getValue();
    return value;
  }
  float value = FLT_MAX;
  auto allActions = s.possibleActionsE();
  if(allActions.size() == 0)
  {
    return 0;
  }
  for(const auto & a: allActions)
  {
    value = std::min(value, max_value(s + a, depth - 1));
  }
  return value;
}