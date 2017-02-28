#pragma once
#include "tile.h"
#include "mypiece.h"
#define boardLength 8
class tile;
class mypiece;

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
    void create();
    tile** m_data;
    static int const m_length;
    friend mypiece;
};