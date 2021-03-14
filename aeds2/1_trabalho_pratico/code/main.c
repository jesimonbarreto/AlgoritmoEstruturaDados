#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file.h"
#include "processing.h"
#include "matriz.h"
#include "grafo.h"
#include "cTime.h"


int main(int argc, char * argv[]){
	FILE * file;
	int ** mDistances, *path, sizePath=0, nCPath=0,* distanceV;
	float t=getTime();
	openFile(&file,argv[1],"r");

	Data * dataf = (Data*) malloc(sizeof(Data));

	
	readData(file,&dataf);
	
	closeFile(file);
	
	processingData(&mDistances, dataf);
	
	//inicialização do algoritmo primeiro passo
	path = (int*) calloc( dataf->nCitys+1, sizeof(int));
	//na posição 1 ja tem 0 que é a cidade de partida
	//adiciona 1 no numero de cidades 
	nCPath++;
	
	//Segundo passo
	//o tamanho total do caminho será do 0 até a cidade mais proxima
	//antes de passar pego as distancias do 0 pra qualquer cidade na matriz com todas as distancias
	getDistances(mDistances, path[0], dataf->nCitys,&distanceV);
	int positionSmaller = getSmaller(&distanceV, dataf->nCitys);
	
	addPath(&path,&sizePath,positionSmaller,distanceV[positionSmaller],nCPath,&nCPath);
	//terceiro
	//encontrar um e encaixar entre dois dos adicionados
    int i;
	for(i=0;i<dataf->nCitys;i++){
		calcVertices(mDistances,&path,&sizePath,&nCPath,i);
	}
	//inserindo a volta
	
	sizePath += getDistance(mDistances,path[nCPath-1],path[0]);
	nCPath++;
	
	float timef=getTime()-t;
	
	
	writeFile(&path, nCPath,timef,sizePath);
	
	
	for (i=0; i<dataf->nCitys; i++) free (mDistances[i]);
	free(mDistances);
	free(dataf->cdnt);
	free(dataf);
	free(path);
	free(distanceV);

	return 0;
}