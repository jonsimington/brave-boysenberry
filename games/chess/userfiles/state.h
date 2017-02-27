#pragma once
#include "../game.hpp"
#include "../../../joueur/src/base_ai.hpp"
#include <set>
#include <vector>
#include "board.h"
#include "tile.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
class state
{
  public:
    state();
  private:
    board m_board;
    //friendly mypieces
    std::set<mypiece> m_fp;
    //enemy mypieces
    std::set<mypiece> m_ep;
};