#include <stdio.h>
#include <stdlib.h>

#define GRAPH_LINES 5
#define GRAPH_COLUNS 5


typedef struct path{
  char *moviments;
  int distance;
} Path;

typedef struct node{
  int index;
  int visited;
  Path smaller_path;
  struct node *up_edge;
  struct node *down_edge;
  struct node *left_edge;
  struct node *right_edge;
} Node;

typedef struct graph{
  Node node[GRAPH_LINES][GRAPH_COLUNS];
} Graph;

int** add_to_queue(int **queue, int queue_size, int line, int colum ){
  int **new_queue;
  new_queue = (int**)malloc(2 * sizeof(int*));
  new_queue[0] = (int*)malloc((queue_size+1) * sizeof(int));
  new_queue[1] = (int*)malloc((queue_size+1) * sizeof(int));

  if(queue_size > 0){
    for(int count = 0;count < queue_size; count++){
      new_queue[0][count] = queue[0][count];
      new_queue[1][count] = queue[1][count];
    }
  }
  new_queue[0][queue_size] = line;
  new_queue[1][queue_size] = colum;

  return new_queue;
}

int** remove_from_queue(int **queue, int queue_size){
  int **new_queue;
  new_queue = (int**)malloc(2 * sizeof(int*));
  new_queue[0] = (int*)malloc((queue_size-1) * sizeof(int));
  new_queue[1] = (int*)malloc((queue_size-1) * sizeof(int));

  for(int count = 0; count < queue_size - 1; count++){
    new_queue[0][count] = queue[0][count+1];
    new_queue[1][count] = queue[1][count+1];
  }
  return new_queue;
}

Path adds_moviment_to_path(Path path, char moviment){
  Path new_path;
  new_path.distance = path.distance + 1;
  new_path.moviments = (char*)malloc(new_path.distance*sizeof(char));
  if(new_path.distance == 1){
    new_path.moviments[0] = moviment;
  }
  else{
    for(int i = 0; i < path.distance; i++){
      new_path.moviments[i] = path.moviments[i];
    }
    new_path.moviments[path.distance] = moviment;
  }
  return new_path;
}


Path breadth_first_search(Graph graph,int line,int colum, int end_line,
                          int end_colum){
  int queue_size = 0;
  int **queue;
  int end_index = end_line * 10 + end_colum;
    if(graph.node[line][colum].visited == 0){
      queue = add_to_queue(queue,queue_size,line,colum);
      queue_size++;
      graph.node[line][colum].smaller_path.distance = 0;
      graph.node[line][colum].smaller_path.moviments = NULL;
      graph.node[line][colum].visited = 1;
      while(queue_size > 0){
        int node_line = queue[0][0];
        int node_colum = queue[1][0];
        if(end_index == graph.node[node_line][node_colum].index){
          return graph.node[node_line][node_colum].smaller_path;
        }
        queue = remove_from_queue(queue,queue_size);
        queue_size--;
        if(graph.node[node_line][node_colum].up_edge != NULL){
          if(graph.node[node_line-1][node_colum].visited == 0){
            queue = add_to_queue(queue, queue_size, node_line - 1,
                                  node_colum);
            graph.node[node_line-1][node_colum].smaller_path = adds_moviment_to_path(graph.node[node_line][node_colum].smaller_path,'u');
            queue_size++;
            graph.node[node_line-1][node_colum].visited = 1;
          }
        }
        if(graph.node[node_line][node_colum].down_edge != NULL){
          if(graph.node[node_line+1][node_colum].visited == 0){
            queue = add_to_queue(queue, queue_size, node_line + 1,
                                  node_colum);
            graph.node[node_line+1][node_colum].smaller_path = adds_moviment_to_path(graph.node[node_line][node_colum].smaller_path,'d');
            queue_size++;
            graph.node[node_line+1][node_colum].visited = 1;
          }
        }
        if(graph.node[node_line][node_colum].left_edge != NULL){
          if(graph.node[node_line][node_colum - 1].visited == 0){
            queue = add_to_queue(queue, queue_size, node_line,
                                  node_colum - 1);
            graph.node[node_line][node_colum-1].smaller_path = adds_moviment_to_path(graph.node[node_line][node_colum].smaller_path,'l');
            queue_size++;
            graph.node[node_line][node_colum-1].visited = 1;
          }
        }
        if(graph.node[node_line][node_colum].right_edge != NULL){
          if(graph.node[node_line][node_colum + 1].visited == 0){
            queue = add_to_queue(queue, queue_size, node_line,
                                  node_colum + 1);
            graph.node[node_line][node_colum+1].smaller_path = adds_moviment_to_path(graph.node[node_line][node_colum].smaller_path,'r');
            queue_size++;
            graph.node[node_line][node_colum+1].visited = 1;
          }
        }
      }
    }
}
