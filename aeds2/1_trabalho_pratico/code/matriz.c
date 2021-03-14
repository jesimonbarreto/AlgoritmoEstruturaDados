#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file.h"
#include "processing.h"
#include "matriz.h"



	void printAll(int ** matriz, int nline, int nrow){
		int i=0,j=0;
		printf("\n");
		for(;i<nline;i++){
			for(j=0;j<nrow;j++){
				printf("%d ",matriz[i][j]);
			}
			printf("\n");
		}
	}
	
	void printVector(int ** vector, int size){
		int i=0;
		for(;i<size;i++){
				printf("%d ",(*vector)[i]);
		}
		printf("\n");
	}
	
	void printLine(int ** matriz, int line,int nrow){
		
		int i=0;
		for(;i<nrow;i++){
				printf("%d ",matriz[line][i]);
		}
		printf("\n");
	}
	void printRow(int ** matriz, int row, int nline){
		int i=0;
		for(;i<nline;i++){
				printf("%d ",matriz[i][row]);
				printf("\n");
		}
	}
	//retorna a distancia entre duas cidades
	int getDistance(int ** matriz, int nCity1,int nCity2){
		int distanceAB=0;
		//pq o valor só é inserido na matriz se j> i
		//a parte inferior da matriz ta com valores nulos
		if(nCity1>nCity2){
			distanceAB = matriz[nCity2][nCity1];
		}else{
			distanceAB = matriz[nCity1][nCity2];
		}
		return distanceAB;
	}
	
	//retorna um vetor com todas as distancias entre a cidade value e as outras cidades
	void getDistances(int ** matriz, int value, int maxPosition,int ** distances){
		int i=0;
		(*distances) = (int*) malloc(sizeof(int) * maxPosition);
		for(;i<maxPosition;i++){
			if(i<value){
				(*distances)[i]= matriz[i][value];
			}else{
				(*distances)[i]= matriz[value][i];
			}
		}
	}