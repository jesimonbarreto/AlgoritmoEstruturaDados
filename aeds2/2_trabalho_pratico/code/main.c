#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TRIE.h"
#include "matriz.h"

/*
	Só funciona com letras de A a Z, os dados. as primeiras palavras do arquivo que continham numeros e menos de 3 letras foram apagados
	Não diferencia letra maiuscula de minuscula
*/
int main(int argc, char * argv[]){
	Node * trie=NULL;
	Node * trieRepet=NULL;
	//tamanho do grid X e Y
	int sgridx=5,sgridy=5;
	if(argc>0){
	   int r=atoi(argv[1]);
	   if(r>1){
			sgridx=r;
			sgridy=sgridx;
	   }
	}
	
	char  word[20];
	int ** grid, i=0,j=0;
	
	grid = (int**) malloc(sizeof(int*)*sgridx);
	for(i=0;i<sgridx;i++){
		grid[i]= (int*) malloc(sizeof(int)*sgridy);
		for(j=0;j<sgridy;j++){
			srand((unsigned) time(NULL)+j+rand());
			grid[i][j]= 'A' + ( rand() % ('Z'-'A') );
		}	
	}
	//Criar arvores trie de palavras e trie para verificar se a palavra ja foi digitada
	newTRIE(&trie);
	newTRIE(&trieRepet);
	//carrega valores dos arquivos para a arvore trie
	initialize(&trie,"listOfEnglishWords.txt");
	
	strcpy(word, "" );
	
	while(word[0]!='-'){
		printAll(grid, sgridx,sgridy);
		printf("\nUse a tecla '=' e aperte enter para atualizar o grid\n");
		printf("\nUse a tecla '-' e aperte enter para finalizar a execucao\n");
		printf("\nDigite a palavra: ");
		strcpy(word, "" );
		scanf("%s",word);
		if(word[0]=='-') break;
		if(word[0]=='='){
			for(i=0;i<sgridx;i++){
				for(j=0;j<sgridy;j++){
					srand((unsigned) time(NULL)+j+rand());
					grid[i][j]= 'A' + ( rand() % ('Z'-'A') );
				}	
			}
		}
		filterString(word);
		int sizeWord = wordSize(word);
		if(sizeWord>2){
			convertMinforMai(word,sizeWord);
			if(!searchWord(&trieRepet, word)){
				if(wordExistGrid(word, grid, sgridx, sgridy)){
					printf("Maior que 2 letras, possui %d Letras\n", sizeWord);
					printf("Palavra a pesquisar:  %s\n",word);
					printf("\nPesquisando...\n");
					if(searchWord(&trie, word)){
						printf("\nPalavra Encontrada: %s\n", word);
						printf("\nContinue Assim!\n");
						insertWord(word, &trieRepet);
					}else{
						printf("Palavra nao existe na lingua inglesa\n");
					}
				}else{
					printf("Palavra invalida na matriz, digite uma valida: %s\n",word);
				}
			}else{
				printf("\nPalavra repetida: %s\n",word);
			}
		}else{
			printf("Palavra Precisa conter mais de 3 letras\n");
		}
	}

	for(i=0;i<sgridx;i++){
		free(grid[i]);
	}
	free(grid);
	
	freeMemory(&trie,26);
	freeMemory(&trieRepet,26);

	return 0;
}