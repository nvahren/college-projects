/**************
Nathan Vahrenberg - sudoku.cpp
A C++ program designed to solve sudoku puzzles
**************/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "sudoku.h"


using namespace std;

// Sudoku class constructor
sudoku::sudoku(const char *path){

  int i;
  
  ifstream file(path);
  std::string line;
  
  while(getline(file, line)){
    
    stringstream str(line);
    vector<int> vec;
    
    while(str >> i){
       vec.push_back(i);
    }
    
    board.push_back(vec);
  
  }
  
  file.close();
  
  // Generate blank 3D solution grid
  vector< vector<int> > vec1;
  vector<int> vec2;
  
  for( i = 0; i <= board.size(); i++ ){
    vec2.push_back(i);
  }
  
  for( i = 0; i < board.size(); i++ ){
    vec1.push_back(vec2);
  }
  
  for( i = 0; i < board.size(); i++ ){
    sol.push_back(vec1);
  }

}

// Print function
void sudoku::print(){

  int i, j;

  for(i = 0; i < board.size(); ++i){
    for(j = 0; j < board[i].size(); ++j){
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
  
}

// Function to solve puzzle
void sudoku::solve(){

  // Display puzzle before any changes are made
  cout << endl << endl;
  cout << "Initial:" << endl;
  print();

  int i, j;
  int complete = 0;

  while(!complete){
  
    computeSolutions();
  
    placeMove();
    
    complete = checkBoard();

  }
  
  // Display completed puzzle
  cout << endl << endl;
  cout << "Final:" << endl;
  print();
  cout << endl;

}

// Function to create 3D solution vector
void sudoku::computeSolutions(){
  
  // Remove invalid solutions
  int a, b, i, j, k, l, n;
  
  for( i = 0; i < board.size(); i++ ){
    for( j = 0; j < board.size(); j++ ){
    
      // Check if space is filled
      if( board[i][j] != 0 ){
        for( n = 0; n <= 9; n++ ){
          sol[i][j][n] = 0;
        }
      }
      
      // Check row
      for( k = 0; k < board.size(); k++ ){
        n = board[i][k];
        sol[i][j][n] = 0;
      }
      
      // Check column
      for( k = 0; k < board.size(); k++ ){
        n = board[k][j];
        sol[i][j][n] = 0;
      }
      
      // Check subgrid
      if( i <= 2 ){
        a = 0;
      }else if( i <= 5 ){
        a = 3;
      }else{
        a = 6;
      }
      if( j <= 2 ){
        b = 0;
      }else if( j <= 5 ){
        b = 3;
      }else{
        b = 6;
      }
      
      for( k = 0; k <= 2; k++ ){
        for( l = 0; l <= 2; l++ ){
          n = board[a+k][b+l];
          sol[i][j][n] = 0;
        }
      }
      
    }
  }
}

// Function to modify the sudoku board
void sudoku::placeMove(){

  int a, b, i, j, k, l, n;
  int numMoves;
  int loc;

  // A "Brute Force" algorithm to place any certain moves
  for( i = 0; i < board.size(); i++ ){
    for( j = 0; j < board.size(); j++ ){
    
      numMoves = 0;
      for( n = 1; n <= 9; n++ ){
        if( sol[i][j][n] != 0 ){
          numMoves++;
        }
      }
      if( numMoves == 1 ){
        n = 1;
        while( sol[i][j][n] == 0 ){
          n++;
        }
        board[i][j] = n;
        return;
      }
      
      
    }
  }

  // A smarter algorithm that checks how many locations a number can occupy
  
  // Check each row
  for( i = 0; i < board.size(); i++ ){
    for( n = 1; n <= 9; n++ ){
      numMoves = 0;  
      for( j = 0; j < board.size(); j++ ){
        if( sol[i][j][n] != 0 ){
          numMoves++;
        } 
      }
      if( numMoves == 1 ){
        for( j = 0; j < board.size(); j++ ){
          if( sol[i][j][n] == n ){
            board[i][j] = n;
            return;
          }
        }
      }
    }
  }

  // Check each column 
  for( j = 0; j < board.size(); j++ ){
    for( n = 1; n <= 9; n++ ){
      numMoves = 0;  
      for( i = 0; i < board.size(); i++ ){
        if( sol[i][j][n] != 0 ){
          numMoves++;
        } 
      }
      if( numMoves == 1 ){
        for( i = 0; i < board.size(); i++ ){
          if( sol[i][j][n] == n ){
            board[i][j] = n;
            return;
          }
        }
      }
    }
  }
  
  // Check each subgrid
  for( i = 0; i <= 6; i+=3 ){
    for( j = 0; j <= 6; j+=3 ){
      
      for( n = 1; n <= 9; n++ ){
      
        numMoves = 0;
        for( k = 0; k <= 2; k++ ){
          for( l = 0; l <= 2; l++ ){
          
            if( sol[i+k][j+l][n] != 0 ){
              numMoves++;
            }
          
          }
        }
        if( numMoves == 1 ){
          for( k = 0; k <= 2; k++ ){
            for( l = 0; l <= 2; l++ ){
              if( sol[i+k][j+l][n] == n ){
                board[i+k][j+l] = n;
                return;
              }
            }
          }
        }
      
      }
      
    }
  }
  
}

// Function to check if sudoku board is complete
int sudoku::checkBoard(){

  int i, j;  

  for(i = 0; i < board.size(); ++i){
    for(j = 0; j < board[i].size(); ++j){
      if( board[i][j] == 0 ){
        return 0;
      }
    }
  }
  
  return 1;
  
}
