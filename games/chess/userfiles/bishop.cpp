#include "bishop.h"

bishop::bishop(const int & x, const int & y)
{
  mypiece(x,y);
}

std::vector<action> bishop::possibleActions() const
{
  std::vector<action> allActions;
  int x, y;
  for(x = m_x + 1, y = m_y + 1; x < boardLength && y < boardLength; x++, y++) //top right
  {
    if((*m_board)[x][y].occupied())
    {
      allActions.push_back(action(*this, (*m_board)[x][y].getPiece()));
      break;
    }
    else
      allActions.push_back(action(*this, x, y));
  }
  for(x = m_x - 1, y = m_y + 1; x >= 0 && y < boardLength; x--, y++) //top left
  {
    if((*m_board)[x][y].occupied())
    {
      allActions.push_back(action(*this, (*m_board)[x][y].getPiece()));
      break;
    }
    else
      allActions.push_back(action(*this, x, y));
  }
  for(x = m_x - 1, y = m_y - 1; x >= 0 && y >= 0; x--, y--) //top left
  {
    if((*m_board)[x][y].occupied())
    {
      allActions.push_back(action(*this, (*m_board)[x][y].getPiece()));
      break;
    }
    else
      allActions.push_back(action(*this, x, y));
  }
  for(x = m_x + 1, y = m_y - 1; x < boardLength && y >= 0; x++, y--) //top left
  {
    if((*m_board)[x][y].occupied())
    {
      allActions.push_back(action(*this, (*m_board)[x][y].getPiece()));
      break;
    }
    else
      allActions.push_back(action(*this, x, y));
  }
  
  return allActions;
}