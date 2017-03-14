#pragma once
#include "action.h"
#include "mypiece.h"
#include <vector>
#include <string>
#define queenValue 9
class queen: public mypiece
{
  public:
    queen();
    queen(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved);
    virtual queen* clone() const;
    virtual std::vector<action> possibleActions(const int & px, const int & py, const bool cp) const;
    virtual float getValue() const;
  private:
};