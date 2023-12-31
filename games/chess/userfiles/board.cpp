#include "board.h"

int const board::m_length = boardLength;

board::board()
{
  create();
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
  create();
  for(int i = 0; i < m_length; i++)
  {
    for(int j = 0; j < m_length; j++)
    {
      m_data[i][j] = rhs.m_data[i][j];
    }
  }
}

const board & board::operator = (const board & rhs)
{
  for(int i = 0; i < m_length; i++)
  {
    for(int j = 0; j < m_length; j++)
    {
      m_data[i][j] = rhs.m_data[i][j];
    }
  }
  return *this;
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

void board::create()
{
  m_data = new tile*[m_length];
  for(int i = 0; i < m_length; i++)
  {
    m_data[i] = new tile[m_length];
  }
}

void board::reset()
{
  for(int i = 0; i < m_length; i++)
  {
    for(int j = 0; j < m_length; j++)
    {
      m_data[i][j].release();
    }
  }
}

void board::print() const
{
  for(int i = m_length - 1; i >= 0; i--)
  {
    std::cout << " " << i << "  |";
    for(int j = 0; j < m_length; j++)
    {
      if(!m_data[j][i].occupied())
      {
        std::cout << ".";
      }
      else
      {
        bool friendly = m_data[j][i].getPiece().isFriendly();
        char type = m_data[j][i].getPiece().getType()[0];
        if(!friendly)
        {
          type += 32;
        }
        std::cout << type;
      }
      std::cout << "  ";
    }
    std::cout << std::endl;
  }
}