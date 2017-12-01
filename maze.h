#include "graph.h"

#define MAZE_LAST_LINE GRAPH_LINES - 1
#define MAZE_LAST_COLUM GRAPH_COLUNS - 1
#define MAZE_1_START_LINE 4
#define MAZE_1_START_COlUM 0
#define MAZE_1_END_LINE 0
#define MAZE_1_END_COLUM 4
#define MAZE_2_START_LINE 0
#define MAZE_2_START_COlUM 0
#define MAZE_2_END_LINE 4
#define MAZE_2_END_COLUM 2

Graph creates_basic_maze(){
  Graph maze;
  for(int line = 0; line < GRAPH_LINES; line++){
    for(int colum = 0; colum < GRAPH_COLUNS; colum ++){
      maze.node[line][colum].visited = 0;
      maze.node[line][colum].floor = 0;
      maze.node[line][colum].index = line* 10 + colum;
      if(line == 0){
        maze.node[line][colum].up_edge = NULL;
      }
      else{
        maze.node[line][colum].up_edge = &maze.node[line - 1][colum];
      }

      if(colum == 0){
        maze.node[line][colum].left_edge = NULL;
      }
      else{
        maze.node[line][colum].left_edge = &maze.node[line][colum - 1];
      }

      if(line == MAZE_LAST_LINE){
        maze.node[line][colum].down_edge = NULL;
      }
      else{
        maze.node[line][colum].down_edge = &maze.node[line + 1][colum];
      }

      if(colum == MAZE_LAST_COLUM){
        maze.node[line][colum].right_edge = NULL;
      }
      else{
        maze.node[line][colum].right_edge = &maze.node[line][colum + 1];
      }
    }
  }
  return maze;
}

Graph creates_maze_2(){
  Node maze_beginnig;
  Node maze_end;

  Graph maze = creates_basic_maze();

  maze.node[0][0].up_edge = &maze_beginnig;
  maze.node[0][1].down_edge = NULL;
  maze.node[0][2].down_edge = NULL;
  maze.node[0][3].down_edge = NULL;
  maze.node[1][1].up_edge = NULL;
  maze.node[1][1].right_edge = NULL;
  maze.node[1][2].up_edge = NULL;
  maze.node[1][2].left_edge = NULL;
  maze.node[1][3].up_edge = NULL;
  maze.node[1][3].right_edge = NULL;
  maze.node[1][3].down_edge = NULL;
  maze.node[1][4].left_edge = NULL;
  maze.node[2][0].right_edge = NULL;
  maze.node[2][1].left_edge = NULL;
  maze.node[2][2].down_edge = NULL;
  maze.node[2][2].right_edge = NULL;
  maze.node[2][3].up_edge = NULL;
  maze.node[2][3].left_edge = NULL;
  maze.node[2][3].right_edge = NULL;
  maze.node[2][4].left_edge = NULL;
  maze.node[3][0].right_edge = NULL;
  maze.node[3][1].down_edge = NULL;
  maze.node[3][1].left_edge = NULL;
  maze.node[3][2].up_edge = NULL;
  maze.node[3][3].down_edge = NULL;
  maze.node[3][3].right_edge = NULL;
  maze.node[3][4].left_edge = NULL;
  maze.node[4][1].up_edge = NULL;
  maze.node[4][1].right_edge = NULL;
  maze.node[4][2].down_edge = &maze_end;
  maze.node[4][2].left_edge = NULL;
  maze.node[4][3].up_edge = NULL;

  return maze;
}

Graph creates_maze_1(){
  Node maze_beginnig;
  Node maze_end;
  Graph maze = creates_basic_maze();

  maze.node[0][1].down_edge = NULL;
  maze.node[0][1].right_edge = NULL;
  maze.node[0][2].left_edge = NULL;
  maze.node[0][3].down_edge = NULL;
  maze.node[0][4].right_edge = &maze_end;
  maze.node[1][1].up_edge = NULL;
  maze.node[1][1].right_edge = NULL;
  maze.node[1][2].left_edge = NULL;
  maze.node[1][3].up_edge = NULL;
  maze.node[1][3].right_edge = NULL;
  maze.node[1][4].left_edge = NULL;
  maze.node[1][4].down_edge = NULL;
  maze.node[2][0].right_edge = NULL;
  maze.node[2][1].down_edge = NULL;
  maze.node[2][1].left_edge = NULL;
  maze.node[2][2].down_edge = NULL;
  maze.node[2][2].right_edge = NULL;
  maze.node[2][3].down_edge = NULL;
  maze.node[2][3].left_edge = NULL;
  maze.node[2][4].up_edge = NULL;
  maze.node[3][0].down_edge = NULL;
  maze.node[3][0].right_edge = NULL;
  maze.node[3][1].up_edge = NULL;
  maze.node[3][1].left_edge = NULL;
  maze.node[3][2].up_edge = NULL;
  maze.node[3][2].down_edge = NULL;
  maze.node[3][3].up_edge = NULL;
  maze.node[3][3].right_edge = NULL;
  maze.node[3][4].left_edge = NULL;
  maze.node[4][0].up_edge = NULL;
  maze.node[4][0].left_edge = &maze_beginnig;
  maze.node[4][2].up_edge = NULL;
  maze.node[4][1].right_edge = NULL;
  maze.node[4][2].left_edge = NULL;

  return maze;
}

