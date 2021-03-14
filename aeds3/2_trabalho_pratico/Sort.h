#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXSTR 7000

typedef struct wordR {
	char name[MAXSTR];
	int NOperat;
} word;

int compar(const void * a, const void * b);
void sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));


#endif
