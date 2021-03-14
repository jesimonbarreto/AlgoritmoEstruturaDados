#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matriz.h"



	void printAll(int ** matriz, int nline, int ncol){
		int i=0,j=0;
		printf("\n");
		for(;i<nline;i++){
			for(j=0;j<ncol;j++){
				printf("%c ",matriz[i][j]);
			}
			printf("\n");
		}
	}
	
	int wordExistGrid(char * word, int ** grid, int lm, int lc){
		int i = 0,j=0;
		Point * poin=(Point*) malloc(sizeof(Point)*(lm*lc));
		for(;i<lm;i++){
			for(;j<lc;j++){
				if(wordExist(word, grid, lm, i, j, 0,0,&poin)){
					return 1;
				}
			}
		}
		free(poin);
		return 0;
	}
	
	int wordExist(char * word, int ** grid, int m, int i, int j, int p, int ind, Point ** vis){
		int c=0;
		for(;c<ind;c++){
			if((*vis)[c].x==i && (*vis)[c].y==j){
				return 0;
			}
		}
		
		if(word[p+1]=='\n' && word[p]==grid[i][j]){
			return 1;
		}	
		//adiciona i e j como ponto no vetor
		(*vis)[ind].x=i;
		(*vis)[ind].y=j;
		ind++;
		if(word[p]==grid[i][j]){
			if(i==0 && j==0){
				if(wordExist(word,grid, m, i+1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i, j+1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j+1, p + 1,ind,vis)) return 1;
			}else if(i==m-1 && j==0){
				if(wordExist(word,grid, m, i-1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i, j+1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i-1, j+1, p + 1,ind,vis)) return 1;
			}else if(i==0 && j==m-1){
				if(wordExist(word,grid, m, i, j-1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j-1, p + 1,ind,vis)) return 1;
			}else if(i==m-1 && j==m-1){
				if(wordExist(word,grid, m, i-1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i, j-1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i-1, j-1, p + 1,ind,vis)) return 1;
			}else if(j==0){
				if(wordExist(word,grid, m, i-1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i-1, j+1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i, j+1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j+1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j, p + 1,ind,vis)) return 1;
			}else if(i==0){
				if(wordExist(word,grid, m, i, j-1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i, j+1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j-1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j+1, p + 1,ind,vis)) return 1;
			}else if(i==m-1){
				if(wordExist(word,grid, m, i, j-1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i, j+1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i-1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i-1, j+1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i-1, j-1, p + 1,ind,vis)) return 1;
			}else if(j==m-1){
				if(wordExist(word,grid, m, i-1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i, j-1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i-1, j-1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j-1, p + 1,ind,vis)) return 1;
			}else{
				if(wordExist(word,grid, m, i, j-1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i-1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i, j+1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i-1, j-1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j+1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i+1, j-1, p + 1,ind,vis)) return 1;
				if(wordExist(word,grid, m, i-1, j+1, p + 1,ind,vis)) return 1;
			}
		}
			return 0;
		
	}
	
	
	void printVector(int ** vector, int size){
		int i=0;
		for(;i<size;i++){
				printf("%d ",(*vector)[i]);
		}
		printf("\n");
	}
	
	void printLine(int ** matriz, int line,int ncol){
		
		int i=0;
		for(;i<ncol;i++){
				printf("%d ",matriz[line][i]);
		}
		printf("\n");
	}
	void printRow(int ** matriz, int col, int nline){
		int i=0;
		for(;i<nline;i++){
				printf("%d ",matriz[i][col]);
				printf("\n");
		}
	}
	
	void convertMinforMai(char * word,int size){
		int i=0;
		for(;i<size;i++){
			char l=word[i];
			if(l == 'a'){ word[i]='A';
			}else if(l == 'b'){ word[i]='B'; 
			}else if(l == 'c'){ word[i]='C';
			}else if(l == 'd'){ word[i]='D';
			}else if(l == 'e'){ word[i]='E';
			}else if(l == 'f'){ word[i]='F';
			}else if(l == 'g'){ word[i]='G';
			}else if(l == 'h'){ word[i]='H';
			}else if(l == 'i'){ word[i]='I';
			}else if(l == 'j'){ word[i]='J';
			}else if(l == 'k'){ word[i]='K';
			}else if(l == 'l'){ word[i]='L';
			}else if(l == 'm'){ word[i]='M';
			}else if(l == 'n'){ word[i]='N';
			}else if(l == 'o'){ word[i]='O';
			}else if(l == 'p'){ word[i]='P';
			}else if(l == 'q'){ word[i]='Q';
			}else if(l == 'r'){ word[i]='R';
			}else if(l == 's'){ word[i]='S';
			}else if(l == 't'){ word[i]='T';
			}else if(l == 'u'){ word[i]='U';
			}else if(l == 'v'){ word[i]='V';
			}else if(l == 'w'){ word[i]='W';
			}else if(l == 'x'){ word[i]='X';
			}else if(l == 'y'){ word[i]='Y';
			}else if(l == 'z'){ word[i]='Z';
			}
		}
	}

