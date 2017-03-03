#include "king.h"
#include "utility.h"
king::king()
{
  
}

king::king(const int & x, const int & y, const std::string & id, board & b, bool friendly): mypiece(x,y,id,b,friendly)
{
  m_type = "King";
}

std::vector<action> king::possibleActions() const
{
  std::vector<action> allActions;
  if(inBounds(m_y + 1))
  {
    if(inBounds(m_x + 1))
    {
      checkToPlace(this,*m_board, m_x + 1, m_y + 1,allActions);
    }
    if(inBounds(m_x - 1))
    {
      checkToPlace(this,*m_board, m_x - 1, m_y + 1,allActions);
    }
  }
  if(inBounds(m_y - 1))
  {
    checkToPlace(this,*m_board, m_x, m_y - 1,allActions);
    if(inBounds(m_x + 1))
    {
      checkToPlace(this,*m_board, m_x + 1, m_y - 1,allActions);
    }
    if(inBounds(m_x - 1))
    {
      checkToPlace(this,*m_board, m_x - 1, m_y - 1,allActions);
    }
  }
  if(inBounds(m_x + 1))
  {
    checkToPlace(this,*m_board, m_x + 1, m_y, allActions);
  }
  if(inBounds(m_x - 1))
  {
    checkToPlace(this,*m_board, m_x - 1, m_y, allActions);
  }
  return allActions;
}

king* king::clone() const
{
  king* p = new king;
  p->copyValues(this);
  return p;
}