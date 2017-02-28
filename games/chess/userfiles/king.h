#pragma once
#include"mypiece.h"
class king: public mypiece
{
  public:
    std::vector<action> possibleActions() const;
    king(const int & x, const int & y, const std::string & s);
  private:
};