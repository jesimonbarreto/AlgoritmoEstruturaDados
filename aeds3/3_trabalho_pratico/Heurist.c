#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Graph.h"
#include "Heurist.h"



void colorGulos(Graph * g, int lenG, int *vm) { 

	int v=0, *verif;
	*vm=-1;
	verif = (int*)calloc(lenG, sizeof(int));
	
	for(; v<lenG; v++){
		Node *aux = g->adj[v].next;
		while(aux!=NULL){
			if(g->adj[aux->w].group!=-1){
				int p = g->adj[aux->w].group;				
				verif[p]++;
			}
			aux = aux->next;
		}	
		
		int i=0;
		while(i<lenG){
			if(verif[i]==0){
				g->adj[v].group = i;
				break;
			}
			i++;
		}
		if(i+1>*vm) *vm=i+1;
		i=0;
		for(;i < lenG;i++){
			verif[i]=0;
		}
	}

	free(verif);
}




