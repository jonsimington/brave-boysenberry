#pragma once
#include <vector>
#include <string>
#include "action.h"
class state;
class board;

class mypiece
{
  public:
    mypiece();
    mypiece(const int & x, const int & y, const std::string & id);
    mypiece(const int & x, const int & y, const std::string & id, board & b, bool friendly, bool hasMoved);
    void place(const int & x, const int & y);
    bool operator < (const mypiece & rhs) const;
    unsigned int hashPos() const;
    void move(const int & x, const int & y);
    void remove();
    int getX() const;
    int getY() const;
    bool isFriendly() const;
    std::string getId() const;
    /*gets all possible actions from the piece values passed are enpassant x and y cordinates and if it can
    enpassant*/
    virtual void possibleActions(const state & s, std::vector<action> & allActions) const;
    virtual mypiece* clone() const; //clones the piece sending a ptr that points to the new piece
    virtual float getValue(const state & s) const;
    void copyValues(const mypiece* rhs); //copies the values from the rhs piece
    bool hasMoved() const;
    bool inUse() const;
    std::string getType() const;
    virtual int getDirection() const; //used for pawn if 0 its white if 1 its black
    bool m_hasMoved; //has the peice moved
    bool m_friendly; //is the piece myn
    char m_x; //x cordinate
    char m_y; //y cordinate
    bool m_inUse; //if the piece is in use
    std::string m_id; //the piece id
    std::string m_type; //the type id
};