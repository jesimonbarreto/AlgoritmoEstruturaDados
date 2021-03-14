#include <stdio.h>
#include <stdlib.h>

int main(){
    char str[51], result[51];

    while(fgets(str, 51, stdin) != NULL){
        int i = 0, ind = 0;

        while(str[i] != '\n' && str[i] != '\0'){
            char c = str[i];
            while(c == ' '){
                if(c=='\n' || c=='\0'){
                    break;
                }
                result[i]= ' ';
                i++;
                c = str[i];
            }

            if(ind == 0 && c >= 'a' && c <= 'z'){
                result[i] = c - 32;   
            }else if(ind == 1 && c >= 'A' && c <= 'Z'){   
                result[i] = c + 32;
            }else{
                result[i] = c;
            }

            ind = !ind;

            i++;   
        } 
        result[i] = '\0';

        printf("%s\n", result);

    }
    return 0;
}