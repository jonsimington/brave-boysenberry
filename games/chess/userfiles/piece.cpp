#include "piece.h"

piece::piece(){;}

piece::piece(const int & x, const int & y)
{
  m_x = x;
  m_y = y;
  m_inUse = true;
}

void piece::place(const int & x, const int & y)
{
  m_x = x;
  m_y = y;
}

void piece::move(const int & x, const int & y)
{
  m_board->m_data[m_x][m_x].release();
  m_board->m_data[x][y].move(*this);
  m_x = x;
  m_y = y;
}

bool piece::operator < (const piece & rhs) const
{
  if(m_x < rhs.m_x)
    return true;
  if(m_x > rhs.m_x)
    return false;
  if(m_y < rhs.m_y)
    return true;
  return false;
}

void piece::remove()
{
  m_inUse = false;
}

int piece::getX() const {return m_x;}
int piece::getY() const {return m_y;}
int piece::getId() const {return m_id;}