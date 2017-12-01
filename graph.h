#include <stdio.h>
#include <stdlib.h>

#define GRAPH_LINES 5
#define GRAPH_COLUNS 5


typedef struct path{
  char *moviments;
  int time;
  int distance;
} Path;

typedef struct node{
  int index;
  int floor;
  int visited;
  Path smaller_path;
  struct node *up_edge;
  struct node *down_edge;
  struct node *left_edge;
  struct node *right_edge;
} Node;

typedef struct heep{
  int size;
  Node *nodes_list;
} Heep;


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

Path adds_moviment_to_path_2(Path path, char moviment,int same_floor){
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
  if(same_floor){
    new_path.time = path.time + 2;
  }
  else{
    new_path.time = path.time + 6;
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

Heep heepify(Heep heep){
  if(heep.size >= 2){
    for(int i = 0; i < heep.size/2;i++){
      if((i+1)*2 < heep.size){
        if(heep.nodes_list[i].smaller_path.time > heep.nodes_list[(i+1)*2].smaller_path.time ){
          Node aux = heep.nodes_list[i];
          heep.nodes_list[i]= heep.nodes_list[(i+1)*2];
          heep.nodes_list[(i+1)*2] = aux;
        }
      }
      if(heep.nodes_list[i].smaller_path.time > heep.nodes_list[(i+1)*2-1].smaller_path.time ){
        Node aux = heep.nodes_list[i];
        heep.nodes_list[i]= heep.nodes_list[(i+1)*2-1];
        heep.nodes_list[(i+1)*2-1] = aux;
      }
    }
  }
  return heep;
}

Heep add_heep(Heep heep, Node node){
  Node *new_nodes_list;
  new_nodes_list = (Node*)malloc((heep.size + 1) * sizeof(Node));
  if(heep.size > 0){
    for(int i = 0; i < heep.size; i++){
      new_nodes_list[i] = heep.nodes_list[i];
    }
  }
  new_nodes_list[heep.size] = node;
  heep.nodes_list = new_nodes_list;
  heep.size++;
  return heepify(heep);
}

Heep remove_heep(Heep heep){
  Node *new_nodes_list;
  new_nodes_list = (Node*)malloc((heep.size - 1) * sizeof(Node));
  for(int i = 0; i < heep.size - 1; i++){
    new_nodes_list[i] = heep.nodes_list[i + 1];
  }
  heep.nodes_list = new_nodes_list;
  heep.size--;
  return heepify(heep);
}

Path shortest_path(Graph graph,int line,int colum, int end_line, int end_colum){
  int end_index = end_line * 10 + end_colum;
  Heep heep;
  heep.size = 0;
  graph.node[line][colum].smaller_path.time = 0;
  graph.node[line][colum].smaller_path.distance = 0;
  graph.node[line][colum].smaller_path.moviments = NULL;
  heep = add_heep(heep,graph.node[line][colum]);
  while(heep.size > 0){
    if(end_index == heep.nodes_list[0].index){
      return heep.nodes_list[0].smaller_path;
    }

    line = heep.nodes_list[0].index / 10;
    colum = heep.nodes_list[0].index % 10;
    heep = remove_heep(heep);

    if(graph.node[line][colum].up_edge != NULL){
      int same_floor = 0;
      if(graph.node[line - 1][colum].floor == graph.node[line][colum].floor ){
        same_floor = 1;
      }
      graph.node[line - 1][colum].smaller_path = adds_moviment_to_path_2(graph.node[line][colum].smaller_path,'u',same_floor);
      heep = add_heep(heep,graph.node[line - 1][colum]);
    }
    if(graph.node[line][colum].down_edge != NULL){
      int same_floor = 0;
      if(graph.node[line + 1][colum].floor == graph.node[line][colum].floor ){
        same_floor = 1;
      }
      graph.node[line + 1][colum].smaller_path = adds_moviment_to_path_2(graph.node[line][colum].smaller_path,'d',same_floor);
      heep = add_heep(heep,graph.node[line + 1][colum]);
    }
    if(graph.node[line][colum].left_edge != NULL){
      int same_floor = 0;
      if(graph.node[line][colum - 1].floor == graph.node[line][colum].floor ){
        same_floor = 1;
      }
      graph.node[line][colum - 1].smaller_path = adds_moviment_to_path_2(graph.node[line][colum].smaller_path,'l',same_floor);
      heep = add_heep(heep,graph.node[line][colum - 1]);
    }
    if(graph.node[line][colum].right_edge != NULL){
      int same_floor = 0;
      if(graph.node[line][colum + 1].floor == graph.node[line][colum].floor ){
        same_floor = 1;
      }
      graph.node[line][colum + 1].smaller_path = adds_moviment_to_path_2(graph.node[line][colum].smaller_path,'r',same_floor);
      heep = add_heep(heep,graph.node[line][colum + 1]);
    }
  }
}
