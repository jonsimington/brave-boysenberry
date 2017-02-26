#pragma once
#include "board.h"
#include "tile.h"
#include "action.h"
#include "utility.h"
class board;

class piece
{
  public:
    piece();
    piece(const int & x, const int & y);
    void place(const int & x, const int & y);
    bool operator < (const piece & rhs) const;
    void move(const int & x, const int & y);
    void remove();
    int getX() const;
    int getY() const;
    int getId() const;
  protected:
    int m_x;
    int m_y;
    board* m_board;
    bool m_inUse;
    int m_id;
};