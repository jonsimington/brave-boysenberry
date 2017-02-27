#pragma once
#include <set>
#include "board.h"
#include "tile.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "../game.hpp"
class state
{
  public:
    state();
  private:
    board m_board;
    //friendly mypieces
    std::set<mypiece> m_fp;
    //enemy mypieces
    std::set<mypiece> m_ep;
};