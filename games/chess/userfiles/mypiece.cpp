#include "mypiece.h"

mypiece::mypiece(){;}

mypiece::mypiece(const int & x, const int & y)
{
  m_x = x;
  m_y = y;
  m_inUse = true;
}

void mypiece::place(const int & x, const int & y)
{
  m_x = x;
  m_y = y;
}

void mypiece::move(const int & x, const int & y)
{
  m_board->m_data[m_x][m_x].release();
  m_board->m_data[x][y].move(*this);
  m_x = x;
  m_y = y;
}

bool mypiece::operator < (const mypiece & rhs) const
{
  if(m_x < rhs.m_x)
    return true;
  if(m_x > rhs.m_x)
    return false;
  if(m_y < rhs.m_y)
    return true;
  return false;
}

void mypiece::remove()
{
  m_inUse = false;
}

int mypiece::getX() const {return m_x;}
int mypiece::getY() const {return m_y;}
int mypiece::getId() const {return m_id;}