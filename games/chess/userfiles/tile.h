#pragma once
#include "mypiece.h"
class mypiece;
class board;

class tile
{
  public:
    tile();
    void release();
    void move(mypiece & p);
    bool occupied() const;
    const mypiece & getPiece() const;
  private:
    mypiece* m_mypiece;
};