/**************
Nathan Vahrenberg - sudoku.cpp
**************/
#include <iostream>
#include <string>
#include "sudoku.h"

using namespace std;

int main(){

  // Sudoku puzzle files can be specified by changing this string
  sudoku s9("sudoku3.txt");
  
  s9.solve();

  return 0;

}
