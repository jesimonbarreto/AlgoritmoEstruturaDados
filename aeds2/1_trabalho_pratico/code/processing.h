#ifndef PROCESSING_H
#define PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file.h"

	int distance(Coordinate city1,Coordinate city2);
	void processingData(int ***distances, Data * data);

#endif