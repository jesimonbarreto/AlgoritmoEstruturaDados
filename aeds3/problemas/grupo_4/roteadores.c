//http://www.codcad.com/lesson/44
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int pai[1000];
int peso[1000];

typedef struct t_aresta{
    int dis;
    int x, y;
} ares;

int comp(const void * a, const void * b){
	 ares *A = (ares *)a;
     ares *B = (ares *)b;
	return (A->dis - B->dis); 
}

int find(int x){
    if(pai[x] == x) return x;
    return pai[x] = find(pai[x]);
}

void join(int a, int b){
    a = find(a);
    b = find(b);
    
    if(peso[a] < peso[b]) pai[a] = b;
    else if(peso[b] < peso[a]) pai[b] = a;
    else{
        pai[a] = b;
        peso[b]++;
    }
    
}




int main(){
	int c,r, dj=0;
	ares a[1000], agm[1000];
	
	
	scanf("%d %d", &r, &c);
	
	int i=0,v1,v2, d;
	
	for(i=0; i<c;i++){
		scanf("%d %d %d", &v1, &v2, &d);
		a[i].dis=d;
		a[i].x=v1;
		a[i].y=v2;
	}
	
	for(i=0; i<=r;i++){ 
		pai[i] = i;
		peso[i]= 0;
	}
	

	qsort (a, c, sizeof(ares), comp);
		
	 int size = 0;
    for(i = 0;i <= c;i++){
        
        if( find(a[i].x) != find(a[i].y) ){ // se estiverem em componentes distintas
            join(a[i].x, a[i].y);
            
            agm[++size] = a[i];
        }
        
    }
	 for(i = 0;i < r;i++){
		 dj+=agm[i].dis;
	 }
	printf("%d\n", dj);
	return 0;
}