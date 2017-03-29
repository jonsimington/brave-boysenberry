#include "queen.h"
#include "utility.h"
queen::queen()
{
  
}

queen::queen(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved): 
mypiece(x,y,id,b,friendly,hasMoved)
{
  m_type = "Queen";
}

queen* queen::clone() const
{
  queen* p = new queen;
  p->copyValues(this);
  return p;
}

void queen::possibleActions(const state & s, std::vector<action> & allActions) const
{
  diagonalMoves(this, s.m_board, allActions);
  straightMoves(this, s.m_board, allActions);
}

float queen::getValue() const
{
  return queenValue;
}