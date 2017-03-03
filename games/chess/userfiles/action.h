#pragma once
#include "mypiece.h"
#include "../move.cpp"
#include <string>

class mypiece;
struct action
{
  public:
    action(const mypiece & pm, const mypiece & pr, const std::string promoteType = "");
    action(const mypiece & pm, const int & x, const int & y, const std::string promoteType = "");
    action(const cpp_client::chess::Move & move);
    
    std::string m_id; //mypiece id
    std::string m_pr; //mypiece id of mypiece removed
    std::string m_promoteType;
    int m_sx;
    int m_sy;
    int m_ex;
    int m_ey;
    bool firstMove;
};