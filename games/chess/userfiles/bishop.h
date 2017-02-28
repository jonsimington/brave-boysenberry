#pragma once
#include "mypiece.h"
#include "action.h"
#include <vector>
#include <string>
class bishop: public mypiece
{
  public:
    bishop(const int & x, const int & y, const std::string & s);
    std::vector<action> possibleActions() const;
  private:
};