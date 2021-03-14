#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char str[1000];
    int dStr[60];

    while(fgets(str, 10000, stdin) != NULL){

        int sizeW =  strlen(str) - 1;
        int i=0,  min = 0;
        for(; i < 60; i++){
            dStr[i] = 0;
        }
        for(i=0; i < sizeW; i++){
            if(str[i] > 'A' && str[i] < 'Z'){
                dStr[str[i] - 'A'] += 1;
            }else{
                dStr[str[i] - 'a'] += 1;
            }
        }

        for(i=0; i < 60; i++){
           if(dStr[i] % 2 != 0){
               min++;
           }
        }
        
        if(min > 1){
            min--;
        }else{
            min = 0;
        }
        

        printf("%d\n", min);

    }
    return 0;
}