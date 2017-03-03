#include "queen.h"
#include "utility.h"
queen::queen()
{
  
}

queen::queen(const int & x, const int & y, const std::string & id, board & b, bool friendly): mypiece(x,y,id,b,friendly)
{
  m_type = "Queen";
}

queen* queen::clone() const
{
  queen* p = new queen;
  p->copyValues(this);
  return p;
}

std::vector<action> queen::possibleActions() const
{
  std::vector<action> allActions;
  //std::cout << m_x << ", " << m_y << std::endl;
  diagonalMoves(this, *m_board, allActions);
  straightMoves(this, *m_board, allActions);
  return allActions;
}