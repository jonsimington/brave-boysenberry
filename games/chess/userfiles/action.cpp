#include "action.h"

action::action(const mypiece & pm, const mypiece & pr)
{
  m_sx = pm.getX();
  m_sy = pm.getY();
  m_ex = pr.getX();
  m_ey = pr.getY();
  m_id = pm.getId();
  m_pr = pm.getId();
}

action::action(const mypiece & pm, const int & x, const int & y)
{
  m_sx = pm.getX();
  m_sy = pm.getY();
  m_ex = x;
  m_ey = y;
  m_id = pm.getId();
}