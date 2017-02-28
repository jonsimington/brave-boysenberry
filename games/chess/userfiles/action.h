#pragma once
#include "mypiece.h"
#include "../move.cpp"
#include <string>

struct action
{
  public:
    action(const mypiece & pm, const mypiece & pr);
    action(const mypiece & pm, const int & x, const int & y);
    action(const cpp_client::chess::Move & move);
  //private:
    //friend class state;
    std::string m_id; //mypiece id
    std::string m_pr; //mypiece id of mypiece removed
    int m_sx;
    int m_sy;
    int m_ex;
    int m_ey;
    bool firstMove;
};