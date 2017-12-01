#include "maze.h"

int main() {
  Graph maze = creates_maze_1();
  print_maze_1(maze);
  solves_maze_1(maze);

  maze = creates_maze_2();
  print_maze_2(maze);
  solves_maze_2(maze);

  maze = creates_maze_3();
  print_maze_2(maze);
  solves_maze_23(maze);

  return 0;
}
