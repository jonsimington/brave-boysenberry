#pragma once
#include <vector>
#include <string>
#include "mypiece.h"
#include "action.h"
#define rookValue 5
class rook: public mypiece
{
  public:
    rook();
    rook(const int & x, const int & y, const std::string & s, board & b, bool friendly, bool hasMoved);
    virtual void possibleActions(const int & px, const int & py, const bool cp, std::vector<action> & allActions) const;
    virtual rook* clone() const;
    virtual float getValue() const;
  private:
};