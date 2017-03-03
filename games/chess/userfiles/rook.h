#pragma once
#include <vector>
#include <string>
#include "mypiece.h"
#include "action.h"
class rook: public mypiece
{
  public:
    rook();
    rook(const int & x, const int & y, const std::string & s, board & b, bool friendly);
    virtual std::vector<action> possibleActions() const;
    virtual rook* clone() const;
  private:
};