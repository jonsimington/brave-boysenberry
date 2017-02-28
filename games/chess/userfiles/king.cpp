#include "king.h"
king::king(const int & x, const int & y, const std::string & s)
{
  mypiece(x,y,s);
}

std::vector<action> king::possibleActions() const
{
  std::vector<action> allActions;
  return allActions;
}