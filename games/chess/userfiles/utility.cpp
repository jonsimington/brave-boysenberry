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

bool inBounds(const int & i)
{
  return i >= 0 && i < boardLength;
}