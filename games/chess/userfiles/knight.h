#pragma once
#include "mypiece.h"
#include "action.h"
#include <vector>
class knight: public mypiece
{
  public:
    knight();
    knight(const int & x, const int & y, const std::string & id, board & b,bool friendly,bool hasMoved);
    virtual knight* clone() const;
    virtual std::vector<action> possibleActions() const;
  private:
};