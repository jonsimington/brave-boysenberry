#pragma once
#include "state.h"
#include <cfloat>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <map>

action MinMaxSearch(state & s, const int depth);
float max_value(state & s, float alpha, float beta, const int depth);
float min_value(state & s, float alpha, float beta, const int depth);
int getHistory(const action & a);
std::map<action, int> historyTable;
bool winningMove;

struct ordering
{
  bool operator () (const action & lhs, const action & rhs) const
  {
    return getHistory(lhs) > getHistory(rhs);
  }
};

int getHistory(const action & a)
{
  auto it = historyTable.find(a);
  if(it == historyTable.end())
    return 0;
  else
    return it->second;
}

void addToHistory(const action & a)
{
  auto it = historyTable.find(a);
  if(it == historyTable.end())
  {
    historyTable[a] = 1;
  }
  else
  {
    it->second++;
  }
}

//limit is in seconds
action IDTLMMS(state & s, const long & limit)
{
  winningMove = false;
  int currentDepth = 1;
  action a;
  auto start = std::chrono::high_resolution_clock::now();
  long timeElapsed = 0;
  while(timeElapsed < limit && !winningMove)
  {
    std::cout << "DepthStart: " << currentDepth << std::endl;
    a = MinMaxSearch(s, currentDepth);
    std::cout << "Depthend: " << currentDepth << std::endl;
    currentDepth++;
    timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << timeElapsed << std::endl;
  }
  return a;
}

//Iterative deepening depth limited min max search
action IDDLMMS(state & s, const int & maxDepth)
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
  std::sort(allActions.begin(), allActions.end(), ordering());
  float bestActionScore = FLT_MAX * -1;
  action bestAction;
  for(const auto & a: allActions)
  {
    s.applyAction(a);
    auto value = min_value(s, alpha, beta, depth - 1);
    s.reverseAction(a);
    if(value > bestActionScore)
    {
      bestActionScore = value;
      bestAction = a;
      alpha = std::max(alpha, value);
    }
  }
  addToHistory(bestAction);
  return bestAction;
}

float max_value(state & s, float alpha, float beta, const int depth)
{
  if(depth == 0 || s.terminal())
  {
   return s.getValue();
  }
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
  std::sort(allActions.begin(), allActions.end(), ordering());
  float bestActionScore = FLT_MAX * -1;
  action bestAction;
  for(const auto & a: allActions)
  {
    s.applyAction(a);
    auto value = min_value(s, alpha, beta, depth - 1);
    s.reverseAction(a);
    if(value > bestActionScore)
    {
      bestActionScore = value;
      bestAction = a;
      if(value >= beta)
      {
        addToHistory(a);
        return value;
      }
      alpha = std::max(alpha, value);
    }
  }
  addToHistory(bestAction);
  return bestActionScore;
}

float min_value(state & s, float alpha, float beta, const int depth)
{
  if(depth == 0 || s.terminal())
  {
    return s.getValue();
  }
  auto allActions = s.possibleActionsE();
  if(allActions.size() == 0)
  {
    if(s.inCheck(s.m_enemyPieces))
    {
      winningMove = true;
      return 10000;
    }
    else//if they're not in check and there's no move its a draw
    {
      return 0;
    }
  }
  std::sort(allActions.begin(), allActions.end(), ordering());
  float bestActionScore = FLT_MAX;
  action bestAction;
  for(const auto & a: allActions)
  {
    s.applyAction(a);
    auto value = max_value(s, alpha, beta, depth - 1);
    s.reverseAction(a);
    if(value < bestActionScore)
    {
      bestActionScore = value;
      bestAction = a;
      if(value <= alpha)
      {
        addToHistory(a);
        return value;
      }
      beta = std::min(beta,value);
    }
  }
  addToHistory(bestAction);
  return bestActionScore;
}