#pragma once
#define myAI "Joshua Zygmunt"
#include <string>
#include <vector>
#include "action.h"
#include "../game.hpp"
#include "../../../joueur/src/base_ai.hpp"
#include "../player.hpp"
struct action;

template <typename T>
std::vector<T> operator + (const std::vector<T> & lhs, const std::vector<T> & rhs)
{
  std::vector<T> result = lhs;
  for(int i = 0; i < rhs.size(); i++)
    result.push_back(rhs[i]);
  return result;
}

template <typename T>
std::vector<T> & operator += (std::vector<T> & lhs, const std::vector<T> & rhs)
{
  for(int i = 0; i < rhs.size(); i++)
    lhs.push_back(rhs[i]);
  return lhs;
}

int fileToInt(const char f);
int fileToInt(const std::string & f);
bool inBounds(const int & i);
std::string intToFile(const int & i);
void modifyGame(cpp_client::chess::Player & player, const action & a);