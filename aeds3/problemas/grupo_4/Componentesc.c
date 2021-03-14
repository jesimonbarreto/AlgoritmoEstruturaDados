#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




void atualiza(int p, int q, int pai[1000], int nv){
	if(pai[p]<pai[q]){
		int v = pai[q], i=0;
		for(i=0; i<nv;i++){ 
			if(pai[i] == v) pai[i] = pai[p]; 
		}
	}else{
		int v = pai[p], i=0;
		for(i=0; i<nv;i++){ 
			if(pai[i] == v) pai[i] = pai[q]; 
		}
	}
}

int existe(int fp[1000], int nv, int v){
	int i=0;
	for(i=0; i<nv;i++){ 
		if(fp[i] == v) return 1; 
	}
	return 0;
}

int verif(int pai[1000], int nv,int fp[1000]){
	int m=0;
	int v = 29, i;
	for(i=0; i<nv;i++){ 
			if(pai[i]!= v){
				if(!existe(fp, m, pai[i])){
					fp[m] = pai[i];
					v = pai[i];
					m++;
				}
			}
	}
	return m;
}


int main(){
	int n, cont=0;
	int pai[1000], fp[1000];
	
	
	scanf("%d", &n);
	while(cont < n){
		printf("Case #%d:\n", cont+1);
		int v, a;
		scanf("%d %d", &v, &a);
		
		int i=0;
		char v1,v2;
		
		for(i=0; i<v;i++){ 
			pai[i] = i;
		}
		
		for(i=0; i<a;i++){
			v1 =getchar();
			v1 =getchar();
			v2 =getchar();
			v2 =getchar();
			int p=0,q=0;
			p = v1 - 'a';
			q = v2 - 'a';
			atualiza(p,q, pai, v);
		}
		int maior = verif(pai, v, fp);
		
		for(i=0; i<maior;i++){
			int j = 0;
			for(j=0; j < v;j++){ 
				if(pai[j] == fp[i]){
					char p = j + 'a';
					printf("%c,", p);
				}
			}
			printf("\n");
		}
		printf("%d connected components\n\n", maior);
		
		cont++;
	}
	
	return 0;
}