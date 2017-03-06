#include "bishop.h"
#include "utility.h"

bishop::bishop()
{
  
}

bishop::bishop(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved): 
mypiece(x,y,id,b,friendly,hasMoved)
{
  m_type = "Bishop";
}

bishop::bishop(const int & x, const int & y, const std::string & id): mypiece(x,y,id)
{
  
}

std::vector<action> bishop::possibleActions(const int & px, const int & py, const bool cp) const
{
  std::vector<action> allActions;
  diagonalMoves(this, *m_board, allActions);
  return allActions;
}

bishop* bishop::clone() const
{
  bishop* p = new bishop;
  p->copyValues(this);
  return p;
}