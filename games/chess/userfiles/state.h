#pragma once
#include "../game.hpp"
#include "../../../joueur/src/base_ai.hpp"
#include "board.h"
#include "action.h"
#include <vector>
#include <map>

class action;

class state
{
  public:
    std::vector<action> possibleActions() const;
    state();
    state(const state & rhs);
    state & operator = (const state & rhs);
    state & operator = (const cpp_client::chess::Game & g);
    state(const cpp_client::chess::Game & g);
    state operator + (const action & a) const;
  private:
    board m_board;
    std::map<std::string, mypiece> m_pieces;
};