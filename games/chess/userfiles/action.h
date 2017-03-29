#pragma once
#include "../move.cpp"
#include <string>
class mypiece;

class action
{
  public:
    action();
    action(const mypiece & pm, const mypiece & pr, const std::string promoteType = "");
    action(const mypiece & pm, const int & x, const int & y, const std::string promoteType = "");
    action(const mypiece & pm, const mypiece & pr, bool enPassant);
    action(const cpp_client::chess::Move & move);
    bool operator == (const action & rhs) const;
    bool operator != (const action & rhs) const;
    bool operator < (const action & rhs) const;
    
    std::string m_id; //mypiece id
    std::string m_pr; //mypiece id of mypiece removed
    std::string m_promoteType; //what a piece is being promoted to
    std::string m_promoteFrom; //what a piece is being promoted from (i know its always a pawn)
    int m_sx;  //source x location
    int m_sy;  // source y location
    int m_ex;  //end x location
    int m_ey;  //end y location
    bool m_enPassant; //is the move using enPassant?
    bool m_firstMove; //is it the piece's first move?
};