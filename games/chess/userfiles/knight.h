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
    virtual void possibleActions(const int & px, const int & py, const bool cp, std::vector<action> & allActions) const;
    virtual float getValue() const;
  private:
};