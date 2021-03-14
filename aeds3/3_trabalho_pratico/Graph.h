#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define vertex int

typedef struct node { 
   int w; 
   int group;
   struct node *next; 
} Node;

typedef struct graph {
   int numberVert; 
   int numberEdge; 
   Node *adj; 
} Graph;

Node* NewNode( vertex w, Node* next);
Graph* NewGraph(vertex V);
void insertEdge(Graph* G, vertex v, vertex w);
void printGraph(Graph* G, int lenG);
void freeGraph(Graph* G, int size);
#endif
