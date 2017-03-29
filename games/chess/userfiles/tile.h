#pragma once
#include "mypiece.h"

class tile
{
  public:
    tile();
    ~tile();
    void release();
    void move(mypiece & p);
    bool occupied() const;
    const mypiece & getPiece() const;
    mypiece* getPieceRef();
  private:
    mypiece* m_mypiece;
};