#pragma once
#include"mypiece.h"
#include"action.h"
#include<vector>
class king: public mypiece
{
  public:
    king();
    virtual void possibleActions(const state & s, std::vector<action> & allActions) const;
    king(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved);
    virtual king* clone() const;
  private:
};