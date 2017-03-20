#include "mypiece.h"

mypiece::mypiece(){;}

mypiece::mypiece(const int & x, const int & y, const std::string & id)
{
  m_x = x;
  m_y = y;
  m_id = id;
}

mypiece::mypiece(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved)
{
  m_friendly = friendly;
  m_x = x;
  m_y = y;
  m_id = id;
  m_board = &b;
  (*m_board)[x][y].move(*this); 
  m_inUse = true;
  m_hasMoved = hasMoved;
}

void mypiece::place(const int & x, const int & y)
{
  m_x = x;
  m_y = y;
}

void mypiece::move(const int & x, const int & y)
{
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

void mypiece::possibleActions(const int & px, const int & py, const bool cp, std::vector<action> & allActions) const
{
}

mypiece* mypiece::clone() const
{
  mypiece* p = new mypiece(m_x, m_y, m_id);
  p->m_inUse = m_inUse;
  p->m_hasMoved = m_hasMoved;
  p->m_type = m_type;
  p->m_board = nullptr;
  p->m_friendly = m_friendly;
  return p;  
}

int mypiece::getX() const {return m_x;}
int mypiece::getY() const {return m_y;}
std::string mypiece::getId() const {return m_id;}

void mypiece::copyValues(const mypiece* rhs)
{
    m_x = rhs->m_x;
    m_y = rhs->m_y;
    m_inUse = rhs->m_inUse;
    m_id = rhs->m_id;
    m_board = nullptr;
    m_hasMoved = rhs->m_hasMoved;
    m_type = rhs->m_type;
    m_friendly = rhs->m_friendly;
}

bool mypiece::isFriendly() const
{
  return m_friendly;
}

bool mypiece::inUse() const
{
  return m_inUse;
}

std::string mypiece::getType() const
{
  return m_type;
}

int mypiece::getDirection() const
{
  return -1;
}

float mypiece::getValue() const
{
  return 0;
}

bool mypiece::hasMoved() const
{
  return m_hasMoved;
}