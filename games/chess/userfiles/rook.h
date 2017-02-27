#pragma once
#include <vector>
#include "mypiece.h"
#include "action.h"
class rook: public mypiece
{
  public:
    std::vector<action> possibleActions() const;
  private:
};