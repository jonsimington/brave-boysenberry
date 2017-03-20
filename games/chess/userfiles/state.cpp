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
  lastCapture = rhs.lastCapture;
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

void state::applyAction(const action & a)
{
  if(a.m_promoteType != "")
  {
    changeType(*this, m_pieces[a.m_id], a.m_promoteType);
  }
  auto it = m_pieces.find(a.m_id);
  if(a.m_pr != "")
  {
    m_pieces[a.m_pr]->remove(); //m_inUse = false;
    m_board[a.m_ex][a.m_ey].release();
  }
  m_board[a.m_sx][a.m_sy].release();
  it->second->move(a.m_ex, a.m_ey);
  m_board[a.m_ex][a.m_ey].move(*(it->second));
  it->second->m_hasMoved = true;
  if(it->second->getType() == "Pawn" && std::abs(a.m_ey - a.m_sy) == 2)
  {
    can_EnPassant = true;
    px = a.m_ex;
    if(it->second->getDirection())
    {
      py = a.m_ey + 1;
    }
    else
    {
      py = a.m_ey - 1;
    }
  }
  else
  {
    can_EnPassant = false;
  }
  if(it->second->getType() == "King" && std::abs(a.m_ex - a.m_sx) == 2)
  {
    mypiece* rook;
    int newx;
    if(a.m_ex - a.m_sx > 0)
    {
      rook = m_board[boardLength - 1][a.m_sy].getPieceRef();
      newx = a.m_ex - 1;
    }
    else
    {
      rook = m_board[0][a.m_sy].getPieceRef();
      newx = a.m_ex + 1;
    }
    m_board[rook->getX()][rook->getY()].release();
    rook->m_hasMoved = true;
    rook->move(newx, a.m_sy);
    m_board[newx][a.m_sy].move(*rook);
  }
  if(a.m_pr == "" && a.m_promoteType == "" && it->second->getType() != "Pawn")
  {
    if(lastCapture.size() == 0)
    {
      lastCapture.push_back(0); 
    }
    else
    {
      lastCapture.push_back(lastCapture[lastCapture.size() - 1] + 1);
    }
  }
  else
  {
    lastCapture.push_back(0);
  }
  addToPrevious(a); 
}

void state::reverseAction(const action & a)
{
  if(a.m_promoteType != "")
  {
    changeType(*this, m_pieces[a.m_id], a.m_promoteFrom);
  }
  auto it = m_pieces.find(a.m_id);
  m_board[a.m_ex][a.m_ey].release();
  m_board[a.m_sx][a.m_sy].move(*(it->second));
  it->second->move(a.m_sx, a.m_sy);
  if(a.m_firstMove)
  {
    it->second->m_hasMoved = false;
  }
  if(it->second->getType() == "King" && std::abs(a.m_ex - a.m_sx) == 2)
  {
    //std::cout << "King stuff" << std::endl;
    mypiece* rook;
    int newx;
    if(a.m_ex - a.m_sx > 0)
    {
      rook = m_board[a.m_ex - 1][a.m_sy].getPieceRef();
      newx = 7;
    }
    else
    {
      rook = m_board[a.m_ex + 1][a.m_sy].getPieceRef();
      newx = 0;
    }
    m_board[rook->getX()][rook->getY()].release();
    rook->m_hasMoved = false;
    rook->move(newx, a.m_sy);
    m_board[newx][a.m_sy].move(*rook);
    //std::cout << "End King stuff" << std::endl;
  }
  if(a.m_pr != "")
  {
    it = m_pieces.find(a.m_pr);
    it->second->m_inUse = true;
    m_board[it->second->getX()][it->second->getY()].move(*(it->second));
  }
  if(a.m_enPassant)
  {
    can_EnPassant = true;
    px = a.m_ex;
    py = a.m_ey;
  }
  else
  {
    can_EnPassant = false;
  }
  lastCapture.erase(lastCapture.begin() + lastCapture.size() - 1);
  previous_actions.erase(previous_actions.begin() + previous_actions.size() - 1);
}

state state::operator + (const action & a) const
{
  state result(*this);
  result.applyAction(a);
  return result;
}

std::vector<action> state::possibleActionsF()
{
  std::vector<action> allActions;
  std::string kingId;
  in_check = inCheck(m_friendlyPieces);
  for(int i = 0; i < m_friendlyPieces.size(); i++)
  {
    if(m_friendlyPieces[i]->inUse())
    {
      m_friendlyPieces[i]->possibleActions(px,py,can_EnPassant,allActions);
    }
    if(m_friendlyPieces[i]->getType() == "King")
    {
      kingId = m_friendlyPieces[i]->getId();
    }
  }
  for(int i = 0; i < allActions.size();)
  {
    this->applyAction(allActions[i]);
    if(isUnderAttack(*(m_pieces[kingId]), m_board))
    {
      this->reverseAction(allActions[i]);
      allActions.erase(allActions.begin() + i);
    }
    else
    {
      this->reverseAction(allActions[i]);
      i++;
    }
  }
  return allActions;
}

std::vector<action> state::possibleActionsE()
{
  std::vector<action> allActions;
  std::string kingId;
  in_check = inCheck(m_enemyPieces);
  for(int i = 0; i < m_enemyPieces.size(); i++)
  {
    if(m_enemyPieces[i]->inUse())
    {
      m_enemyPieces[i]->possibleActions(px,py,can_EnPassant,allActions);
    }
    if(m_enemyPieces[i]->getType() == "King")
    {
      kingId = m_enemyPieces[i]->getId();
    }
  }
  for(int i = 0; i < allActions.size();)
  {
    this->applyAction(allActions[i]);
    if(isUnderAttack(*(m_pieces[kingId]), m_board))
    {
      this->reverseAction(allActions[i]);
      allActions.erase(allActions.begin() + i);
    }
    else
    {
      this->reverseAction(allActions[i]);
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

bool state::inCheck(const std::vector<mypiece*> & pieces) const
{
  for(int i = 0; i < pieces.size(); i++)
  {
    if(pieces[i]->getType() == "King")
    {
      return isUnderAttack(*pieces[i], m_board);
    }
  }
}

float state::getValue() const
{
  float value = 0;
  if(isDraw())
  {
    return 0;
  }
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
        return -10000;
      }
      else
      {
        return 10000;
      }
    }
  }
  return value;
}

bool state::terminal() const
{
  if(isDraw())
  {
    return true;
  }
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
  int lc;
  if(lastCapture.size() == 0)
  {
    lc = 0;
  }
  else
  {
    lc = lastCapture[lastCapture.size() - 1];
  }
  if(previous_actions.size() >= 8 && lc >= 8)
  {
    if(lc >= 50)
    {
      return true;
    }
    int size = previous_actions.size();
    return previous_actions[size - 8] == previous_actions[size - 4] && 
    previous_actions[size - 7] == previous_actions[size - 3] &&
    previous_actions[size - 6] == previous_actions[size - 2] &&
    previous_actions[size - 5] == previous_actions[size - 1];
  }
  else
  {
    return false;
  }
}

void state::addToPrevious(const action & a)
{
  previous_actions.push_back(a);
}