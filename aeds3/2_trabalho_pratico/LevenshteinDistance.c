#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Matrix.h"
#include "LevenshteinDistance.h"

#define MAXSTR 7000


int calcMinimum(int v1, int v2, int v3){
	if(v1<v2 && v1<v3) return v1;
	if(v2<v1 && v2<v3) return v2;
	return v3;
}


//retorna -1 para valores que ultrapassam valor
int calcLevenshteinDistance(char * model, char * test, int MinChange, int printMatrix){
	int sizeModel = strlen(model) + 1;
	int sizeTest = strlen(test) + 1;

	if(!sizeModel || !sizeTest) return -1;
	
	int ** matrix = allocaMatrix(sizeTest, sizeModel);
	int i = 0, j = 0;

	for(;i < sizeTest; i++){
		matrix[i][0] = i;
	}
	for(;j < sizeModel; j++){
		matrix[0][j] = j;
	}
	

	char CModel, CTest;
	int cost = 0; 
	for(i=1;i < sizeTest; i++){
		CTest = test[i-1];
		for(j=1;j < sizeModel; j++){
			CModel = model[j-1];
			
			if(CModel == CTest){
				cost = 0;
			}else{
				cost = 1;
			}
			int v1 = (matrix[i-1][j]) + 1;
			int v2 = (matrix[i][j-1]) + 1;
			int v3 = (matrix[i-1][j-1]) + cost;
			matrix[i][j] = calcMinimum(v1, v2, v3);
		}
	}
	
	int constG = matrix[sizeTest-1][sizeModel-1]; 
	
	if(printMatrix) printAll(matrix, sizeTest, sizeModel);

	freeMatrix(matrix, sizeTest);

	if(constG > MinChange) return -1;
	
	return constG; 
}
