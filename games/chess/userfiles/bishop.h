#pragma once
#include "mypiece.h"
#include "action.h"
#include <vector>
class bishop: public mypiece
{
  public:
    std::vector<action> possibleActions() const;
  private:
};