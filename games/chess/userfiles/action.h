#pragma once
#include "mypiece.h"
class action
{
  public:
    action(const int & id, const int & pr, const int & sx, const int & sy, const int & ex, const int & ey);
    action(const int & id, const int & sx, const int & sy, const int & ex, const int & ey);
    action(const mypiece & pm, const mypiece & pr);
    action(const mypiece & pm, const int & x, const int & y);
  private:
    int m_id; //mypiece id
    int m_pr; //mypiece id of mypiece removed
    int m_sx;
    int m_sy;
    int m_ex;
    int m_ey;
};