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
}

action::action(const mypiece & pm, const int & x, const int & y, const std::string promoteType)
{
  m_sx = pm.getX();
  m_sy = pm.getY();
  m_ex = x;
  m_ey = y;
  m_id = pm.getId();
  m_promoteType = promoteType;
}

action::action(const cpp_client::chess::Move & move)
{
  //std::cout << "action copy const start" << std::endl;
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
  //std::cout << "action copy const end" << std::endl;
}