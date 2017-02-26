#include "tile.h"
tile::tile()
{
  m_piece = nullptr;
}

void tile::release()
{
  m_piece = nullptr;
}

void tile::add(piece & p)
{
  if(m_piece != nullptr)//remove the piece
  {
    
  }
  m_piece = &p;
}