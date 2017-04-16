#pragma once
#include "state.h"
#include "transtable.h"
#include "historytable.h"
#include "quiescence.h"
#include <cfloat>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <cmath>

action MinMaxSearch(state & s, const int depth, const int qdepth);
float max_value(state & s, float alpha, float beta, const int depth, const int qdepth);
float min_value(state & s, float alpha, float beta, const int depth, const int qdepth);
float min_valueP(state & s, float alpha, float beta, const int depth, const int qdepth);
float max_valueP(state & s, float alpha, float beta, const int depth, const int qdepth);

bool MYTURN;

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
    a = MinMaxSearch(s, currentDepth, 2);
    std::cout << "Depthend: " << currentDepth << std::endl;
    currentDepth++;
    timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << timeElapsed << std::endl;
  }
  if(counter >= 5)
  {
    clearHistoryTable();
    counter = 0;
  }
  else
  {
    counter++;
  }
  return a;
}

//Minmax search of set depth
action MinMaxSearch(state & s, const int depth, const int qdepth)
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
    auto value = min_value(s, alpha, beta, depth - 1, qdepth);
    s.reverseAction(a);
    if(value > bestActionScore)
    {
      bestActionScore = value;
      bestAction = a;
      alpha = std::max(alpha, value);
    }
  }
  addToHistory(bestAction, depth);
  addEntry(s, true, depth, bestActionScore, false);
  return bestAction;
}

float max_value(state & s, float alpha, float beta, const int depth, const int qdepth)
{
  //std::cout << "max\n";
  float bestActionScore = FLT_MAX * -1;
  bool isPrune;
  float score;
  if(check(s, true, depth, score, isPrune))
  {
    if(!isPrune)
    {
      return score;
    }
    else
    {
      //bestActionScore = score;
      alpha = score;
    }
  }
  if((depth == 0 && (isQuiescent(s) || qdepth == 0)) || s.isDraw())
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
  action bestAction;
  float value;
  for(const auto & a: allActions)
  {
    s.applyAction(a);
    if(depth != 0)
      value = min_value(s, alpha, beta, depth - 1, qdepth);
    else
      value = min_value(s, alpha, beta, depth, qdepth - 1);
    s.reverseAction(a);
    if(value > bestActionScore)
    {
      bestActionScore = value;
      bestAction = a;
      if(value >= beta)
      {
        addToHistory(bestAction, depth);
        addEntry(s, true, depth, bestActionScore, true);
        return value;
      }
      alpha = std::max(alpha, value);
    }
  }
  addToHistory(bestAction, depth);
  addEntry(s, true, depth, bestActionScore, false);
  //std::cout << "end max\n";
  return bestActionScore;
}

float min_value(state & s, float alpha, float beta, const int depth, const int qdepth)
{
  //std::cout << "min\n";
  float bestActionScore = FLT_MAX;
  bool isPrune;
  float score;
  if(check(s, false, depth, score, isPrune))
  {
    if(!isPrune)
    {
      return score;
    }
    else
    {
      //bestActionScore = score;
      beta = score;
    }
  }
  if((depth == 0 && (isQuiescent(s) || qdepth == 0)) || s.isDraw())
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
  action bestAction;
  float value;
  for(const auto & a: allActions)
  {
    s.applyAction(a);
    if(depth != 0)
      value = max_value(s, alpha, beta, depth - 1, qdepth);
    else
      value = max_value(s, alpha, beta, depth, qdepth - 1);
    s.reverseAction(a);
    if(value < bestActionScore)
    {
      bestActionScore = value;
      bestAction = a;
      if(value <= alpha)
      {
        addToHistory(bestAction, depth);
        addEntry(s, false, depth, bestActionScore, true);
        return value;
      }
      beta = std::min(beta,value);
    }
  }
  addToHistory(bestAction, depth);
  addEntry(s, false, depth, bestActionScore, false);
  //std::cout << "end min\n";
  return bestActionScore;
}

void pondering(const state & s)
{
  state tempState = s;
  int currentDepth = 1;
  float alpha = FLT_MAX * -1;
  float beta = FLT_MAX;
  try
  {
    while(true)
    {
      std::cout << "is pondering: " << currentDepth << std::endl;
      min_valueP(tempState, alpha, beta, currentDepth, 2);
      currentDepth++;
    }
  }
  catch(int i)
  {
    
  }
}

float max_valueP(state & s, float alpha, float beta, const int depth, const int qdepth)
{
  //std::cout << "max\n";
  if(MYTURN)
    throw 0;
  float bestActionScore = FLT_MAX * -1;
  bool isPrune;
  float score;
  if(check(s, true, depth, score, isPrune))
  {
    if(!isPrune)
    {
      return score;
    }
    else
    {
      //bestActionScore = score;
      alpha = score;
    }
  }
  if((depth == 0 && (isQuiescent(s) || qdepth == 0)) || s.isDraw())
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
  action bestAction;
  float value;
  for(const auto & a: allActions)
  {
    s.applyAction(a);
    if(depth != 0)
      value = min_valueP(s, alpha, beta, depth - 1, qdepth);
    else
      value = min_valueP(s, alpha, beta, depth, qdepth - 1);
    s.reverseAction(a);
    if(value > bestActionScore)
    {
      bestActionScore = value;
      bestAction = a;
      if(value >= beta)
      {
        addToHistory(bestAction, depth);
        addEntry(s, true, depth, bestActionScore, true);
        return value;
      }
      alpha = std::max(alpha, value);
    }
  }
  addToHistory(bestAction, depth);
  addEntry(s, true, depth, bestActionScore, false);
  //std::cout << "end max\n";
  return bestActionScore;
}

float min_valueP(state & s, float alpha, float beta, const int depth, const int qdepth)
{
  //std::cout << "min\n";
  if(MYTURN)
    throw 0;
  float bestActionScore = FLT_MAX;
  bool isPrune;
  float score;
  if(check(s, false, depth, score, isPrune))
  {
    if(!isPrune)
    {
      return score;
    }
    else
    {
      //bestActionScore = score;
      beta = score;
    }
  }
  if((depth == 0 && (isQuiescent(s) || qdepth == 0)) || s.isDraw())
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
  action bestAction;
  float value;
  for(const auto & a: allActions)
  {
    s.applyAction(a);
    if(depth != 0)
      value = max_valueP(s, alpha, beta, depth - 1, qdepth);
    else
      value = max_valueP(s, alpha, beta, depth, qdepth - 1);
    s.reverseAction(a);
    if(value < bestActionScore)
    {
      bestActionScore = value;
      bestAction = a;
      if(value <= alpha)
      {
        addToHistory(bestAction, depth);
        addEntry(s, false, depth, bestActionScore, true);
        return value;
      }
      beta = std::min(beta,value);
    }
  }
  addToHistory(bestAction, depth);
  addEntry(s, false, depth, bestActionScore, false);
  //std::cout << "end min\n";
  return bestActionScore;
}