#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct re{ 
   int a; 
   int b;
} re;




int main(){
	int c,v, g[11000][11000], d[11000];
	
	scanf("%d %d", &c, &v);
	
	int i=0, j=0, v1,v2, d;
	
	for(; i<c;i++){
		for(; j<c;j++){
			g[j][i] = -1;
			g[i][j] = -1;
		}
		d[i] = -1;
	}
	d[0] = 0;
	for(i=0; i<v;i++){
		scanf("%d %d %d", &v1, &v2, &d);
		g[v1-1][v2-1] = d;
		g[v2-1][v1-1] = d;
	}
	
	for(i=0; i<c;i++){
		for(j=1; j<c;j++){
			int vq=g[i][j];
			if(vq!=-1 && (d[j] == -1 || d[j] > vq)){
				d[j] = vq;
			}
		}
	}
	
	printf("%d\n", dj);
	return 0;
}