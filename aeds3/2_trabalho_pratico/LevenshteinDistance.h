#ifndef LevenshteinDistance_H
#define LevenshteinDistance_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Matrix.h"

#define MAXSTR 7000


int calcMinimum(int v1, int v2, int v3);


//retorna -1 para valores que ultrapassam valor
int calcLevenshteinDistance(char * model, char * test, int MinChange, int printMatrix);

#endif
