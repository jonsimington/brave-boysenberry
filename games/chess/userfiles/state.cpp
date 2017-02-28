#include "state.h"
state::state()
{
  
}

state::state(const state & rhs)
{
  *this = rhs;
}

state & state::operator = (const state & rhs)
{
  m_pieces = rhs.m_pieces;
  for(auto it = m_pieces.begin(); it != m_pieces.end(); it++)
    m_board[it->second.getX()][it->second.getY()].move(it->second);
  return *this;
}

state::state(const cpp_client::chess::Game & g)
{
  std::map<std::string, mypiece>* pieces;
  for(int i = 0; i < g->pieces.size(); i++)
  {
   /* if(g->pieces[i]->owner->name == myAI)
      pieces = &m_fp;
    else
      pieces = &m_ep;
    */
    auto x = fileToInt(g->pieces[i]->file);
    auto y = g->pieces[i]->rank - 1;
    auto id = g->pieces[i]->id;
    if(g->pieces[i]->type == "Pawn")
    {
      bool facing;
      if(y == 1)
       facing = 0;
      else
       facing = 1;
      (*pieces)[id] = pawn(x, y, facing);
    }
    else if(g->pieces[i]->type == "Knight")
    {
      m_pieces[id] = knight(x, y);
    }
    else if(g->pieces[i]->type == "Rook")
    {
      m_pieces[id] = rook(x, y);
    }
    else if(g->pieces[i]->type == "Bishop")
    {
      m_pieces[id] = bishop(x,y);
    }
    else if(g->pieces[i]->type == "King")
    {
      m_pieces[id] = king(x, y);
    }
    else if(g->pieces[i]->type == "Queen")
    {
      m_pieces[id] = queen(x, y);
    }
  }
}

state state::operator + (const action & a) const
{
  state result(*this);
  auto it = result.m_pieces.find(a.m_id);
  if(a.m_pr != "")
  {
    result.m_pieces[a.m_pr].remove();
    result.m_board[a.m_ex][a.m_ey].release();
  }
  result.m_board[a.m_sx][a.m_sy].release();
  it->second.m_x = a.m_sx;
  it->second.m_y = a.m_sy;
  result.m_board[a.m_ex][a.m_ey].move(it->second);
  return result;
}

std::vector<action> state::possibleActions() const
{
  std::vector<action> allActions;
  return allActions;
}