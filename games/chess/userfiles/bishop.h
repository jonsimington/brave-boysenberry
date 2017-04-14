#pragma once
#include "mypiece.h"
#include "action.h"
#include <vector>
#include <string>
#define bishopValue 3
class bishop: public mypiece
{
  public:
    bishop();
    bishop(const int & x, const int & y, const std::string & id);
    bishop(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved);
    virtual void possibleActions(const state & s, std::vector<action> & allActions) const;
    virtual bishop* clone() const;
    virtual float getValue(const state & s) const;
  private:
};