#include "king.h"
#include "utility.h"
king::king()
{
  
}

king::king(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved): 
mypiece(x,y,id,b,friendly, hasMoved)
{
  m_type = "King";
}

void king::possibleActions(const int & px, const int & py, const bool cp, std::vector<action> & allActions) const
{
  if(m_y + 1 < boardLength)
  {
    checkToPlace(this,*m_board, m_x, m_y + 1,allActions);
    if(m_x + 1 < boardLength)
    {
      checkToPlace(this,*m_board, m_x + 1, m_y + 1,allActions);
    }
    if(m_x - 1 >= 0)
    {
      checkToPlace(this,*m_board, m_x - 1, m_y + 1,allActions);
    }
  }
  if(m_y - 1 >= 0)
  {
    checkToPlace(this,*m_board, m_x, m_y - 1,allActions);
    if(m_x + 1 < boardLength)
    {
      checkToPlace(this,*m_board, m_x + 1, m_y - 1,allActions);
    }
    if(m_x - 1 >= 0)
    {
      checkToPlace(this,*m_board, m_x - 1, m_y - 1,allActions);
    }
  }
  if(m_x + 1 < boardLength)
  {
    checkToPlace(this,*m_board, m_x + 1, m_y, allActions);
  }
  if(m_x - 1 >= 0)
  {
    checkToPlace(this,*m_board, m_x - 1, m_y, allActions);
  }
  if(!m_hasMoved && !in_check && (*m_board)[0][m_y].occupied() && (*m_board)[0][m_y].getPiece().getType() == "Rook" && 
     !(*m_board)[0][m_y].getPiece().m_hasMoved && isClearHorizontalA(m_x - 2, m_x - 1, m_y, *m_board, m_friendly) && isClearHorizontal(1, m_x - 1, m_y, *m_board))
  {
    allActions.push_back(action(*this, m_x - 2, m_y));
  }
  if(!m_hasMoved && !in_check && (*m_board)[boardLength - 1][m_y].occupied() && (*m_board)[boardLength - 1][m_y].getPiece().getType() == "Rook" && 
     !(*m_board)[boardLength - 1][m_y].getPiece().m_hasMoved && isClearHorizontalA(m_x + 1, m_x + 2, m_y, *m_board, m_friendly) && isClearHorizontal(m_x + 1, boardLength - 2, m_y, *m_board))
  {
    allActions.push_back(action(*this, m_x + 2, m_y));
  }
}

king* king::clone() const
{
  king* p = new king;
  p->copyValues(this);
  return p;
}