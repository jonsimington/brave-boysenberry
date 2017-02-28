#include "state.h"
#include "utility.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
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

state & state::operator = (const cpp_client::chess::Game & g)
{
  std::vector<mypiece*>* pieces;
  for(int i = 0; i < g->pieces.size(); i++)
  {
   if(g->pieces[i]->owner->name == myAI)
      pieces = &m_friendlyPieces;
    else
      pieces = &m_enemyPieces;
    
    int x = fileToInt(g->pieces[i]->file);
    int y = g->pieces[i]->rank - 1;
    std::string id = g->pieces[i]->id;
    if(g->pieces[i]->type == "Pawn")
    {
      bool facing;
      if(y == 1)
        facing = 0;
      else
        facing = 1;
      m_pieces[id] = pawn(x, y, facing,id);
      pieces->push_back(&m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Knight")
    {
      m_pieces[id] = knight(x, y,id);
      pieces->push_back(&m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Rook")
    {
      m_pieces[id] = rook(x, y,id);
      pieces->push_back(&m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Bishop")
    {
      m_pieces[id] = bishop(x,y,id);
      pieces->push_back(&m_pieces[id]);
    }
    else if(g->pieces[i]->type == "King")
    {
      m_pieces[id] = king(x, y,id);
      pieces->push_back(&m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Queen")
    {
      m_pieces[id] = queen(x, y,id);
      pieces->push_back(&m_pieces[id]);
    }
  }
  return *this;
}

state::state(const cpp_client::chess::Game & g)
{
  *this = g; 
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