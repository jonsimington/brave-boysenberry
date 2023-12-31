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

void bishop::possibleActions(const state & s, std::vector<action> & allActions) const
{
  diagonalMoves(this, s.m_board, allActions);
}

bishop* bishop::clone() const
{
  bishop* p = new bishop;
  p->copyValues(this);
  return p;
}

float bishop::getValue(const state & s) const
{
  return bishopValue;
}