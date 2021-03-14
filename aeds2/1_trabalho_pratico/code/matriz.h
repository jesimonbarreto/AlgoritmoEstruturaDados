#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file.h"
#include "processing.h"


void printAll(int ** matriz, int nline, int nrow);
void printVector(int ** vector, int size);
void printLine(int ** matriz, int line,int nrow);
void printRow(int ** matriz, int row, int nline);
int getDistance(int ** matriz, int nCity1,int nCity2);
void getDistances(int ** matriz, int value, int maxPosition,int ** distances);

#endif