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

std::vector<action> queen::possibleActions(const int & px, const int & py, const bool cp) const
{
  std::vector<action> allActions;
  diagonalMoves(this, *m_board, allActions);
  straightMoves(this, *m_board, allActions);
  return allActions;
}

float queen::getValue() const
{
  return queenValue;
}