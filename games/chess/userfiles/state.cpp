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
  std::cout << "state created\n" << std::endl;
}

state::state(const state & rhs)
{
  *this = rhs;
}

state::~state()
{
  deleteData();
}

state & state::operator = (const state & rhs)
{
  //std::cout << "= operator state start" << std::endl;
  m_board.reset();
  deleteData();
  //std::cout << rhs.m_pieces.size() << std::endl;
  for(auto it = rhs.m_pieces.begin(); it != rhs.m_pieces.end(); it++)
  {
    auto p = m_pieces[it->first] = it->second->clone();
    p->m_board = &m_board;
    if(p->isFriendly())
    {
      m_friendlyPieces.push_back(p);
    }
    else
    {
      m_enemyPieces.push_back(p);
    }
    if(p->inUse())
    {
      m_board[p->getX()][p->getY()].move(*p);
    }
  }
  m_id = rhs.m_id;
  //std::cout << "= operator state end" << std::endl;
  return *this;
}

state & state::operator = (const cpp_client::chess::Game & g)
{
  //std::cout << "= operator game start" << std::endl;;
  m_board.reset();
  deleteData();
  std::vector<mypiece*>* pieces;
  bool friendly;
  for(int i = 0; i < g->pieces.size(); i++)
  {
   if(g->pieces[i]->owner->id == m_id)
   {
     pieces = &m_friendlyPieces;
     friendly = true;
   }
   else
   {
     pieces = &m_enemyPieces;
     friendly = false;
   }
    int x = fileToInt(g->pieces[i]->file);
    int y = g->pieces[i]->rank - 1;
    std::string id = g->pieces[i]->id;
    bool hasMoved = g->pieces[i]->has_moved;
    if(g->pieces[i]->type == "Pawn")
    {
      bool facing;
      if(y == 1)
        facing = 0;
      else
        facing = 1;
      m_pieces[id] = new pawn(x, y, facing,id,m_board,friendly,hasMoved);
      pieces->push_back(m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Knight")
    {
      m_pieces[id] = new knight(x, y,id,m_board,friendly,hasMoved);
      pieces->push_back(m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Rook")
    {
      m_pieces[id] = new rook(x, y,id,m_board,friendly,hasMoved);
      pieces->push_back(m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Bishop")
    {
      m_pieces[id] = new bishop(x,y,id,m_board,friendly,hasMoved);
      pieces->push_back(m_pieces[id]);
    }
    else if(g->pieces[i]->type == "King")
    {
      m_pieces[id] = new king(x, y,id,m_board,friendly,hasMoved);
      pieces->push_back(m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Queen")
    {
      m_pieces[id] = new queen(x, y,id,m_board,friendly,hasMoved);
      pieces->push_back(m_pieces[id]);
    }
  }
  //std::cout << "= operator game end" << std::endl;
  return *this;
}

state::state(const cpp_client::chess::Game & g)
{
  *this = g; 
}

state state::operator + (const action & a) const
{
  //std::cout << "+ operator action start" << std::endl;
  state result(*this);
  auto it = result.m_pieces.find(a.m_id);
  if(a.m_pr != "")
  {
    result.m_pieces[a.m_pr]->remove(); //m_inUse = false;
    result.m_board[a.m_ex][a.m_ey].release();
  }
  result.m_board[a.m_sx][a.m_sy].release();
  it->second->move(a.m_ex, a.m_ey);
  result.m_board[a.m_ex][a.m_ey].move(*(it->second));
  it->second->m_hasMoved = true;
  //std::cout << "+ operator action end" << std::endl;
  return result;
}

std::vector<action> state::possibleActionsF() const
{
  std::vector<action> allActions;
  //std::cout << "number of friendly pieces: " << m_friendlyPieces.size() << std::endl;
  for(int i = 0; i < m_friendlyPieces.size(); i++)
  {
    if(m_friendlyPieces[i]->inUse())
    {
      allActions += m_friendlyPieces[i]->possibleActions();
    }
  }
  for(int i = 0; i < allActions.size();)
  {
    state s = *this + allActions[i];
    if(inCheck(s, s.m_enemyPieces))
    {
      //std::cout << "removing: " <<  allActions[i].m_sx << ", ";
      //std::cout << allActions[i].m_sy << " to ";
      //std::cout << allActions[i].m_ex << ", " << allActions[i].m_ey << std::endl;      
      allActions.erase(allActions.begin() + i);
    }
    else
    {
      i++;
    }
  }
  return allActions;
}

std::vector<action> state::possibleActionsE() const
{
  std::vector<action> allActions;
  for(int i = 0; i < m_enemyPieces.size(); i++)
  {
    if(m_enemyPieces[i]->inUse())
    {
      allActions += m_enemyPieces[i]->possibleActions();
    }
  }
  /*auto it = allActions.begin();
  while(it != allActions.end())
  {
    auto s = *this + *it;
    if(inCheck(s))
    {
      it = allActions.erase(it);
    }
    else
    {
      it++;
    }
  }*/
  return allActions;
}

void state::deleteData()
{
  for(auto it = m_pieces.begin(); it != m_pieces.end(); it++)
  {
    delete it->second;
  }
  m_pieces.clear();
  m_friendlyPieces.clear();
  m_enemyPieces.clear();
}