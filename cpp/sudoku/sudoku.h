/**************
Nathan Vahrenberg - sudoku.cpp
**************/
#ifndef SUDOKU_H
#define SUDOKU_H
#include <vector>

using namespace std;

class sudoku{

  public:
    sudoku(const char*);
    void print();
    void solve();
    void computeSolutions();
    void placeMove();
    int checkBoard();
  
  private:
    vector< vector<int> > board;
    vector< vector< vector<int> > > sol;
    
};

#endif
