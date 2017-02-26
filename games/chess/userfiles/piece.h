#pragma once
#include "utility.h"
#include "board.h"
#include "tile.h"
class board;

class piece
{
  public:
    piece();
    peice(const int & x, const int & y);
    void place(const int & x, const int & y);
    bool operator < (const piece & rhs) const;
  private:
    void move(const int & x, const int & y);
    int m_x;
    int m_y;
    board* m_board;
};