#include "tile.h"
tile::tile()
{
  m_mypiece = nullptr;
}

tile::~tile()
{
  m_mypiece = nullptr;
}

void tile::release()
{
  m_mypiece = nullptr;
}

void tile::move(mypiece & p)
{
  if(m_mypiece != nullptr)
    m_mypiece->remove();
  m_mypiece = &p;
}

bool tile::occupied() const
{
  return m_mypiece != nullptr;
}

const mypiece & tile::getPiece() const
{
  return *m_mypiece;
}