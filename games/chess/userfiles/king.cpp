#include "king.h"
#include "utility.h"
king::king(const int & x, const int & y, const std::string & s)
{
  mypiece(x,y,s);
}

std::vector<action> king::possibleActions() const
{
  std::vector<action> allActions;
  if(inBounds(m_y + 1))
  {
    if((*m_board)[m_x][m_y + 1].occupied())
      allActions.push_back(action(*this, m_x, m_y + 1));
    else
      allActions.push_back(action(*this, (*m_board)[m_x][m_y + 1].getPiece()));
    if(inBounds(m_x + 1))
    {
      if((*m_board)[m_x + 1][m_y + 1].occupied())
        allActions.push_back(action(*this, m_x + 1, m_y + 1));
      else
        allActions.push_back(action(*this, (*m_board)[m_x + 1][m_y + 1].getPiece()));
    }
    if(inBounds(m_x - 1))
    {
      if((*m_board)[m_x - 1][m_y + 1].occupied())
        allActions.push_back(action(*this, m_x - 1, m_y + 1));
      else
        allActions.push_back(action(*this, (*m_board)[m_x - 1][m_y - 1].getPiece()));
    }
  }
  if(inBounds(m_y - 1))
  {
    if((*m_board)[m_x][m_y - 1].occupied())
      allActions.push_back(action(*this, m_x, m_y - 1));
    else
      allActions.push_back(action(*this, (*m_board)[m_x][m_y - 1].getPiece()));
    if(inBounds(m_x + 1))
    {
      if((*m_board)[m_x + 1][m_y - 1].occupied())
        allActions.push_back(action(*this, m_x + 1, m_y - 1));
      else
        allActions.push_back(action(*this, (*m_board)[m_x + 1][m_y - 1].getPiece()));
    }
    if(inBounds(m_x - 1))
    {
      if((*m_board)[m_x - 1][m_y - 1].occupied())
        allActions.push_back(action(*this, m_x - 1, m_y - 1));
      else
        allActions.push_back(action(*this, (*m_board)[m_x - 1][m_y - 1].getPiece()));
    }
  }
  if(inBounds(m_x + 1))
  {
    if((*m_board)[m_x + 1][m_y].occupied())
      allActions.push_back(action(*this, m_x + 1, m_y));
    else
      allActions.push_back(action(*this, (*m_board)[m_x + 1][m_y].getPiece()));
  }
  if(inBounds(m_x - 1))
  {
    if((*m_board)[m_x - 1][m_y].occupied())
      allActions.push_back(action(*this, m_x - 1, m_y));
    else
      allActions.push_back(action(*this, (*m_board)[m_x - 1][m_y].getPiece()));
  }
  return allActions;
}