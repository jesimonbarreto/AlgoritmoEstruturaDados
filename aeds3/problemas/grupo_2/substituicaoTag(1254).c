#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char p[11];
    char t[51];
    char r[51];
    int findP=0;
    char sub[5];

    while(fgets(p, 11, stdin) != NULL){
        fgets(sub, 5, stdin);
        fgets(t, 51, stdin);


        int sizeP =  strlen(p) - 1;
        int sizeT =  strlen(t) - 1;
        int sizeS = strlen(sub) - 1;
        int i=0, pR=0;

        
        for(i=0;i < sizeT; i++){
            if(findP){
                if(t[i] == '>'){
                    findP = 0;
                    r[pR] = t[i];
                    pR++;
                    continue;
                }
                int j = i, pp=0;
                for(;pp < sizeP; pp++){
                    int v =0;
                    if(p[pp] >= 'a' && p[pp] <= 'z'){
                        if(t[j] != p[pp] && t[j] != p[pp]-32){
                            v++;
                        }
                    }else if(p[pp] >= 'A' && p[pp] <= 'Z'){
                        if(t[j] != p[pp] && t[j] != p[pp]+32){
                            v++;
                        }
                    }else{
                        v++;
                    }
                    if(v){
                        break;
                    }
                    j++;
                }
                
                if(pp==sizeP){
                    int k=i;
                    int ap=0;
                    for(;ap<sizeS;ap++){
                        r[pR] = sub[ap];
                        pR++; 
                    }
                    i+=sizeP-1;
                }else{
                    r[pR] = t[i];
                    pR++;
                }
                
            }else{
                if(t[i] == '<' && t[i+1] != '>'){
                    findP=1;
                } 
                r[pR] = t[i];
                pR++;
            }
                        

        }
        r[pR] = '\0';
        printf("%s\n", r);

    }
    return 0;
}