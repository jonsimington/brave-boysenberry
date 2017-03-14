#pragma once
#include "mypiece.h"
#include "action.h"
#include <vector>
#define knightValue 3
class knight: public mypiece
{
  public:
    knight();
    knight(const int & x, const int & y, const std::string & id, board & b,bool friendly,bool hasMoved);
    virtual knight* clone() const;
    virtual std::vector<action> possibleActions(const int & px, const int & py, const bool cp) const;
    virtual float getValue() const;
  private:
};