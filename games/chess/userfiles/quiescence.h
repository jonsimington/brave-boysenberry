#pragma once
#include "utility.h"
#include "state.h"
/*checks if valuable pieces are threatened on either side of the board*/
bool isQuiescent(const state & s)
{
  for(auto it = s.m_pieces.cbegin(); it != s.m_pieces.cend(); it++)
  {
    if(it->second->inUse() && isUnderAttack(*(it->second), s.m_board) && (it->second->getValue(s) > 4 || it->second->getType() == "King"))
    {
      //std::cout << "qui\n";
      return false;
    }
  }
  return true;
}