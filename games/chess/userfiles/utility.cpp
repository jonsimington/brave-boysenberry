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