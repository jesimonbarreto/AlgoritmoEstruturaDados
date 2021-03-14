#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file.h"
#include "grafo.h"

	
	
	


	//passando uma cidade, adiciona ao caminho percorrido 
	void addPath(int ** path,int * sizePath,int vertice,int distance,int position,int * sizeVerticeP){
		int i = (*sizeVerticeP);
		for(;i>position;i--){
			(*path)[i]=(*path)[i-1];
		}
		(*path)[position] = vertice;
		(*sizePath) += distance;
		(*sizeVerticeP)++;
	}
	
	//calcula as distancias da nova cidade sendo colocada entre as cidades que ja estão no caminho
	void calcVertices(int ** matriz,int ** path,int * sizePath,int * sizeVectorP,int vertice){
		//executará apenas se a cidade ainda nao foi adicionada no path
		int e=verifyPath(path,(*sizeVectorP),vertice);
		if(e==1){
			int i=0, *distanV= (int*) calloc( (*sizeVectorP)-1, sizeof(int));
			
			for(;i<((*sizeVectorP)-1);i++){
				distanV[i]= getDistance(matriz,vertice,(*path)[i]) + getDistance(matriz,vertice,(*path)[i+1]);
			}
			int positionSmaller = getSmaller(&distanV, ((*sizeVectorP)-1));
			//subtrair a distancia entre os dois que ja estavam no path
			(*sizePath)-=getDistance(matriz,(*path)[positionSmaller],(*path)[positionSmaller+1]);
			//adicionar as duas novas distancias que ligam a nova cidade a outras duas que ja existiam no path
			//a posição retornada será a uma a menos do que deve ser inserido 
			addPath(path,sizePath,vertice,distanV[positionSmaller],positionSmaller+1,sizeVectorP);
			free(distanV);
		}
	}
	
	//Passado o vetor de distancias da cidade para todas as outras cidades 
	//retorna menor caminho, sem contar o caminho para a propria cidade que é 0
	int getSmaller(int ** distancesVector, int sizeVector){
		
		int i,smaller=999999,pointer = -1;
		
		for(i=0;i<sizeVector;i++){
			
			if((*distancesVector)[i]!=0 && (*distancesVector)[i]<smaller){
				smaller=(*distancesVector)[i];
				pointer=i;
			}	
		}
		return pointer;
	}
	
	//verifica a cidade faz parte do caminho, se retornar 0 nao faz parte, se retornar 1 faz
	int verifyPath(int ** path, int sizeVerticeP, int vertice){
		int i=0,nExist = 1;
		
		for(i=0;i<sizeVerticeP;i++){
			if((*path)[i]==vertice){
				nExist=0;
				i=sizeVerticeP;
			}
		}
		return nExist;
	}
	
	
