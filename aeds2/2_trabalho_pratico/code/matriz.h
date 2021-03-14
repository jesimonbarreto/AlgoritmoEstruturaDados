#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


	typedef struct{
		 int x; 
		 int y;
	} Point;

void printAll(int ** matriz, int nline, int ncol);
int wordExistGrid(char * word, int ** grid, int lm, int lc);
int wordExist(char * word, int ** grid, int m, int i, int j, int p, int ind, Point ** vis);
void printVector(int ** vector, int size);
void printLine(int ** matriz, int line,int ncol);
void printRow(int ** matriz, int col, int nline);
void convertMinforMai(char * word,int size);

#endif