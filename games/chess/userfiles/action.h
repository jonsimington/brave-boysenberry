#pragma once

class action
{
  public:
    action(const int & id, const int & pr, const int & sx, const int & sy, const int & ex, const int & ey);
    action(const int & id, const int & sx, const int & sy, const int & ex, const int & ey);
  private:
    int m_id; //piece id
    int m_pr; //piece id of piece removed
    int m_sx;
    int m_sy;
    int m_ex;
    int m_ey;
};