#pragma once
#include"mypiece.h"
class king: public mypiece
{
  public:
    std::vector<action> possibleActions() const;
  private:
};