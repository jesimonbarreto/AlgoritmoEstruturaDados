#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Queue.h"


typedef struct Vertice{
    int id, age, nEdges, visited, *edges;
} Vertice; 

	
	void createGraph(Vertice ** vertices, int size);
	int verifyDuplicate(Vertice ** vertices, int sizeV, int id1, int id2);
	int binarySearch(Vertice ** vertices, int sizeV, int value);
	int insertEdge(Vertice ** vertices, int sizeV, int id1, int id2);
	void insertEdgeSelec(Vertice ** vertices, int positionAdd, int position);
	int search(Vertice ** vertices, int ** controlList, int * sizeLC);
	int visit(Vertice ** vertices, int ** controlL, int * sizeLs);
	
	

#endif