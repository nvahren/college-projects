#include <stdio.h>
#include <unistd.h>

#define B_SIZE 40

void initial_setup( char board_a[B_SIZE][B_SIZE], char board_b[B_SIZE][B_SIZE] ){

  int x, y;

  for( x = 0; x < B_SIZE; x++ ){
    for( y = 0; y < B_SIZE; y++ ){
      board_a[y][x] = ' ';
      board_b[y][x] = ' ';
    }
  }
}

void disp_board( char board_a[B_SIZE][B_SIZE] ){

  int i, j;

  printf("\033[2J\033[H");
  
  for( j = 0; j < B_SIZE; j++ ){
    for( i = 0; i < B_SIZE; i++ ){
      printf("%c",board_a[j][i]);
    }
    printf("\n");
  }

}

void update_board( char board_a[B_SIZE][B_SIZE], char board_b[B_SIZE][B_SIZE] ){

  int i, j;
  int liveNeighboringCells;
  for( j = 0; j < B_SIZE; j++ ){
    for( i = 0; i < B_SIZE; i++ ){
      board_b[j][i] = board_a[j][i];
    }
  }
  
  for( j = 0; j < B_SIZE; j++ ){
    for( i = 0; i < B_SIZE; i++ ){

      liveNeighboringCells = 0;

      if ((board_b[j+1][i] == 'X') && (j < (B_SIZE - 1))){
        liveNeighboringCells++;
      }
      if ((board_b[j+1][i+1] == 'X') && (j < (B_SIZE - 1)) && (i < (B_SIZE - 1))){
        liveNeighboringCells++;
      }
      if ((board_b[j][i+1] == 'X') && (i < (B_SIZE - 1))){
        liveNeighboringCells++;
      }
      if ((board_b[j-1][i+1] == 'X') && (j > 0) && (i < (B_SIZE - 1))){
        liveNeighboringCells++;
      }
      if ((board_b[j-1][i] == 'X') && (j > 0)){
        liveNeighboringCells++;
      }
      if ((board_b[j-1][i-1] == 'X') && (j > 0) && (i > 0)){
        liveNeighboringCells++;
      }
      if ((board_b[j][i-1] == 'X') && (i > 0)){
        liveNeighboringCells++;
      }
      if ((board_b[j+1][i-1] == 'X') && (j < (B_SIZE - 1)) && (i > 0)){
        liveNeighboringCells++;
      }
      
      if ((board_b[j][i] == ' ') && (liveNeighboringCells == 3)){
        board_a[j][i] = 'X';
      }
      if ((board_b[j][i] == 'X') && ((liveNeighboringCells > 3) || (liveNeighboringCells < 2))){
        board_a[j][i] = ' ';
      }
      
    }
  }
}

int get_input( char board_a[B_SIZE][B_SIZE], int firstIteration ){

  char input = ' ';
  char input2 = ' ';
  int i, j;
  int x, y;
  int redrawRequired = 0;

  while(1){
    
      if (firstIteration){
        printf("Enter 'h' or '?' for help\n");
        firstIteration = 0;
      }
      printf("Input: ");
      scanf(" %c",&input);
    
    if ((input == 'h') || (input == '?')){
      printf("a: Create Cell\n");
      printf("r: Remove Cell\n");
      printf("s: Randomize Cells\n");
      printf("c: Clear Cells\n");
      printf("n: Next Frame\n");
      printf("p: Play Frames\n");
      printf("q: Quit\n\n");
    }
    
    if (input == 'a'){
      printf("Create Cell: ");
      scanf("%d %d",&i,&j);
      board_a[j][i] = 'X';
      redrawRequired = 1;
    }
    
    if (input == 'r'){
      printf("Remove Cell: ");
      scanf("%d %d",&i,&j);
      board_a[j][i] = ' ';
      redrawRequired = 1;
    }
    
    if (input == 's'){
      printf("Randomize? (y/n): ");
      scanf(" %c",&input2);
      if (input2 == 'y'){
        for( j = 0; j < B_SIZE; j++ ){
          for( i = 0; i < B_SIZE; i++ ){
            if (rand()%2 == 1){
              board_a[j][i] = 'X';
            }else{
              board_a[j][i] = ' ';
            } 
          }
        }
      redrawRequired = 1;
      }
    }
    
    if (input == 'c'){
      printf("Clear all cells? (y/n): ");
      scanf(" %c",&input2);
      if (input2 == 'y'){
        for( j = 0; j < B_SIZE; j++ ){
          for( i = 0; i < B_SIZE; i++ ){
            board_a[j][i] = ' ';
          }
        }
      redrawRequired = 1;
      }
    }
    
    if (input == 'n'){
      redrawRequired = 1;
      return 1;
    }
    
    if (input == 'p'){
      return 0;
    }
    
    if (input == 'q'){
      return -1;
    }
    
    if (redrawRequired){
      disp_board( board_a );
      redrawRequired = 0;
    }
  }

}

int main( void ){

  char board_a[B_SIZE][B_SIZE], board_b[B_SIZE][B_SIZE];
  int inputRequired = 1;
  int firstIteration = 1;
  
  srand(time(0));

  initial_setup( board_a, board_b );

  while(1){

    disp_board( board_a );

    if (inputRequired){
      inputRequired = get_input( board_a, firstIteration );
      firstIteration = 0;
    }

    update_board( board_a, board_b );

    if (inputRequired == 0){
      usleep(200000);
    }
    
    if (inputRequired == -1){
      return 0;
    }
  }

}
