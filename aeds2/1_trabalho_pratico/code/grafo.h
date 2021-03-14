#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file.h"
#include "processing.h"
#include "matriz.h"

//passando uma cidade, adiciona ao caminho percorrido 
	/*
	path lista de cidades, sizePath é o somatorio do caminho, vertice é a cidade para adicionar,distance, é a distancia até a cidade
		position é a posição para inserir, sizeVerticeP é a quantidade de cidades no vetor path
	*/
	void addPath(int ** path,int * sizePath,int vertice,int distance,int position,int * sizeVerticeP);
	//calcula as distancias da nova cidade sendo colocada entre as cidades que ja estão no caminho
	void calcVertices(int ** matriz,int ** path,int * sizePath,int * sizeVectorP,int vertice);
	//passando um vertice, adiciona ao caminho percorrido 
	void addVertice(int ** path,int * sizePath,int vertice,int distance,int position,int * sizeVerticeP);
	
	//Passado o vetor de distancias da cidade para todas as outras cidades 
	//retorna a cidade de menor caminho, sem contar o caminho para a propria cidade que é 0
	int getSmaller(int ** distancesVector, int sizeVector);
	
	//verifica a cidade faz parte do caminho, se retornar 0 nao faz parte, se retornar 1 faz
	int verifyPath(int ** path, int sizeVerticeP, int vertice);
	

#endif