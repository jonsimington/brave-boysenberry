#pragma once
#include <vector>
#include "mypiece.h"
#include "action.h"
class rook: public mypiece
{
  public:
    rook(const int & x, const int & y);
    std::vector<action> possibleActions() const;
  private:
};