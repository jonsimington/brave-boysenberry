#pragma once
#include "mypiece.h"
#include "action.h"
#include <vector>
class bishop: public mypiece
{
  public:
    bishop(const int & x, const int & y);
    std::vector<action> possibleActions() const;
  private:
};