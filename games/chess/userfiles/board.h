#pragma once
#include "piece.h"
class piece;

template <typename T>
class board
{
  public:
    board();
    ~board();
    board(const board<T> & rhs);
    const board<T> & operator = (const board<T> & rhs);
    board(board<T> && rhs);
    const T* operator [] (const int & i) const;
    T* operator [] (const int & i);
  private:
    T** m_data;
    static int const m_length;
    friend piece;
};

#include "board.hpp"