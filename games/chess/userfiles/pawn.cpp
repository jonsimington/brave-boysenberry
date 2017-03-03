#include "pawn.h"
#include "utility.h"
pawn::pawn()
{
  
}

pawn::pawn(const int & x, const int & y, const bool direction, const std::string & id, board & b, bool friendly, bool hasMoved):
mypiece(x,y,id,b,friendly, hasMoved)
{
  m_type = "Pawn";
  m_direction = direction;
}

std::vector<action> pawn::possibleActions() const
{
  bool aheadOccupied;
  std::vector<action> allActions;
  int x = m_x - 1;
  int y = lookAhead(1);
  if(!(*m_board)[m_x][y].occupied())
  {
    allActions.push_back(action(*this, m_x, y));
    aheadOccupied = false;
  }
  else
    aheadOccupied = true;
  if(inBounds(x) && (*m_board)[x][y].occupied() && (*m_board)[x][y].getPiece().isFriendly() != m_friendly)
    allActions.push_back(action(*this, (*m_board)[x][y].getPiece()));
  x = m_x + 1;
  if(inBounds(x) && (*m_board)[x][y].occupied() && (*m_board)[x][y].getPiece().isFriendly() != m_friendly)
    allActions.push_back(action(*this, (*m_board)[x][y].getPiece()));
  if(!aheadOccupied && !m_hasMoved)
  {
    y = lookAhead(2);
    if(!(*m_board)[m_x][y].occupied())
      allActions.push_back(action(*this, m_x, y));
  }
  return allActions;
}

int pawn::lookAhead(const int & d) const
{
  int m;
  if(m_direction == 1)
    m = -1;
  else
    m = 1;
  return m_y + d * m;
}

pawn* pawn::clone() const
{
  pawn* p = new pawn;
  p->copyValues(this);
  p->m_direction = m_direction;
  return p;
}
