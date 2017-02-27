#include "pawn.h"

pawn::pawn(const int & x, const int & y, const bool direction)
{
  mypiece(x,y);
  m_direction = true;
}

std::vector<action> pawn::possibleActions() const
{
  bool aheadOccupied;
  std::vector<action> allActions;
  int x = m_x - 1;
  int y = lookAhead(1);
  if(!(*m_board)[m_x][y].occupied())
  {
    allActions.push_back(action(*this, x, m_y));
    aheadOccupied = false;
  }
  else
    aheadOccupied = true;
  if(inBounds(x) & (*m_board)[x][y].occupied())
    allActions.push_back(action(*this, (*m_board)[x][y].getPiece()));
  x = m_x + 1;
  if(inBounds(x) & (*m_board)[x][y].occupied())
    allActions.push_back(action(*this, (*m_board)[x][y].getPiece()));
  if(!aheadOccupied && ((!m_direction && m_y == 1) || (m_direction && m_y == boardLength - 2)))
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
  if(m_direction)
    m = -1;
  else
    m = 1;
  return m_x + d * m;
}
