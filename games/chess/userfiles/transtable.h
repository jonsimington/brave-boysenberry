#pragma once
#include <random>
bool checkForCastel(const state & s, const char x, const char y);
bool checkForKingCastel(const state & s, const char x, const char y);
unsigned long long int getPieceZooHash(const mypiece * p);
struct entry
{
  entry()
  {
    m_depth = -1;
    m_hash = 0;
  }
  unsigned long long int m_hash;
  char m_depth;
  bool m_prune;
  float m_eval;
};

const unsigned long long int TTSIZE = std::pow(10,6) * 6;
unsigned long long int ZOBTABLE[2][6][64];
unsigned long long int FMOVE[2];
unsigned long long int CASTELING[4];
unsigned long long int ENPASSANT[8][8];
entry TT[TTSIZE];

void getRand64(unsigned long long int & value)
{
   //std::cout << "getting rand\n";
   //static std::random_device rd; 
   static std::mt19937_64 e2(57381323);
   static std::uniform_int_distribution<unsigned long long int> dist(std::llround(std::pow(2,63)), std::llround(std::pow(2,64)) - 1);
   value = dist(e2);
   std::cout << value << std::endl;
   //std::cout << "done getting rand\n";
}

unsigned long long int getHash(const state & s, const bool move)
{
  //std::cout << "gethash\n";
  unsigned long long int hashValue = 0;
  hashValue ^= FMOVE[move];  
  if(s.can_EnPassant)
  {
    hashValue ^= ENPASSANT[s.px][s.py];
  }
  for(auto it = s.m_pieces.cbegin(); it != s.m_pieces.cend(); it++)
  {
    char type;
    if(it->second->inUse())
    {
      hashValue ^= getPieceZooHash(it->second);
    }
  }
  if(checkForKingCastel(s, 4, 0))
  {
    if(checkForCastel(s, 0, 0))
    {
      hashValue ^= CASTELING[0];
    }
    if(checkForCastel(s, 7, 0))
    {
      hashValue ^= CASTELING[1];
    }
  }
  if(checkForKingCastel(s, 4, 7))
  {
    if(checkForCastel(s, 7, 7))
    {
      hashValue ^= CASTELING[2];
    }
    if(checkForCastel(s, 0, 7))
    {
      hashValue ^= CASTELING[3];
    }
  }
  //std::cout << "done gethash\n";
  return hashValue;
}

void addEntry(const state & s, const bool turn, const int & depth, const float & eval, const bool & prune)
{
  //std::cout << "adding entry\n";
  unsigned long long int hashValue = getHash(s, turn);
  entry* e = &TT[hashValue % TTSIZE];
  if(depth > e->m_depth || (depth == e->m_depth && e->m_prune && !prune))
  {
    e->m_depth = depth;
    e->m_eval = eval;
    e->m_hash = hashValue;
    e->m_prune = prune;
  }
  //std::cout << "done adding entry\n";
}

void setTables()
{
  for(int i = 0; i < 2; i++)
  {
    for(int j = 0; j < 6; j++)
    {
      for(int k = 0; k < 64; k++)
      {
        getRand64(ZOBTABLE[i][j][k]);
      }
    }
  }
  getRand64(FMOVE[0]);
  getRand64(FMOVE[1]);
  for(int i = 0; i < 4; i++)
  {
    getRand64(CASTELING[i]);
  }
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      getRand64(ENPASSANT[i][j]);
    }
  }
}

bool checkForCastel(const state & s, const char x, const char y)
{
  return s.m_board[x][y].occupied() && s.m_board[x][y].getPiece().getType() == "Rook" && !s.m_board[x][y].getPiece().hasMoved();
}

bool checkForKingCastel(const state & s, const char x, const char y)
{
  return s.m_board[x][y].occupied() && s.m_board[x][y].getPiece().getType() == "King" && !s.m_board[x][y].getPiece().hasMoved();
}

bool check(const state & s, const bool turn, const int & depth, float & eval, bool & prune)
{
  //std::cout << "checking\n";
  unsigned long long int hashValue = getHash(s, turn);
  entry* e = &TT[hashValue % TTSIZE];
  if(e->m_depth < depth || hashValue != e->m_hash)
  {
    //if(hashValue != e->m_hash && e->m_depth >= depth)
    //{
      //std::cout << "bad!!!!!!!!!\n";
    //}
    //std::cout << "exitchecking\n";
    return false;
  }
  //std::cout << "good\n";
  eval = e->m_eval;
  prune = e->m_prune;
  //std::cout << "exitchecking\n";
  return true;
}

unsigned long long int getPieceZooHash(const mypiece * p)
{
  char type;
  if(p->getType() == "Pawn")
  {
    type = 0;
  }
  else if(p->getType() == "Knight")
  {
    type = 1;
  }
  else if(p->getType() == "Bishop")
  {
    type = 2;
  }
  else if(p->getType() == "Rook")
  {
    type = 3;
  }
  else if(p->getType() == "Queen")
  {
    type = 4;
  }
  else//else king
  {
    type = 5;
  }
  return ZOBTABLE[p->isFriendly()][type][p->hashPos()];
}