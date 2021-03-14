#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void zeraVector(int * v, int size){
    int i;
    for(i=0; i<100; i++){
        v[i]=0;
    }
}

int main() {
 
    unsigned int n, m, v, i=0, vec[100];
    char emot[200][50], text[1000];

    scanf("%d",&n);
    scanf("%d",&m);

    while(n!=0 && m!=0){
	 fgets(emot[0], 50, stdin);
	
        for(i=0; i<n; i++){
           fgets(emot[i], 50, stdin);
            //calcular tamanho de cada emoticon
            int s = strlen(emot[i])-1;
            emot[i][s] = '\0';
        }
      
        for(i=0; i<m; i++){
            fgets(text, 1000, stdin);

            zeraVector(vec, n);
		   
            int s = strlen(text)-1;	
            text[s] = '\0';
            int j=0;
            while(text[j] != '\n' && text[j] != '\0'){
                int k;
                for(k=0; k<n; k++){
                    int siz = 0; 
                    siz = strlen(emot[k]);
                    if(text[j] == emot[k][vec[k]]){
                        vec[k] += 1;
                    }else{
                        if(text[j] == emot[k][0]){
                            vec[k] = 1;
                        }else{
                            vec[k] = 0;
                        }
                    }
                    if(vec[k] == siz){
                        text[j] = ' ';
                        v++;
                        zeraVector(vec, n);
                    }
                
                }
                j++;
            }
        }

        printf("%d\n", v);
	v = 0;
        scanf("%d",&n);
        scanf("%d",&m);

    }
    return 0;
}