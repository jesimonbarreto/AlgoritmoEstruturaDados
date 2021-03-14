#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Queue.h"



void addPosition(int ** controLS, int itens, int * sizeLS, int sizeI){
    (*controLS) = realloc((*controLS), ((*sizeLS) + (sizeI)) * sizeof(int));
    (*controLS)[(*sizeLS)] = itens;
    (*sizeLS) += sizeI;
}
 
void removePosition(int ** controLS, int * sizeLS){
    int i = 0;
    for(; i < (*sizeLS) - 1; i++ ){
        (*controLS)[i] = (*controLS)[i+1];
    }
    (*sizeLS)--;
    (*controLS) = realloc((*controLS), (*sizeLS) * sizeof(int));
}
 
int exist(int ** ListC, int sizeLC ,int value){
    int i=0;
    for(;i < sizeLC;i++){
        if((*ListC)[i]==value){
            return 1;
        }
    }
    return 0;
}