#pragma once
#include "tile.h"
#define boardLength 8
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
    void reset();
    void print() const;
  private:
    void create();
    tile** m_data;
    static int const m_length;
};