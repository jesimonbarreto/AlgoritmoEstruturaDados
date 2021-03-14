#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Graph.h"

#define vertex int


Node* NewNode( vertex w, Node* next) { 
   Node *a =(Node*) malloc( sizeof (Node));
   a->w = w;
   a->group = -1; 
   a->next = next;     
   return a;                         
}


Graph* NewGraph(vertex V) { 
	Graph * G = (Graph*) malloc(sizeof(Graph));
	G->numberVert = V; 
	G->numberEdge = 0;
	G->adj = (Node*) malloc( V * sizeof(Node));
	int v;
	for (v = 0; v < V; ++v){
		G->adj[v].w = v;
		G->adj[v].group = -1; 
	}
	return G;
}

void insertEdge(Graph* G, vertex v, vertex w) { 
	if(v<0 || w<0) return;
	if(v==w) return;

	for (Node* a = &G->adj[v]; a != NULL; a = a->next) 
		if (a->w == w) return;
	G->adj[v].next = NewNode( w, G->adj[v].next);
	G->adj[w].next = NewNode( v, G->adj[w].next);
   	G->numberEdge++;
}

void printGraph(Graph* G,int lenG) { 
	int v;
	for (v = 0; v < lenG; v++){
		printf("Vert: %d, set: %d  -> ", G->adj[v].w, G->adj[v].group);
		for (Node* a = G->adj[v].next; a != NULL; a = a->next)
			printf(" %d, ", a->w);
		printf("\n");
	}
	printf("\n");
}

void freeGraph(Graph* G, int size){
	int i=0;

	for(;i<size;i++){
		Node *a= G->adj[i].next;
		while(a!=NULL){
			Node *aux=a->next;
			free(a);
			a=aux;		
		}
	}
	free(G->adj);
	free(G);
}



