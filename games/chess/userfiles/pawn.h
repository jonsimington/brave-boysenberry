#pragma once
#include<vector>
#include<string>
#include "mypiece.h"
#include "action.h"
#define pawnValue 1
class pawn: public mypiece
{
  public:
    pawn();
    pawn(const int & x, const int & y, const bool direction, const std::string & id, board & b, bool friendly, bool hasMoved);
    virtual void possibleActions(const state & s, std::vector<action> & allActions) const;
    int lookAhead(const int & d) const;
    virtual pawn* clone() const;
    virtual int getDirection() const;
    virtual float getValue(const state & s) const;
    /*0 is forward 1 is backwards */
    bool m_direction;
};