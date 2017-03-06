#include "action.h"
#include "utility.h"
action::action(const mypiece & pm, const mypiece & pr, const std::string promoteType)
{
  m_sx = pm.getX();
  m_sy = pm.getY();
  m_ex = pr.getX();
  m_ey = pr.getY();
  m_id = pm.getId();
  m_pr = pr.getId();
  m_promoteType = promoteType;
  m_enPassant = false;
}

action::action(const mypiece & pm, const int & x, const int & y, const std::string promoteType)
{
  m_sx = pm.getX();
  m_sy = pm.getY();
  m_ex = x;
  m_ey = y;
  m_id = pm.getId();
  m_promoteType = promoteType;
  m_enPassant = false;
}

action::action(const mypiece & pm, const mypiece & pr, bool enPassant)
{
  m_sx = pm.getX();
  m_sy = pm.getY();
  m_ex = pr.getX();
  if(pm.getDirection())
  {
    m_ey = pr.getY() + 1;
  }
  else
  {
    m_ey = pr.getY() - 1;
  }
  m_id = pm.getId();
  m_pr = pr.getId();
  m_enPassant = enPassant;
}

action::action(const cpp_client::chess::Move & move)
{
  m_sx = fileToInt(move->from_file);
  m_sy = move->from_rank - 1;
  m_ex = fileToInt(move->to_file);
  m_ey = move->to_rank - 1;
  m_id = move->piece->id;
  m_promoteType = move->promotion;
  if(move->captured != nullptr)
  {
    m_pr = move->captured->id;
  }
  m_enPassant = false;
}

bool action::operator == (const action & rhs) const
{
  return m_id == rhs.m_id && m_pr == rhs.m_pr && m_sx == rhs.m_sx && m_promoteType == rhs.m_promoteType &&
         m_sy == rhs.m_sy && m_ex == rhs.m_ex && m_ey == rhs.m_ey && m_enPassant == rhs.m_enPassant;
}

bool action::operator != (const action & rhs) const
{
  return !(*this == rhs);
}