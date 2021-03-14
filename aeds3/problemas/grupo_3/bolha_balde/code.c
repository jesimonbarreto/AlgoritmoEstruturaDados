#include <stdio.h>
#include <stdlib.h>

int main() {
 
     unsigned int *list, n, v;
    
    scanf("%d",&n);
    while(n!=0){
        int i=0;
        list = (int*) malloc(n*sizeof(n));
        while(i<n) {
            scanf("%d",&list[i]);
            i++;
        }
        i = 0;
        int ind = 0;

        int j = 0, contP=0;
            while(i<n){
                int p2 = list[i]-1;
                
                if(list[i] == list[p2]){
                    i++;
                }else{
                    contP += i + p2 + i + p2 - 1;
                    list[i] = list[i] + list[p2];
                    list[p2] = list[i] - list[p2];
                    list[i] = list[i] - list[p2];
                }
            }
        if(contP%2==0){
            printf("Carlos\n");
        }else{
            printf("Marcelo\n");
        }
        free(list);
        scanf("%d",&n);
    }
    return 0;
}
