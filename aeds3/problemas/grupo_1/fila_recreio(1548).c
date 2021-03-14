#include <stdio.h>
#include <stdlib.h>

typedef struct student{
    int grades;
    int id;
    int ordem;
} student;


int main(){
    int N, M, i;

    scanf("%d", &N);
    for(i=0; i < N; i++){
        scanf("%d", &M);
        
        int j, contContinuam=0;
        student * students = (student*) calloc(M, sizeof(student));
        for(j=0; j < M; j++){
            students[j].id = j;
            students[j].ordem = j;
            scanf("%d", &students[j].grades);
            int z = j;
            for(;z>0;z--){
                if(students[z].grades > students[z-1].grades){
                    int c = students[z].ordem;
                    students[z].ordem = students[z-1].ordem;
                    students[z-1].ordem = c;
                    c = students[z].grades;
                    students[z].grades = students[z-1].grades;
                    students[z-1].grades = c;
                }
            }
            
        }

        for(j=0; j < M; j++){
            if(students[j].id==students[j].ordem){
                contContinuam++;
            }
        }
        free(students);
        printf("%d\n", contContinuam);   
    }

    return 0;
}