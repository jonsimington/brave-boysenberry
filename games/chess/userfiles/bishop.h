#pragma once
#include "mypiece.h"
#include "action.h"
#include <vector>
#include <string>
class bishop: public mypiece
{
  public:
    bishop();
    bishop(const int & x, const int & y, const std::string & id);
    bishop(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved);
    virtual std::vector<action> possibleActions() const;
    virtual bishop* clone() const;
  private:
};