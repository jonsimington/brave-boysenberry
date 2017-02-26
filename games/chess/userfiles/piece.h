#pragma once
#include "board.h"
#include "tile.h"

class piece
{
  public:
    piece();
    peice(const int & x, const int & y);
    void place(const int & x, const int & y);
  private:
    int m_x;
    int m_y;
    //board<tile<piece> > m_board;
};