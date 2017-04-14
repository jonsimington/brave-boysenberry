#include "knight.h"
#include "utility.h"

knight::knight()
{
  
}

knight::knight(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved): 
mypiece(x,y,id,b,friendly, hasMoved)
{
  m_type = "Knight";
}

knight* knight::clone() const
{
  knight* p = new knight;
  p->copyValues(this);
  return p;
}

void knight::possibleActions(const state & s, std::vector<action> & allActions) const
{
  if(m_y + 2 < boardLength)
  {
    if(m_x + 1 < boardLength)
    {
      checkToPlace(this, s.m_board, m_x + 1, m_y + 2, allActions);
    }
    if(m_x - 1 >= 0)
    {
      checkToPlace(this, s.m_board, m_x - 1, m_y + 2, allActions);
    }
  }
  if(m_y - 2 >= 0)
  {
    if(m_x + 1 < boardLength)
    {
      checkToPlace(this, s.m_board, m_x + 1, m_y - 2, allActions);
    }
    if(m_x - 1 >= 0)
    {
      checkToPlace(this, s.m_board, m_x - 1, m_y - 2, allActions);
    }
  }
  if(m_x + 2 < boardLength)
  {
    if(m_y + 1 < boardLength)
    {
      checkToPlace(this, s.m_board, m_x + 2, m_y + 1, allActions);
    }
    if(m_y - 1 >= 0)
    {
      checkToPlace(this, s.m_board, m_x + 2, m_y - 1, allActions);
    }
  }
  if(m_x - 2 >= 0)
  {
    if(m_y + 1 < boardLength)
    {
      checkToPlace(this, s.m_board, m_x - 2, m_y + 1, allActions);
    }
    if(m_y - 1 >= 0)
    {
      checkToPlace(this, s.m_board, m_x - 2, m_y - 1, allActions);
    }
  }
}

float knight::getValue(const state & s) const
{
  return knightValue;
}