#include "action.h"
action::action(const int & id, const int & pr, const int & sx, 
               const int & sy, const int & ex, const int & ey): 
               m_id(id), m_pr(pr), m_sx(sx), m_sy(sy),
               m_ex(ex), m_ey(ey) {}

action::action(const int & id, const int & sx, const int & sy, 
               const int & ex, const int & ey): 
               m_id(id), m_pr(-1), m_sx(sx), m_sy(sy),
               m_ex(ex), m_ey(ey) {}
              
action::action(const piece & pm, const piece & pr)
{
  m_sx = pm.getX();
  m_sy = pm.getY();
  m_ex = pr.getX();
  m_ey = pr.getY();
  m_id = pm.getId();
  m_pr = pm.getId();
}

action::action(const piece & pm, const int & x, const int & y)
{
  m_sx = pm.getX();
  m_sy = pm.getY();
  m_ex = x;
  m_ey = y;
  m_id = pm.getId();
  m_pr = -1;
}