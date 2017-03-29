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

void pawn::possibleActions(const state & s, std::vector<action> & allActions) const
{
  const board & theBoard = s.m_board;
  bool aheadOccupied;
  int x = m_x - 1;
  int y = lookAhead(1);
  if(!theBoard[m_x][y].occupied())
  {
    if(y == 0 || y == boardLength - 1)
    {
      for(auto t: upgrade_types)
      {
        allActions.push_back(action(*this, m_x, y, t));
      }
    }
    else
    {
      allActions.push_back(action(*this, m_x, y));
      aheadOccupied = false;
    }
  }
  else
  {
    aheadOccupied = true;
  }
  if(x >= 0 && theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != m_friendly)
  {
    if(y == 0 || y == boardLength - 1)
    {
      for(auto t: upgrade_types)
      {
        allActions.push_back(action(*this, theBoard[x][y].getPiece(), t));
      }
    }
    else
    {
      allActions.push_back(action(*this, theBoard[x][y].getPiece()));
    }
  }
  x = m_x + 1;
  if(x < boardLength && theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != m_friendly)
  {
    if(y == 0 || y == boardLength - 1)
    {
      for(auto t: upgrade_types)
      {
        allActions.push_back(action(*this, theBoard[x][y].getPiece(), t));
      }
    }
    else
    {
      allActions.push_back(action(*this, theBoard[x][y].getPiece()));
    }
  }
  if(s.can_EnPassant && m_x - 1 >= 0 && s.px == m_x - 1 && s.py == y && theBoard[m_x - 1][m_y].occupied() && theBoard[m_x - 1][m_y].getPiece().isFriendly() != m_friendly)
  {
    allActions.push_back(action(*this, theBoard[m_x - 1][m_y].getPiece(), 1));  
  }
  if(s.can_EnPassant && m_x + 1 < boardLength &&  s.px == m_x + 1 && s.py == y && theBoard[m_x + 1][m_y].occupied() && theBoard[m_x + 1][m_y].getPiece().isFriendly() != m_friendly)
  {
    allActions.push_back(action(*this, theBoard[m_x + 1][m_y].getPiece(), 1));  
  }
  if(!aheadOccupied && !m_hasMoved)
  {
    y = lookAhead(2);
    if(!theBoard[m_x][y].occupied())
    {
      allActions.push_back(action(*this, m_x, y));
    }
  }
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

int pawn::getDirection() const
{
  return m_direction;
}

float pawn::getValue() const
{
  return pawnValue;
}