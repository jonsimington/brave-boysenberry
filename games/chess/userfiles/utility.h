#pragma once
#define myAI "Joshua Zygmunt"
#include <string>
#include <vector>
#include "action.h"
#include "state.h"
#include "../game.hpp"
#include "../../../joueur/src/base_ai.hpp"
#include "../player.hpp"
struct action;
class state;
class board;

static std::vector<std::string> upgrade_types = {"Queen", "Bishop", "Rook", "Knight"};
static bool in_check = false;

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
bool checkToPlace(const mypiece* p, const board & theBoard, const int & x, const int & y, std::vector<action> & actions);
void diagonalMoves(const mypiece* p, const board & theBoard, std::vector<action> & allActions);
void straightMoves(const mypiece* p, const board & theBoard, std::vector<action> & allActions);
mypiece* changeType(state & s, mypiece* p, const std::string & typeTo);
bool isClearHorizontalA(const int & x1, const int & x2, const int & y, const board & theBoard, bool friendly);
bool isClearHorizontal(const int & x1, const int & x2, const int & y, const board & theBoard);
bool isUnderAttack(const mypiece & p, const board & theBoard);