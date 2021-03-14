#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

	 typedef struct {
	 float x;
	 float y; 
	} Coordinate;

	typedef struct {
		Coordinate * cdnt;
		int nCitys;
	} Data;

	//Abre arquivo, se tiver erro retorna -1 
	int openFile(FILE ** file, char * dir, char * mode);
	//passar struct como parametro
	//pega os dados do arquivo, salva os valores em ordem em um vetor double e a data em uma matriz int
	int readData(FILE * file, Data ** dataF);
	void writeFile(int ** vector, int size,float time,int distanceT);
	void closeFile(FILE * file);

#endif