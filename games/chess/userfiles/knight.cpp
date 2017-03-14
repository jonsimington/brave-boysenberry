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

std::vector<action> knight::possibleActions(const int & px, const int & py, const bool cp) const
{
  std::vector<action> allActions;
  if(m_y + 2 < boardLength)
  {
    if(m_x + 1 < boardLength)
    {
      checkToPlace(this, *m_board, m_x + 1, m_y + 2, allActions);
    }
    if(m_x - 1 >= 0)
    {
      checkToPlace(this, *m_board, m_x - 1, m_y + 2, allActions);
    }
  }
  if(m_y - 2 >= 0)
  {
    if(m_x + 1 < boardLength)
    {
      checkToPlace(this, *m_board, m_x + 1, m_y - 2, allActions);
    }
    if(m_x - 1 >= 0)
    {
      checkToPlace(this, *m_board, m_x - 1, m_y - 2, allActions);
    }
  }
  if(m_x + 2 < boardLength)
  {
    if(m_y + 1 < boardLength)
    {
      checkToPlace(this, *m_board, m_x + 2, m_y + 1, allActions);
    }
    if(m_y - 1 >= 0)
    {
      checkToPlace(this, *m_board, m_x + 2, m_y - 1, allActions);
    }
  }
  if(m_x - 2 >= 0)
  {
    if(m_y + 1 < boardLength)
    {
      checkToPlace(this, *m_board, m_x - 2, m_y + 1, allActions);
    }
    if(m_y - 1 >= 0)
    {
      checkToPlace(this, *m_board, m_x - 2, m_y - 1, allActions);
    }
  }
  return allActions;
}

float knight::getValue() const
{
  return knightValue;
}