#pragma once
#include "piece.h"

class piece;

class tile
{
  public:
    tile();
    void release();
    void move(piece & p);
    bool occupied() const;
  private:
    piece* m_piece;
};