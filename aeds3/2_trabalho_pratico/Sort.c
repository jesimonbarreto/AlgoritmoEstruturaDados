#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Sort.h"

#define MAXSTR 7000

int compar(const void * a, const void * b){
	word* wA = (word*) a;
	word* wB = (word*) b;
 
	if(wA->NOperat < wB->NOperat) return -1;
	if(wA->NOperat > wB->NOperat) return 1;
	
	char *SWA =  wA->name;
	char *SWB =  wB->name;

	int i = 0;
	while(i<MAXSTR){
		if(SWA[i]=='\0' && SWB[i]=='\0') return 0;
		if(SWA[i]=='\0' || SWA[i] < SWB[i]) return -1;		
		if(SWB[i]=='\0' || SWA[i] > SWB[i]) return 1;
		i++;
	}

	return 0;
}

void sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)){

	qsort(base, nitems, size, compar);

}
