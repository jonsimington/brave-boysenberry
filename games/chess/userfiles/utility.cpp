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

/*cpp_client::chess::Move actionToMove(const action & a)
{
  cpp_client::chess::Move move;
  move->from_file = intToFile(a.m_sx);
  move->from_rank = a.m_sy + 1;
  move->to_file = intToFile(a.m_ex)
  move->to_rank = a.m_ey + 1
  move->piece->id = a.m_id;
  move->captured->id = a.m_pr;
  return move;
}*/