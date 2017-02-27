#include "rook.h"
#include "board.h"
std::vector<action> rook::possibleActions() const
{
  std::vector<action> allActions;
  int i;
  for(i = m_x + 1; i < boardLength; i++) //checking x value to the right
  {
    if((*m_board)[i][m_y].occupied())
    {
      allActions.push_back(action(*this, (*m_board)[i][m_y].getPiece()));
      break;
    }
    else
      allActions.push_back(action(*this, i, m_y));
  }
  //checking x value to the left
  for(i = m_x - 1; i >= 0; i--)
  {
    if((*m_board)[i][m_y].occupied())
    {
      allActions.push_back(action(*this, (*m_board)[i][m_y].getPiece()));
      break;
    }
    else
      allActions.push_back(action(*this, i, m_y));
  }
  
  for(i = m_y + 1; i < boardLength; i++)
  {
    if((*m_board)[m_x][i].occupied())
    {
      allActions.push_back(action(*this, (*m_board)[m_x][i].getPiece()));
      break;
    }
    else
      allActions.push_back(action(*this, m_x, i));
  }
  for(i = m_y - 1; i >= 0; i--)
  {
    if((*m_board)[m_x][i].occupied())
    {
      allActions.push_back(action(*this, (*m_board)[m_x][i].getPiece()));
      break;
    }
    else
      allActions.push_back(action(*this, m_x, i));
  }
  return allActions;
}