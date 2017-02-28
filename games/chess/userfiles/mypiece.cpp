#include "mypiece.h"

mypiece::mypiece(){;}

mypiece::mypiece(const int & x, const int & y)
{
  m_x = x;
  m_y = y;
  m_inUse = true;
  m_hasMoved = false;
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
  return m_id < rhs.m_id;
}

void mypiece::remove()
{
  m_inUse = false;
}

int mypiece::getX() const {return m_x;}
int mypiece::getY() const {return m_y;}
std::string mypiece::getId() const {return m_id;}