#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Queue.h"
#include "Graph.h"



int main(int argc, char * argv[]){
    
    Vertice * vertices;
    int N,M, first = 0;

        
        

    scanf("%d",&N);
    scanf("%d",&M);
    
    createGraph(&vertices, N);
    int i;
    for(i=0; i<N; i++){
        int id, age;
        scanf("%d" "%d", &id, &age);
        vertices[i].id = id;
        vertices[i].visited = 0;
        vertices[i].age = age;
        vertices[i].nEdges = 0;
    }
    
    for(i=0; i<M; i++){
        int id1, id2;
        
        scanf("%d" "%d", &id1, &id2);

        //verifica se os numeros ja foram adicionados ou se sao iguais
        if(id1!=id2 && verifyDuplicate(&vertices, N, id1, id2)){
            insertEdge(&vertices, N, id1, id2);
        }
    }
    scanf("%d", &first);
    
    int * listControl = (int*) malloc(sizeof(int));
    int sizeLC = 1, liked;
    listControl[0] = binarySearch(&vertices, N, first);
    //Inicia busca
    liked = search(&vertices, &listControl, &sizeLC);
    
    printf("%d\n", liked);

    free(listControl);
    free(vertices);

    



    return 0;
}