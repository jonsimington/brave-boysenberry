#pragma once
/*my history table is a move from one space on the board
to another space on the board*/
unsigned int historyTable[64][64] = {0};

int getHistory(const action & a)
{
  return historyTable[a.getHashFrom()][a.getHashTo()];
}

struct ordering
{
  bool operator () (const action & lhs, const action & rhs) const
  {
    return getHistory(lhs) > getHistory(rhs);
  }
};

void addToHistory(const action & a, const int & depth)
{
  historyTable[a.getHashFrom()][a.getHashTo()] += depth * depth;
}

void clearHistoryTable()
{
  for(int i = 0; i < 64; i++)
  {
    for(int j = 0; j < 64; j++)
    {
      historyTable[i][j] = 0;
    }
  }
}