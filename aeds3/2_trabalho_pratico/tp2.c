#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Matrix.h"
#include "LevenshteinDistance.h"
#include "Sort.h"
#include <time.h>


#define MAXSTR 7000



int main(int argc, char * argv[]){
	//clock_t tInicio, tFim;
	//double tDecorrido;
	int D, n, contlist = 0;
	char q[MAXSTR], d[MAXSTR];
	word * list;

	scanf("%d",&D);
    	scanf("%d",&n);
	scanf("%s",q);
	
	list = (word*) malloc(sizeof(word)*D);
    	//tInicio = clock();
	/*seu codigo vem aqui*/
	//ler linha a linha processando a distancia e so adiciona no vetor as palavras que tiverem distancia menor ou igual a n
	int i, save;
	for(i = 0; i < D; i++){
		scanf("%s",d);
		//Funçao retorna -1 para valor de operaçoes maior que n, caso contrario retorna o numero de operaçoes necessarias
		save = calcLevenshteinDistance(q, d, n, 0);		
		if(save > -1){
			strcpy(list[contlist].name, d);			
			list[contlist].NOperat = save;	
			contlist++;
		}
			
	}
	
    	//Ordena list com base no tamanho de contlist
	sort(list, contlist, sizeof(word), compar);

	for(i = 0; i < contlist; i++){
		printf("%s\n",list[i].name);
	}
	//tFim = clock();

	/*calcula aproximadamente o tempo em milisegundos gasto entre as duas chamadas de clock()*/
	//tDecorrido = ((double) (tFim - tInicio) / (CLOCKS_PER_SEC));
    return 0;

}
