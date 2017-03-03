#pragma once
#include "../game.hpp"
#include "../../../joueur/src/base_ai.hpp"
#include "board.h"
#include <vector>
#include <map>
#include "utility.h"
class action;
class mypiece;
class board;

class state
{
  public:
    std::vector<action> possibleActionsF() const;
    std::vector<action> possibleActionsE() const;
    state();
    ~state();
    state(const state & rhs);
    state & operator = (const state & rhs);
    state & operator = (const cpp_client::chess::Game & g);
    state(const cpp_client::chess::Game & g);
    state operator + (const action & a) const;
    void deleteData();
    
    std::string m_id;
    board m_board;
    std::vector<mypiece*> m_friendlyPieces;
    std::vector<mypiece*> m_enemyPieces;
    std::map<std::string, mypiece*> m_pieces;
};