#pragma once
#include "board.h"
#include "tile.h"
#include "action.h"
#include "utility.h"
class board;

class mypiece
{
  public:
    mypiece();
    mypiece(const int & x, const int & y);
    void place(const int & x, const int & y);
    bool operator < (const mypiece & rhs) const;
    void move(const int & x, const int & y);
    void remove();
    int getX() const;
    int getY() const;
    std::string getId() const;
  protected:
    friend class state;
    int m_x;
    int m_y;
    board* m_board;
    bool m_inUse;
    std::string m_id;
    bool m_hasMoved;
};