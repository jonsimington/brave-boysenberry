#pragma once
#include "../game.hpp"
#include "mypiece.h"
#include "tile.h"
#define boardLength 8
class mypiece;
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
    int getLength() const;
  private:
    tile** m_data;
    static int const m_length;
    friend mypiece;
};