Graph creates_maze_3(){
  Graph maze = creates_maze_2();
  maze.node[1][1].floor = 1;
  maze.node[1][2].floor = 1;
  maze.node[1][3].floor = 1;
  maze.node[2][1].floor = 1;
  maze.node[2][3].floor = 1;
  maze.node[3][1].floor = 1;
  maze.node[3][2].floor = 1;
  maze.node[3][3].floor = 1;
  return maze;
}

void print_maze(Graph maze,int start_line,int start_colum,int end_line,int end_colum){

  for(int line = 0; line < GRAPH_LINES; line++){
    for(int i = 0; i < 2; i++){
      printf("\n");
      if(i){
        for(int colum = 0; colum < GRAPH_COLUNS; colum++){
          if(maze.node[line][colum].left_edge == NULL){
            printf("|");
          }
          else{
            printf(" ");
          }
          if(line == start_line && colum == start_colum){
            printf(" S ");
          }
          else if(line == end_line && colum == end_colum){
            printf(" E ");
          }
          else{
            if(maze.node[line][colum].floor == 0){
              printf(" # ");
            }
            else{
              printf(" @ ");
            }
          }
        }
        if(maze.node[line][MAZE_LAST_COLUM].right_edge == NULL){
          printf("|");
        }
        else{
          printf(" ");
        }
      }
      else{
        for(int colum = 0; colum < GRAPH_COLUNS; colum++){
          printf(" ");
          if(maze.node[line][colum].up_edge == NULL){
            printf("---");
          }
          else{
            printf("   ");
          }
        }
      }
    }
  }
  printf("\n");
  for(int colum = 0;colum < GRAPH_COLUNS; colum++){
    printf(" ");
    if(maze.node[MAZE_LAST_LINE][colum].down_edge == NULL){
      printf("---");
    }
    else{
      printf("   ");
    }
  }
  printf("\n\n");

}

void print_maze_1(Graph maze){
  print_maze(maze,MAZE_1_START_LINE,MAZE_1_START_COlUM,MAZE_1_END_LINE,MAZE_1_END_COLUM);
}

void print_maze_2(Graph maze){
  print_maze(maze,MAZE_2_START_LINE,MAZE_2_START_COlUM,MAZE_2_END_LINE,MAZE_2_END_COLUM);
}

void solves_maze(Graph maze,int start_line,int start_colum, int end_line,
                  int end_colum){

  Path answer = breadth_first_search(maze,start_line,start_colum,end_line,end_colum);
  printf("\n\n");
  printf("Number of moviments: %d\n",answer.distance);
  printf("Moviments: ");
  for(int i = 0; i < answer.distance; i++ ){
    if(answer.moviments[i] == 'u'){
      printf("up ");
    }
    else if(answer.moviments[i] == 'd'){
      printf("down ");
    }
    else if(answer.moviments[i] == 'l'){
      printf("left ");
    }
    else{
      printf("right ");
    }
  }
  printf("\n\n");
}

void solves_maze_1(Graph maze){
  maze.node[MAZE_1_START_LINE][MAZE_1_START_COlUM].left_edge = NULL;
  maze.node[MAZE_1_END_LINE][MAZE_1_END_COLUM].right_edge = NULL;
  solves_maze(maze,MAZE_1_START_LINE,MAZE_1_START_COlUM,MAZE_1_END_LINE,
              MAZE_1_END_COLUM);
}

void solves_maze_2(Graph maze){
  maze.node[MAZE_2_START_LINE][MAZE_2_START_COlUM].up_edge = NULL;
  maze.node[MAZE_2_END_LINE][MAZE_2_END_COLUM].down_edge = NULL;
  solves_maze(maze,MAZE_2_START_LINE,MAZE_2_START_COlUM,MAZE_2_END_LINE,
              MAZE_2_END_COLUM);
}

void solves_maze_3(Graph maze,int start_line,int start_colum, int end_line,
                  int end_colum){

  Path answer = shortest_path(maze,start_line,start_colum,end_line,end_colum);
  printf("\n\n");
  printf("Minimum time: %d\n",answer.distance);
  printf("Number of moviments: %d\n",answer.distance);
  printf("Moviments: ");
  for(int i = 0; i < answer.distance; i++ ){
    if(answer.moviments[i] == 'u'){
      printf("up ");
    }
    else if(answer.moviments[i] == 'd'){
      printf("down ");
    }
    else if(answer.moviments[i] == 'l'){
      printf("left ");
    }
    else{
      printf("right ");
    }
  }
  printf("\n\n");
}

void solves_maze_23(Graph maze){
  maze.node[MAZE_2_START_LINE][MAZE_2_START_COlUM].up_edge = NULL;
  maze.node[MAZE_2_END_LINE][MAZE_2_END_COLUM].down_edge = NULL;
  solves_maze_3(maze,MAZE_2_START_LINE,MAZE_2_START_COlUM,MAZE_2_END_LINE,
              MAZE_2_END_COLUM);
}
