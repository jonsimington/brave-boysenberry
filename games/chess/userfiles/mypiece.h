#pragma once
#include "action.h"
#include "board.h"
#include <vector>
#include <string>
class action;
class board;

class mypiece
{
  public:
    mypiece();
    mypiece(const int & x, const int & y, const std::string & id);
    mypiece(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved);
    void place(const int & x, const int & y);
    bool operator < (const mypiece & rhs) const;
    void move(const int & x, const int & y);
    void remove();
    int getX() const;
    int getY() const;
    bool isFriendly() const;
    std::string getId() const;
    virtual std::vector<action> possibleActions() const;
    virtual mypiece* clone() const;
    void copyValues(const mypiece* rhs);
    bool inUse() const;
    bool m_hasMoved;
    std::string getType() const;
    board* m_board;
  protected:
    bool m_friendly;
    int m_x;
    int m_y;
    bool m_inUse;
    std::string m_id;
    std::string m_type;
};