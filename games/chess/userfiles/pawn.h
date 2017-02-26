#pragma once
#include<vector>
#include "piece.h"
class pawn: public piece
{
  public:
    pawn(const int & x, const int & y, const bool direction);
    std::vector<action> possibleActions() const;
    int lookAhead(const int & d) const;
  private:
    /*0 is forward 1 is backwards */
    bool m_direction;
};