#include "action.h"
action::action(const int & id, const int & pr, const int & sx, const int & sy, const int & ex, const int & ey): m_id(id), m_pr(pr), m_sx(sx), m_sy(sy),
                                        m_ex(ex), m_ey(ey) {}

action::action(const int & id, const int & sx, const int & sy, const int & ex, const int & ey): m_id(id), m_pr(-1), m_sx(sx), m_sy(sy),
                                    m_ex(ex), m_ey(ey) {}