#pragma once
#include<vector>
#include "mypiece.h"
class pawn: public mypiece
{
  public:
    pawn(const int & x, const int & y, const bool direction, const std::string & id);
    std::vector<action> possibleActions() const;
    int lookAhead(const int & d) const;
  private:
    /*0 is forward 1 is backwards */
    bool m_direction;
};