#pragma once
#include "state.h"
#include <climits>
#include <cfloat>
#include <algorithm>

action MinMaxSearch(const state & s, const int depth, bool & killerMove);
float max_value(const state & s, const int depth, bool & killerMove);
float min_value(const state & s, const int depth, bool & killerMove);

action IDDLMS(const state & s, const int & maxDepth)
{
  bool killerMove = false;
  int currentDepth = 1;
  action a;
  while(currentDepth <= maxDepth && killerMove == false)
  {
    a = MinMaxSearch(s, currentDepth, killerMove);
    currentDepth++;
  }
  return a;
}

action MinMaxSearch(const state & s, const int depth, bool & killerMove)
{
  action bestAction;
  float bestActionScore = FLT_MIN;
  auto allActions = s.possibleActionsF();
  for(const auto & a: allActions)
  {
    auto value = min_value(s + a, depth - 1, killerMove);
    if((value > bestActionScore) || (value == bestActionScore && std::rand() % 2))
    {
      bestAction = a;
      bestActionScore = value;
    }
  }
  return bestAction;
}

float max_value(const state & s, const int depth, bool & killerMove)
{
  if(depth == 0 || s.terminal())
  {
    auto value = s.getValue();
    if(value == 1)
    {
      killerMove = true;
    }
    return value;
  }
  float value = FLT_MIN;
  auto allActions = s.possibleActionsF();
  for(const auto & a: allActions)
  {
    value = std::max(value, min_value(s + a, depth - 1, killerMove));
  }
  return value;
}

float min_value(const state & s, const int depth, bool & killerMove)
{
  if(depth == 0 || s.terminal())
  {
    auto value = s.getValue();
    if(value == 1)
    {
      killerMove = true;
    }
    return value;
  }
  float value = FLT_MAX;
  auto allActions = s.possibleActionsE();
  for(const auto & a: allActions)
  {
    value = std::min(value, max_value(s + a, depth - 1, killerMove));
  }
  return value;
}