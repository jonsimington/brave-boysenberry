#pragma once
#include "utility.h"
#include <vector>
#include "queen.h"
#include "board.h"
#include "tile.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "king.h"
#include <map>
class state
{
  public:
    std::vector<action> possibleActions() const;
    state();
    state(const state & rhs);
    state & operator = (const state & rhs);
    state(const cpp_client::chess::Game & g);
    state operator + (const action & a) const;
  private:
    board m_board;
    std::map<std::string, mypiece> m_pieces;
};