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

std::vector<action> rook::possibleActions() const
{
  std::vector<action> allActions;
  straightMoves(this, *m_board, allActions);
  return allActions;
}

rook* rook::clone() const
{
  rook* p = new rook;
  p->copyValues(this);
  return p;
}