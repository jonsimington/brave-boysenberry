#pragma once
#include "action.h"
#include "mypiece.h"
#include <vector>
#include <string>
#define queenValue 9
class queen: public mypiece
{
  public:
    queen();
    queen(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved);
    virtual queen* clone() const;
    virtual void possibleActions(const state & s, std::vector<action> & allActions) const;
    virtual float getValue() const;
  private:
};