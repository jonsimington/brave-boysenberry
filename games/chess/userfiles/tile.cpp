#include "tile.h"
tile::tile()
{
  m_piece = nullptr;
}

void tile::release()
{
  m_piece = nullptr;
}

void tile::move(piece & p)
{
  if(m_piece != nullptr)
    m_piece->remove();
  m_piece = &p;
}

bool tile::occupied() const
{
  return m_piece != nullptr;
}