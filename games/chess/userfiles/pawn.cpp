#include "pawn.h"

pawn::pawn(const int & x, const int & y, const bool direction)
{
  piece(x,y);
  m_direction = true;
}

std::vector<action> pawn::possibleActions() const
{
  std::vector<action> allActions;
  int y = m_y - 1;
  int x = lookAhead(1);
  if(!(*m_board)[x][m_y].occupied())
    allActions.push_back(action(m_id, m_x, m_y, x, m_y));
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