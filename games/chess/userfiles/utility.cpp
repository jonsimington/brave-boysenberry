#include "utility.h"
#include "board.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "pawn.h"
#include "knight.h"
#include <sstream>

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
  std::cout << "modifying game...." << std::endl;
  for(int i = 0; i < player->pieces.size(); i++)
  {
    if(player->pieces[i]->id == a.m_id)
    {
      player->pieces[i]->move(intToFile(a.m_ex), a.m_ey + 1, a.m_promoteType);
      break;
    }
  }
  std::cout << "done modifying game...." << std::endl;
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

mypiece* changeType(state & s, mypiece* p, const std::string & typeTo)
{
  mypiece* newpiece;
  std::vector<mypiece*>* pieces;
  std::string type;
  if(typeTo == "Queen")
  {
    newpiece = new queen;
    type = "Queen";
  }
  else if(typeTo == "Knight")
  {
    newpiece = new knight;
    type = "Knight";
  }
  else if(typeTo == "Rook")
  {
    newpiece = new rook;
    type = "Rook";
  }
  else if(typeTo == "Bishop")
  {
    newpiece = new bishop;
    type = "Bishop";
  }
  else if(typeTo == "Pawn")
  {
    pawn* newpawn = new pawn;
    if(p->getY() < 2)
      newpawn->m_direction = 1;
    else
      newpawn->m_direction = 0;
    type = "Pawn";
    newpiece = newpawn;
    newpawn = nullptr;
  }
  newpiece->copyValues(p);
  newpiece->m_type = type;
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

bool isClearHorizontalA(const int & x1, const int & x2, const int & y, const board & theBoard, bool friendly)
{
  mypiece* p = new mypiece;
  p->m_y = y;
  p->m_friendly = friendly;
  for(int i = x1; i <= x2; i++)
  {
    p->m_x = i;
    if(isUnderAttack(*p, theBoard))
    {
      delete p;
      return false;
    }
  }
  delete p;
  return true;
}

bool isClearHorizontal(const int & x1, const int & x2, const int & y, const board & theBoard)
{
  for(int i = x1; i <= x2; i++)
  {
    if(theBoard[i][y].occupied())
    {
      return false;
    }
  }
  return true;
}

bool isUnderAttack(const mypiece & p, const board & theBoard)
{
  int x, y;

  //checking for king attacks
  for(x = p.getX() - 1; x <= p.getX() + 1; x++)
  {
    for(y = p.getY() - 1; y <= p.getY() + 1; y++)
    {
      if((x != p.getX() || y != p.getY()) && inBounds(x) && inBounds(y) && theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != p.isFriendly() &&
      theBoard[x][y].getPiece().getType() == "King")
        return true;
    }
  }
  
  //check for pawn attacks
  for(x = p.getX() - 1; x <= p.getX() + 1; x++)
  {
    for(y = p.getY() - 1; y <= p.getY() + 1; y++)
    {
      if(x != p.getX() && y != p.getY() && inBounds(x) && inBounds(y) && theBoard[x][y].occupied() && 
         theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && theBoard[x][y].getPiece().getType() == "Pawn" && 
         ((y > p.getY() && theBoard[x][y].getPiece().getDirection()) || (y < p.getY() && !theBoard[x][y].getPiece().getDirection())))
        return true;
    }
  }

  //checking for queens and bishops
  for(x = p.getX() + 1, y = p.getY() + 1; x < boardLength && y < boardLength; x++, y++) //top right
  {
    if(theBoard[x][y].occupied())
    {
      if(theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && (theBoard[x][y].getPiece().getType() == "Bishop" || theBoard[x][y].getPiece().getType() == "Queen"))
      {
        return true;
      }
      break;
    }      
  }
  for(x = p.getX() - 1, y = p.getY() + 1; x >= 0 && y < boardLength; x--, y++) //top left
  {
    if(theBoard[x][y].occupied())
    {
      if(theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && (theBoard[x][y].getPiece().getType() == "Bishop" || theBoard[x][y].getPiece().getType() == "Queen"))
      {
        return true;
      }
      break;
    }   
  }
  for(x = p.getX() - 1, y = p.getY() - 1; x >= 0 && y >= 0; x--, y--) //bottom left
  {
    if(theBoard[x][y].occupied())
    {
      if(theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && (theBoard[x][y].getPiece().getType() == "Bishop" || theBoard[x][y].getPiece().getType() == "Queen"))
      {
        return true;
      }
      break;
    }   
  }
  for(x = p.getX() + 1, y = p.getY() - 1; x < boardLength && y >= 0; x++, y--) //bottom right
  {
    if(theBoard[x][y].occupied())
    {
      if(theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && (theBoard[x][y].getPiece().getType() == "Bishop" || theBoard[x][y].getPiece().getType() == "Queen"))
      {
        return true;
      }
      break;
    }   
  }
  
  //checking for rooks and queens
  for(x = p.getX() + 1, y = p.getY(); x < boardLength; x++) //checking x value to the right
  {
    if(theBoard[x][y].occupied())
    {
      if(theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && (theBoard[x][y].getPiece().getType() == "Rook" || theBoard[x][y].getPiece().getType() == "Queen"))
      {
        return true;
      }
      break;
    }
  }
  for(x = p.getX() - 1, y = p.getY(); x >= 0; x--)
  {
    if(theBoard[x][y].occupied())
    {
      if(theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && (theBoard[x][y].getPiece().getType() == "Rook" || theBoard[x][y].getPiece().getType() == "Queen"))
      {
        return true;
      }
      break;
    }
  }
  for(y = p.getY() + 1, x = p.getX(); y < boardLength; y++)
  {
    if(theBoard[x][y].occupied())
    {
      if(theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && (theBoard[x][y].getPiece().getType() == "Rook" || theBoard[x][y].getPiece().getType() == "Queen"))
      {
        return true;
      }
      break;
    } 
  }
  for(y = p.getY() - 1, x = p.getX(); y >= 0; y--)
  {
    if(theBoard[x][y].occupied())
    {
      if(theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && (theBoard[x][y].getPiece().getType() == "Rook" || theBoard[x][y].getPiece().getType() == "Queen"))
      {
        return true;
      }
      break;
    }
  }
  if(p.getY() + 2 < boardLength)
  {
    y = p.getY() + 2;
    if(p.getX() + 1 < boardLength)
    {
      x = p.getX() + 1;
      if(theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && theBoard[x][y].getPiece().getType() == "Knight")
        return true;
    }
    if(p.getX() - 1 >= 0)
    {
      x = p.getX() - 1;
      if(theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && theBoard[x][y].getPiece().getType() == "Knight")
        return true;
    }
  }
  if(p.getY() - 2 >= 0)
  {
    y = p.getY() - 2;
    if(p.getX() + 1 < boardLength)
    {
      x = p.getX() + 1;
      if(theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && theBoard[x][y].getPiece().getType() == "Knight")
        return true;
    }
    if(p.getX() - 1 >= 0)
    {
      x = p.getX() - 1;
      if(theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && theBoard[x][y].getPiece().getType() == "Knight")
        return true;
    }
  }
  if(p.getX() + 2 < boardLength)
  {
    x = p.getX() + 2;
    if(p.getY() + 1 < boardLength)
    {
      y = p.getY() + 1;
      if(theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && theBoard[x][y].getPiece().getType() == "Knight")
        return true;
    }
    if(p.getY() - 1 >= 0)
    {
      y = p.getY() - 1;
      if(theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && theBoard[x][y].getPiece().getType() == "Knight")
        return true;
    }
  }
  if(p.getX() - 2 >= 0)
  {
    x = p.getX() - 2;
    if(p.getY() + 1 < boardLength)
    {
      y = p.getY() + 1;
      if(theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && theBoard[x][y].getPiece().getType() == "Knight")
        return true;
    }
    if(p.getY() - 1 >= 0)
    {
      y = p.getY() - 1;
      if(theBoard[x][y].occupied() && theBoard[x][y].getPiece().isFriendly() != p.isFriendly() && theBoard[x][y].getPiece().getType() == "Knight")
        return true;
    }
  }
  return false;
}