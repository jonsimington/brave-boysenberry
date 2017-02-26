#pragma once
#include <set>
#include "board.h"
#include "tile.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
class state
{
  public:
    state();
  private:
    board m_board;
    std::set<piece> m_pieces;
};