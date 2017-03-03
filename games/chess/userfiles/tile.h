#pragma once
#include "mypiece.h"
class mypiece;
class tile
{
  public:
    tile();
    ~tile();
    void release();
    void move(mypiece & p);
    bool occupied() const;
    const mypiece & getPiece() const;
  private:
    mypiece* m_mypiece;
};