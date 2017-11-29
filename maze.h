#include <stdio.h>
#include <stdlib.h>

#define MAZE_LINES 3
#define MAZE_COLUNS 3
#define MAZE_LAST_LINE MAZE_LINES - 1
#define MAZE_LAST_COLUM MAZE_COLUNS - 1

typedef struct node{
  int visited;
  struct node *up_edge;
  struct node *down_edge;
  struct node *left_edge;
  struct node *right_edge;
} Node;

typedef struct maze{
  Node quadrant[MAZE_LINES][MAZE_COLUNS];
} Maze;

Maze creates_maze(){
  Maze maze;
  for(int line = 0; line < MAZE_LINES; line++){
    for(int colum = 0; colum < MAZE_COLUNS; colum ++){
      maze.quadrant[line][colum].visited = 0;
      if(line == 0){
        maze.quadrant[line][colum].up_edge = NULL;
      }
      else{
        maze.quadrant[line][colum].up_edge = &maze.quadrant[line - 1][colum];
      }

      if(colum == 0){
        maze.quadrant[line][colum].left_edge = NULL;
      }
      else{
        maze.quadrant[line][colum].left_edge = &maze.quadrant[line][colum - 1];
      }

      if(line == MAZE_LAST_LINE){
        maze.quadrant[line][colum].down_edge = NULL;
      }
      else{
        maze.quadrant[line][colum].down_edge = &maze.quadrant[line + 1][colum];
      }

      if(colum == MAZE_LAST_COLUM){
        maze.quadrant[line][colum].right_edge = NULL;
      }
      else{
        maze.quadrant[line][colum].right_edge = &maze.quadrant[line][colum + 1];
      }
    }
  }
  return maze;
}

void print_maze(Maze maze){

  for(int line = 0; line < MAZE_LINES; line++){
    for(int i = 0; i < 2; i++){
      printf("\n");
      if(i){
        for(int colum = 0; colum < MAZE_COLUNS; colum++){
          if(maze.quadrant[line][colum].left_edge == NULL){
            printf("|");
          }
          else{
            printf(" ");
          }
          printf("%d", maze.quadrant[line][colum].visited);
        }
        if(maze.quadrant[line][MAZE_LAST_COLUM].right_edge == NULL){
          printf("|");
        }
        else{
          printf(" ");
        }
      }
      else{
        for(int colum = 0; colum < MAZE_COLUNS; colum++){
          printf(" ");
          if(maze.quadrant[line][colum].up_edge == NULL){
            printf("_");
          }
          else{
            printf(" ");
          }
        }
      }
    }
  }
  printf("\n");
  for(int colum = 0;colum < MAZE_COLUNS; colum++){
    printf(" ");
    if(maze.quadrant[MAZE_LAST_LINE][colum].down_edge == NULL){
      printf("_");
    }
    else{
      printf(" ");
    }
  }
  printf("\n\n");

}
