#pragma once
#include<vector>
#include<string>
#include "mypiece.h"
#include "action.h"
class pawn: public mypiece
{
  public:
    pawn();
    pawn(const int & x, const int & y, const bool direction, const std::string & id, board & b, bool friendly, bool hasMoved);
    virtual std::vector<action> possibleActions(const int & px, const int & py, const bool cp) const;
    int lookAhead(const int & d) const;
    virtual pawn* clone() const;
    virtual int getDirection() const;
  private:
    /*0 is forward 1 is backwards */
    bool m_direction;
};