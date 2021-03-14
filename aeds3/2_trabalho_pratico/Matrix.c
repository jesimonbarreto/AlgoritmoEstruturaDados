#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Matrix.h"

#define MAXSTR 7000

int** allocaMatrix(int l,int r){ 
 
	int i,j; 

	int **m = (int**)malloc(l * sizeof(int*)); 

	for (i = 0; i < l; i++){ 
		m[i] = (int*) malloc(r * sizeof(int)); 
		for (j = 0; j < r; j++){ 
		    m[i][j] = 0; 
		}
	}

	return m; 
}

void freeMatrix(int ** m, int l){
	int i; 

	for (i = 0; i < l; i++){ 
		free(m[i]);	
	}

	free(m); 
}

void printAll(int ** matriz, int nline, int nr){
	int i=0,j=0;
	printf("\n");
	for(;i<nline;i++){
		for(j=0;j<nr;j++){
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
}


