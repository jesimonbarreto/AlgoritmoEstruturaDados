#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Graph.h"
#include "Heurist.h"
#include <time.h>

#define vertex int


int main(){
	//clock_t tInicio, tFim;
	//double tDecorrido;
	int N, M, i=0, r;
	Graph *graph;	

	scanf("%d",&N);
	scanf("%d",&M);
	//criar grafo com tamanho N
	graph = NewGraph(N);
	//ler conexoes e adicionar arestas no grafo
	for(i=0; i < M; i++){
		int v, w;
		scanf("%d %d",&v,&w);
		v--;
		w--;
		//insert edge v-w
		insertEdge(graph, v, w);
	}
	//tInicio = clock();
	//printGraph(graph, N);
	//chamar algoritmo para atribuir 
	//resolution()
	colorGulos(graph, N, &r);
	//printGraph(graph, N);
	//colocar no arquivo +1 
	//ler linha a linha processando a distancia e so adiciona no vetor as palavras que tiverem distancia menor ou igual a n
	
	//tFim = clock();
	//printf("%d\n", r);
	/*calcula aproximadamente o tempo em milisegundos gasto entre as duas chamadas de clock()*/
	//tDecorrido = ((double) (tFim - tInicio) / (CLOCKS_PER_SEC));
	//printf("%lf\n", tDecorrido);
	FILE *out;
	out = fopen("rodada.txt", "w");
	fprintf(out, "%d\n", r);
	fclose(out);
	out = fopen("alocacao.txt", "w");
	for(i=0; i<N; i++){
		fprintf(out,"%d %d\n", graph->adj[i].w+1, graph->adj[i].group+1);
	}
	fclose(out);
	freeGraph(graph, N);
	//free todos os nos de alocacao
    return 0;

}
