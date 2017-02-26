#include "piece.h"
piece::piece(){;}

piece::peice(const int & x, const int & y)
{
  m_x = x;
  m_y = y;
}

void piece::place(const int & x, const int & y)
{
  m_x = x;
  m_y = y;
}