#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXSTR 7000

int** allocaMatrix(int l,int r);
void freeMatrix(int ** m, int l);
void printAll(int ** matriz, int nline, int nr);


#endif
