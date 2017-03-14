#include "state.h"
#include "utility.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include <cmath>
#include <sstream>
state::state()
{
  can_EnPassant = false;
  lastCapture = 0;
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
  lastCapture = 0;
  previous_actions = rhs.previous_actions;
  m_board.reset();
  deleteData();
  lastCapture = rhs.lastCapture;
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
  px = rhs.px;
  py = rhs.py;
  can_EnPassant = rhs.can_EnPassant;
  return *this;
}

state & state::operator = (const cpp_client::chess::Game & g)
{
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
      if(g->pieces[i]->owner->color == "White")
      {
        facing = 0;
        if(y == 1)
        {
          hasMoved = false;
        }
        else
        {
          hasMoved = true;
        }
      }
      else
      {
        facing = 1;
        if(y == 6)
        {
          hasMoved = false;
        }
        else
        {
          hasMoved = true;
        }
      }
      m_pieces[id] = new pawn(x, y, facing,id,m_board,friendly,hasMoved);
      pieces->push_back(m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Knight")
    {
      m_pieces[id] = new knight(x, y,id,m_board,friendly,true);
      pieces->push_back(m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Rook")
    {
      m_pieces[id] = new rook(x, y,id,m_board,friendly,true);
      pieces->push_back(m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Bishop")
    {
      m_pieces[id] = new bishop(x,y,id,m_board,friendly,true);
      pieces->push_back(m_pieces[id]);
    }
    else if(g->pieces[i]->type == "King")
    {
      m_pieces[id] = new king(x, y,id,m_board,friendly,true);
      pieces->push_back(m_pieces[id]);
    }
    else if(g->pieces[i]->type == "Queen")
    {
      m_pieces[id] = new queen(x, y,id,m_board,friendly,true);
      pieces->push_back(m_pieces[id]);
    }
  }
  std::istringstream stringstream(g->fen);
  std::string code;
  stringstream >> code;
  stringstream >> code;
  stringstream >> code;
  if(code != "-")
  {
    for(int i = 0; i < code.size(); i++)
    {
      if(code[i] == 'K')
      {
        m_board[4][0].getPieceRef()->m_hasMoved = false;
        m_board[7][0].getPieceRef()->m_hasMoved = false;
      }
      else if(code[i] == 'Q')
      {
        m_board[4][0].getPieceRef()->m_hasMoved = false;
        m_board[0][0].getPieceRef()->m_hasMoved = false;
      }
      else if(code[i] == 'k')
      {
        m_board[4][7].getPieceRef()->m_hasMoved = false;
        m_board[7][7].getPieceRef()->m_hasMoved = false;
      }
      else if(code[i] == 'q')
      {
        m_board[4][7].getPieceRef()->m_hasMoved = false;
        m_board[0][7].getPieceRef()->m_hasMoved = false;
      }
    }
  }
  stringstream >> code;
  if(code != "-")
  {
    px = fileToInt(code[0]);
    py = code[1] - '1';
    can_EnPassant = true;
  }
  else
  {
    can_EnPassant = false;
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
  if(a.m_promoteType != "")
  {
    changeType(result, result.m_pieces[a.m_id], a.m_promoteType);
  }
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
  if(it->second->getType() == "Pawn" && std::abs(a.m_ey - a.m_sy) == 2)
  {
    result.can_EnPassant = true;
    result.px = a.m_ex;
    if(it->second->getDirection())
      result.py = a.m_ey - 1;
    else
      result.py = a.m_ey + 1;
  }
  else
  {
    result.can_EnPassant = false;
  }
  if(it->second->getType() == "King" && std::abs(a.m_ex - a.m_sx) == 2)
  {
    mypiece* rook;
    int newx;
    if(a.m_ex - a.m_sx > 0)
    {
      rook = result.m_board[boardLength - 1][a.m_sy].getPieceRef();
      newx = a.m_ex - 1;
    }
    else
    {
      rook = result.m_board[0][a.m_sy].getPieceRef();
      newx = a.m_ex + 1;
    }
    result.m_board[rook->getX()][rook->getY()].release();
    rook->m_hasMoved = true;
    rook->move(newx, a.m_sy);
    result.m_board[newx][a.m_sy].move(*rook);
  }
  if(a.m_pr == "" && a.m_promoteType == "" && it->second->getType() != "Pawn")
  {
    result.lastCapture++;
  }
  else
  {
    result.lastCapture = 0;
  }
  result.addToPrevious(a);
  return result;
}

std::vector<action> state::possibleActionsF() const
{
  std::vector<action> allActions;
  std::string kingId;
  in_check = inCheck();
  for(int i = 0; i < m_friendlyPieces.size(); i++)
  {
    if(m_friendlyPieces[i]->inUse())
    {
      allActions += m_friendlyPieces[i]->possibleActions(px,py,can_EnPassant);
    }
    if(m_friendlyPieces[i]->getType() == "King")
    {
      kingId = m_friendlyPieces[i]->getId();
    }
  }
  for(int i = 0; i < allActions.size();)
  {
    state s = *this + allActions[i];
    if(isUnderAttack(*(s.m_pieces[kingId]), s.m_board) || s.isDraw())
    {
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
  std::string kingId;
  in_check = inCheck();
  for(int i = 0; i < m_enemyPieces.size(); i++)
  {
    if(m_enemyPieces[i]->inUse())
    {
      allActions += m_enemyPieces[i]->possibleActions(px,py,can_EnPassant);
    }
    if(m_enemyPieces[i]->getType() == "King")
    {
      kingId = m_enemyPieces[i]->getId();
    }
  }
  for(int i = 0; i < allActions.size();)
  {
    state s = *this + allActions[i];
    if(isUnderAttack(*(s.m_pieces[kingId]), s.m_board) || s.isDraw())
    {
      allActions.erase(allActions.begin() + i);
    }
    else
    {
      i++;
    }
  }
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

bool state::inCheck() const
{
  for(int i = 0; i < m_friendlyPieces.size(); i++)
  {
    return isUnderAttack(*(m_friendlyPieces[i]), m_board);
  }
}

float state::getValue() const
{
  float value = 0;
  for(auto it = m_pieces.cbegin(); it != m_pieces.cend(); it++)
  {
    if(it->second->inUse())
    {
      if(it->second->isFriendly())
      {
        value += it->second->getValue();
      }
      else
      {
        value -= it->second->getValue();
      }
    }
    else if(it->second->getType() == "King")
    {
      if(it->second->isFriendly())
      {
        return 0;
      }
      else
      {
        return 1;
      }
    }
  }
  value /= (pawnValue * 8 + bishopValue * 2 + rookValue * 2 + knightValue * 2 + queenValue) * 2;
  //std::cout << value + .5 << std::endl;
  return value + .5;
}

bool state::terminal() const
{
  for(auto it = m_pieces.cbegin(); it != m_pieces.cend(); it++)
  {
    if(it->second->getType() == "King" && !it->second->inUse())
    {
      return true;
    }
  }
  return false;
}

bool state::isDraw() const
{
  //std::cout << previous_actions.size() << "\n";
  if(previous_actions.size() == 8 && lastCapture >= 8)
  {
    return previous_actions[0] == previous_actions[4] && 
    previous_actions[1] == previous_actions[5] &&
    previous_actions[2] == previous_actions[6] &&
    previous_actions[3] == previous_actions[7];
  }
  else
  {
    return false;
  }
}

void state::addToPrevious(const action & a)
{
  if(previous_actions.size() == 8)
  {
    previous_actions.erase(previous_actions.begin());
  }
  previous_actions.push_back(a);
}