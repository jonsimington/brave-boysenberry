#include "utility.h"
#include "board.h"
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
      player->pieces[i]->move(intToFile(a.m_ex), a.m_ey + 1);
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

bool inCheck(const state & s)
{
  //std::cout << "enter" << std::endl;
  auto allActions = s.possibleActionsE();
  for(auto it = allActions.begin(); it != allActions.end(); it++)
  {
    if(it->m_pr != "" && s.m_pieces.find(it->m_pr)->second->getType() == "King")
    {
      //std::cout << "leave!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
      return true;
    }
  }
  //std::cout << "leave" << std::endl;
  return false;
}