#include "rook.h"
#include "utility.h"
rook::rook()
{
  
}

rook::rook(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved): 
mypiece(x,y,id,b,friendly,hasMoved)
{
  m_type = "Rook";
}

void rook::possibleActions(const state & s, std::vector<action> & allActions) const
{
  straightMoves(this, s.m_board, allActions);
}

rook* rook::clone() const
{
  rook* p = new rook;
  p->copyValues(this);
  return p;
}

float rook::getValue(const state & s) const
{
  return rookValue;
}