#pragma once
#include "state.h"
#include <string>
#include <cfloat>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <map>
#include <unordered_map>

action MinMaxSearch(state & s, const int depth);
float max_value(state & s, float alpha, float beta, const int depth);
float min_value(state & s, float alpha, float beta, const int depth);
int getHistory(const action & a);
/*
struct myHash
{
  unsigned long operator() (const action & a) const
  {
    unsigned long h1 = std::hash<std::string>()(a.m_id);
    unsigned long h2 = a.m_sx + (a.m_sy << 3) + (a.m_ex << 6) + (a.m_ey << 9);
    return h1 ^ h2;
  }
};
*/
unsigned int historyTable[64][64] = {0};
int MAX_DEPTH;

struct ordering
{
  bool operator () (const action & lhs, const action & rhs) const
  {
    return getHistory(lhs) > getHistory(rhs);
  }
};

int getHistory(const action & a)
{
  return historyTable[a.getHashFrom()][a.getHashTo()];
}

void addToHistory(const action & a, const int & depth)
{
  historyTable[a.getHashFrom()][a.getHashTo()] += depth * depth;
}

//limit is in seconds
action IDTLMMS(state & s, const long & limit)
{
  static int counter = 0;
  int currentDepth = 1;
  action a;
  auto start = std::chrono::high_resolution_clock::now();
  long timeElapsed = 0;
  while(timeElapsed < limit)
  {
    std::cout << "DepthStart: " << currentDepth << std::endl;
    MAX_DEPTH = currentDepth;
    a = MinMaxSearch(s, currentDepth);
    std::cout << "Depthend: " << currentDepth << std::endl;
    currentDepth++;
    timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << timeElapsed << std::endl;
  }
  if(counter >= 5)
  {
    for(int i = 0; i < 64; i++)
    {
      for(int j = 0; j < 64; j++)
      {
        historyTable[i][j] = 0;
      }
    }
    counter = 0;
  }
  else
  {
    counter++;
  }
  return a;
}

//Minmax search of set depth
action MinMaxSearch(state & s, const int depth)
{
  /*contains actions that have the same hueristic value
  one random one is returned at the end of the function*/
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
  return bestAction;
}

float max_value(state & s, float alpha, float beta, const int depth)
{
  if(depth == 0 || s.isDraw())
  {
   return s.getValue();
  }
  auto allActions = s.possibleActionsF();
  if(allActions.size() == 0)
  {
    if(s.inCheck(true))
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
        addToHistory(bestAction, MAX_DEPTH - depth);
        return value;
      }
      alpha = std::max(alpha, value);
    }
  }
  addToHistory(bestAction, MAX_DEPTH - depth);
  return bestActionScore;
}

float min_value(state & s, float alpha, float beta, const int depth)
{
  if(depth == 0 || s.isDraw())
  {
    return s.getValue();
  }
  auto allActions = s.possibleActionsE();
  if(allActions.size() == 0)
  {
    if(s.inCheck(false))
    {
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
        addToHistory(bestAction, MAX_DEPTH - depth);
        return value;
      }
      beta = std::min(beta,value);
    }
  }
  addToHistory(bestAction, MAX_DEPTH - depth);
  return bestActionScore;
}