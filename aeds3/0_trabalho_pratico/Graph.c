#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Graph.h"
#include "Queue.h"

void createGraph(Vertice ** vertices, int size){
     (*vertices) = (Vertice*) calloc(size, sizeof(Vertice));
}

int binarySearch(Vertice ** vertices, int sizeV, int value){
    int inf = 0;
    int sup = sizeV - 1;
    int meio;

   while(inf <= sup){
        meio = ((inf+sup)/2);
        if((*vertices)[meio].id == value){
            return meio;
        }
       if((*vertices)[meio].id > value){
          sup = meio-1;
       }else{
           inf = meio+1;
       }
   }
   return -1;
}



int verifyDuplicate(Vertice ** vertices, int sizeV, int id1, int id2){
    //verifica qual tem menos conexoes para procurar se a associação proposta ja foi feita
    int p, s;
    //sao dados ids é necessario buscar a posição no vetor
    p = binarySearch(vertices, sizeV, id1);
    s = binarySearch(vertices, sizeV, id2);

    if(p == -1 || s == -1){
        return 0;
    }

    if( (*vertices)[p].nEdges > (*vertices)[s].nEdges){
        int x = p;
        p = s;
        s = x;
    }
    //Procurando associação
   
    int i =0;
    for(; i < (*vertices)[p].nEdges; i++){
        if( (*vertices)[p].edges[i] == s){
            return 0;
        }
    }

    return 1;
}

int insertEdge(Vertice ** vertices, int sizeV, int id1, int id2){
     
      int position1 = binarySearch(vertices, sizeV, id1);
      int position2 = binarySearch(vertices, sizeV, id2);

      if(position1==-1 || position2==-1){
          return -1;
      }
      
      insertEdgeSelec(vertices, position1, position2);
      return 1;
}


void insertEdgeSelec(Vertice ** vertices, int position1, int position2){
    (*vertices)[position1].nEdges+=1;
    int size = (*vertices)[position1].nEdges;

    (*vertices)[position1].edges = (int*) realloc((*vertices)[position1].edges, size * sizeof(int));
    (*vertices)[position1].edges[size-1] = position2;

    (*vertices)[position2].nEdges+=1;
    size = (*vertices)[position2].nEdges;
    (*vertices)[position2].edges = (int*) realloc((*vertices)[position2].edges, size * sizeof(int));
    //recebe a posição de do elemento na lista depois de ordenado
    (*vertices)[position2].edges[size-1] = position1;
}




int search(Vertice ** vertices, int ** controlList, int * sizeLC){
    int liked = 0;
    //As visitas sao baseadas na posicao no vetor e nao no ID
    //criar lista com a posição inicial dada pela problema
   
    while((*sizeLC) != 0){
        
        liked += visit(vertices, controlList, sizeLC);
        
        removePosition(controlList, sizeLC);
    }


    return liked;
}




int visit(Vertice ** vertices, int ** controlL, int * sizeLs){
    int l = 0;
    if((*vertices)[(*controlL)[0]].age < 35){
        l++;
        int i=0;
        
        for(; i < (*vertices)[(*controlL)[0]].nEdges; i++){
            //adiciona se nao existe na lista e nao foi visitado adiciona o no a lista para visita
            if(!exist(controlL, (*sizeLs), (*vertices)[(*controlL)[0]].edges[i]) && 
                                        !(*vertices)[(*vertices)[(*controlL)[0]].edges[i]].visited){
                //add position ControlList();
                //sizeLS++
                
                addPosition(controlL, (*vertices)[(*controlL)[0]].edges[i], sizeLs, 1);
            }
        }
        (*vertices)[(*controlL)[0]].visited = 1;  
    }
   
    return l;
}


