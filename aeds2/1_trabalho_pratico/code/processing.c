#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file.h"
#include "processing.h"


	//calcula a distancia baseado nos pontos do plano
	int distance(Coordinate city1,Coordinate city2){
		int distance = 0;
		float x = (city2.x-city1.x);
		float y = (city2.y-city1.y);
		distance = sqrt((x*x)+(y*y)) + 0.5;
		return distance;
	}
	//coloca valores na matriz com a representação de dados baseada em matriz de incidencia
	void processingData(int ***distances, Data * data){
		(*distances) = (int** ) malloc(sizeof(int*) * (data->nCitys));
		int i=0,j=0;
		while(i<(data->nCitys)){
			(*distances)[i] = (int*) calloc( data->nCitys, sizeof(int));
			i++;
		}
		
		for(i=0;i<(data->nCitys);i++){
			for(j=0;j<(data->nCitys);j++){
				if(j>i){
					(*distances)[i][j] = distance(data->cdnt[i],data->cdnt[j]);
				} 
			}
		}
		
		
	}
