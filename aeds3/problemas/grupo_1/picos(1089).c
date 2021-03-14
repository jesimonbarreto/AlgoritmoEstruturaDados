#include <stdio.h>
#include <stdlib.h>


int main(){
    int N, i, contPic = 0;
    int * data;

    scanf("%d", &N);
    while(N!=0){
        data = (int*) calloc(N, sizeof(int));

        for(i=0; i < N; i++){
            scanf("%d", &data[i]);
        }

        contPic = 0;
        for(i=0; i < N; i++){
            int ant, prox, p = data[i];
        
            if(i != 0 && i != N-1){
                ant = data[i-1];
                prox = data[i+1];
            }else if(i==0){
                ant = data[N-1];
                prox = data[i+1];
            }else{
                ant = data[i-1];
                prox = data[0];
            }
        
            if(ant<p && prox<p){
                contPic++;
            }else if(ant>p && prox>p){
                contPic++;
            }
            
        }
        free(data);

        printf("%d\n", contPic);
        scanf("%d", &N);
    }

    return 0;
}

