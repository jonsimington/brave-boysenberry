#pragma once
#include "piece.h"
#include "tile.h"
class piece;
class tile;

class board
{
  public:
    board();
    ~board();
    board(const board & rhs);
    const board & operator = (const board & rhs);
    board(board && rhs);
    const tile* operator [] (const int & i) const;
    tile* operator [] (const int & i);
  private:
    tile** m_data;
    static int const m_length;
    friend piece;
};