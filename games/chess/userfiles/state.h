#pragma once
#include "../game.hpp"
#include "../../../joueur/src/base_ai.hpp"
#include "board.h"
#include <vector>
#include <map>
#include "utility.h"
class action;
class mypiece;
class board;

class state
{
  public:
    std::vector<action> possibleActionsF();
    std::vector<action> possibleActionsE();
    state();
    ~state();
    state(const state & rhs);
    state & operator = (const state & rhs);
    state & operator = (const cpp_client::chess::Game & g);
    state(const cpp_client::chess::Game & g);
    state operator + (const action & a) const;
    void applyAction(const action & a);
    void reverseAction(const action & a);
    void deleteData();
    float getValue() const;
    bool terminal() const;
    bool isDraw() const;
    void addToPrevious(const action & a);
    bool can_EnPassant; //is enpassant possible
    bool inCheck(const std::vector<mypiece*> & pieces) const;
    std::vector<action> possibleActions(const std::vector<mypiece*> & pieces);
    
    std::string m_id;
    board m_board; //the board
    std::vector<mypiece*> m_friendlyPieces;
    std::vector<mypiece*> m_enemyPieces;
    std::map<std::string, mypiece*> m_pieces;
    
    int px; //enpassant target cordinates
    int py; //enpassant target cordinates
    
    std::vector<int> lastCapture; //how many moves ago was there a capture or pawn movement
    std::vector<action> previous_actions; //previous actions
};