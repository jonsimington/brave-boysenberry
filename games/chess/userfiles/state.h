#pragma once
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
    board<tile<piece> > m_board;
};