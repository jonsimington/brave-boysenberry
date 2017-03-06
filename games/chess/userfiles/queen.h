#pragma once
#include "action.h"
#include "mypiece.h"
#include <vector>
#include <string>
class queen: public mypiece
{
  public:
    queen();
    queen(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved);
    virtual queen* clone() const;
    virtual std::vector<action> possibleActions(const int & px, const int & py, const bool cp) const;
  private:
};