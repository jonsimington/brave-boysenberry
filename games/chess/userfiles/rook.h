#pragma once
#include <vector>
#include <string>
#include "mypiece.h"
#include "action.h"
class rook: public mypiece
{
  public:
    rook(const int & x, const int & y, const std::string & id);
    std::vector<action> possibleActions() const;
  private:
};