#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int N, L, C;
    while(scanf("%d %d %d", &N, &L, &C) != EOF){
        
        char * str = (char *) malloc(N * 70 * sizeof(char));    
        scanf(" %[^\n]s",str);
        

        int i = 0, j=0, contC = C,  nPage = 0, nLine=0;

        for(i=0; i < N; i++){
            int sizeWord = 0;
            
            while(str[j] == ' '){
                j++;
            }

            while(str[j] != ' ' && str[j] != '\0'){
                sizeWord++;
                j++;
            }

            int vWord = contC - sizeWord;

            if(vWord > 0){
                contC = vWord - 1;
                if(contC==0){
                    nLine++;
                    contC = C;
                }
                
            }else if(vWord == 0){
                nLine++;
                contC = C;
            }else{
                nLine++;
                contC = C - sizeWord - 1;
                if(contC<=0){
                    nLine++;
                    contC = C;
                }
            }
            
            if(nLine>=L){
                nLine = nLine - L;
                nPage++;
            }
        }
        if(contC<C){
            nLine++;
        }
        if(nLine > 0){
            nPage++;  
        } 
        
        printf("%d\n",nPage);


        free(str);
    }
    return 0;
}