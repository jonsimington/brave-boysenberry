#include "utility.h"
#include "board.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "pawn.h"
#include "knight.h"

int fileToInt(const char f)
{
  return f - 'a';  
}

int fileToInt(const std::string & f)
{
  return fileToInt(f[0]);
}

std::string intToFile(const int & i)
{
  std::string s;
  s.push_back(i + 'a');
  return s;
}

bool inBounds(const int & i)
{
  return i >= 0 && i < boardLength;
}

void modifyGame(cpp_client::chess::Player & player, const action & a)
{
  for(int i = 0; i < player->pieces.size(); i++)
  {
    if(player->pieces[i]->id == a.m_id)
    {
      player->pieces[i]->move(intToFile(a.m_ex), a.m_ey + 1, a.m_promoteType);
      break;
    }
  }
}

bool checkToPlace(const mypiece* p, const board & theBoard, const int & x, const int & y, std::vector<action> & actions)
{
  if(theBoard[x][y].occupied())
  {
    if(theBoard[x][y].getPiece().isFriendly() == p->isFriendly())
    {
      return false;
    }
    else
    {
      actions.push_back(action(*p, theBoard[x][y].getPiece()));
      return false;
    }
  }
  else
  {
    actions.push_back(action(*p, x, y));
    return true;
  }
}

void diagonalMoves(const mypiece* p, const board & theBoard, std::vector<action> & allActions)
{
  int x, y;
  for(x = p->getX() + 1, y = p->getY() + 1; x < boardLength && y < boardLength; x++, y++) //top right
  {
    if(!checkToPlace(p,theBoard,x,y,allActions))
    {
      break;
    }
  }
  for(x = p->getX() - 1, y = p->getY() + 1; x >= 0 && y < boardLength; x--, y++) //top left
  {
    if(!checkToPlace(p,theBoard,x,y,allActions))
    {
      break;
    }
  }
  for(x = p->getX() - 1, y = p->getY() - 1; x >= 0 && y >= 0; x--, y--) //bottom left
  {
    if(!checkToPlace(p,theBoard,x,y,allActions))
    {
      break;
    }
  }
  for(x = p->getX() + 1, y = p->getY() - 1; x < boardLength && y >= 0; x++, y--) //bottom right
  {
    if(!checkToPlace(p,theBoard,x,y,allActions))
    {
      break;
    }
  }
}

void straightMoves(const mypiece* p, const board & theBoard, std::vector<action> & allActions)
{
  int i;
  for(i = p->getX() + 1; i < boardLength; i++) //checking x value to the right
  {
    if(!checkToPlace(p,theBoard,i,p->getY(),allActions))
    {
      break;
    }
  }
  
  //checking x value to the left
  for(i = p->getX() - 1; i >= 0; i--)
  {
    if(!checkToPlace(p,theBoard,i,p->getY(),allActions))
    {
      break;
    }
  }
  
  for(i = p->getY() + 1; i < boardLength; i++)
  {
    if(!checkToPlace(p,theBoard,p->getX(),i,allActions))
    {
      break;
    }
  }
  for(i = p->getY() - 1; i >= 0; i--)
  {
    if(!checkToPlace(p,theBoard,p->getX(),i,allActions))
    {
      break;
    }
  }
}

bool inCheck(const state & s, const std::vector<mypiece*> & pieces)
{
  //std::cout << "enter" << std::endl;
  std::vector<action> allActions;
  for(int i = 0; i < pieces.size(); i++)
  {
    if(pieces[i]->inUse())
    {
      allActions += pieces[i]->possibleActions();
    }
  }
  for(auto it = allActions.begin(); it != allActions.end(); it++)
  {
    if(it->m_pr != "" && s.m_pieces.find(it->m_pr)->second->getType() == "King")
    {
      //s.m_board.print();
      //std::cout << "action that kills is: " <<  it->m_sx << ", ";
      //std::cout << it->m_sy << " to ";
      //std::cout << it->m_ex << ", " << it->m_ey << std::endl;  
      return true;
    }
  }
  //std::cout << "leave" << std::endl;
  return false;
}

mypiece* changeType(state & s, mypiece* p, const std::string & typeTo)
{
  mypiece* newpiece;
  std::vector<mypiece*>* pieces;
  if(typeTo == "Queen")
  {
    newpiece = new queen;
  }
  else if(typeTo == "Knight")
  {
    newpiece = new knight;
  }
  else if(typeTo == "Rook")
  {
    newpiece = new rook;
  }
  else if(typeTo == "Bishop")
  {
    newpiece = new bishop;
  }
  newpiece->copyValues(p);
  delete s.m_pieces[newpiece->getId()];
  s.m_pieces[newpiece->getId()] = newpiece;
  if(newpiece->isFriendly())
    pieces = &s.m_friendlyPieces;
  else
    pieces = &s.m_enemyPieces;
  for(int i = 0; i < pieces->size(); i++)
  {
    if((*pieces)[i]->getId() == newpiece->getId())
    {
      (*pieces)[i] = newpiece;
      break;
    }
  }
  return newpiece;
}