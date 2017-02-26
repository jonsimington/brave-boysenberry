#pragma once
#include "piece.h"

class piece;

class tile
{
  public:
    tile();
    void release();
    void add(piece & p);//needs more work
  private:
    piece* m_piece;
};