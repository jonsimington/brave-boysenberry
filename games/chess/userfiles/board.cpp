#include "board.h"

int const board::m_length = boardLength;

board::board()
{
  m_data = new tile*[m_length];
  for(int i = 0; i < m_length; i++)
    m_data[i] = new tile[m_length];
}

board::~board()
{
  if(m_data != nullptr)
  {
    for(int i = 0; i < m_length; i++)
      delete [] m_data[i];
    delete [] m_data;
    m_data = nullptr;
  }
}

board::board(const board & rhs)
{
  for(int i = 0; i < m_length; i++)
    for(int j = 0; j < m_length; j++)
      m_data[i][j] = rhs.m_data[i][j];
}

const board & board::operator = (const board & rhs)
{
  for(int i = 0; i < m_length; i++)
    for(int j = 0; j < m_length; j++)
      m_data[i][j] = rhs.m_data[i][j];
  return *this;
}

board::board(board && rhs)
{
  if(m_data != nullptr)
  {
    for(int i = 0; i < m_length; i++)
      delete [] m_data[i];
    delete [] m_data;
  }
  m_data = rhs.m_data;
  rhs.m_data = nullptr;
}

const tile* board::operator [] (const int & i) const
{
  return m_data[i];
}

tile* board::operator [] (const int & i)
{
  return m_data[i];
}

int board::getLength() const
{
  return m_length;
}