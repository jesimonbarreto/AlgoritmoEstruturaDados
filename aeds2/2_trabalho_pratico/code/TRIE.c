#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TRIE.h"
#include "matriz.h"
	
	
	//inicializa as palavras da trie de consulta
	void initialize(Node ** trie, char * nameF){
		//carregar arquivo de texto na arvore
		FILE * file=NULL;
		file=fopen(nameF,"r");
		char line[40];
		while (!feof(file)){
			strcpy(line, "" );
			fgets(line, sizeof(line), file);
			insertWord(line, trie);
		}
		fclose(file);
	}
	
	//criar nova argore TRIE e passa o endereço por trie
	void newTRIE(Node ** trie){
		(*trie) = (Node*) malloc(sizeof(Node));
		(*trie)->letter = '1'; // pois é o nó raiz
		(*trie)->finalWord = 0;
		(*trie)->letters = (Node**) malloc(sizeof(Node*)*26);
		cleanVector(trie,26);
	}
	//limpa o vetor (usado no vetor de letras em cada Node)
	void cleanVector(Node ** vec, int size){
		int i =0;
		for(;i<size;i++){
			(*vec)->letters[i] = NULL;
		}
	}
	//insere palavra word na arvore trie
	void insertWord(char * word, Node ** trie){
		if(!filterString(word)){
			insert(trie, word, 0);
		}else{
			printf("Erro palavra ou Palavra ja existe\n");
		}
	}
	//função recursiva que insere palavra
	void insert(Node ** n, char * word, int p){
		int nValue = convertLetterInt(word[p]);
		if((*n)->letters[nValue]==NULL){
			newNodePosition(n,nValue,word[p]);
		}
		if(word[p+1]=='\n'){
			(*n)->finalWord=1;
			return;
		}
		insert(&(*n)->letters[nValue], word, p+1);
	}
	
	int filterString(char * word){
		int v=0,i=0;
		for(;i<100;i++){
			if(word[i]!='\n'){
				char letter = word[i];
				if(letter == 'A' || letter == 'a'){ v= 0;
				}else if(letter == 'B' || letter == 'b'){ v= 0;
				}else if(letter == 'C' || letter == 'c'){ v= 0;
				}else if(letter == 'D' || letter == 'd'){ v= 0;
				}else if(letter == 'E' || letter == 'e'){ v= 0;
				}else if(letter == 'F' || letter == 'f'){ v= 0;
				}else if(letter == 'G' || letter == 'g'){ v= 0;
				}else if(letter == 'H' || letter == 'h'){ v= 0;
				}else if(letter == 'I' || letter == 'i'){ v= 0;
				}else if(letter == 'J' || letter == 'j'){ v= 0;
				}else if(letter == 'K' || letter == 'k'){ v= 0;
				}else if(letter == 'L' || letter == 'l'){ v= 0;
				}else if(letter == 'M' || letter == 'm'){ v= 0;
				}else if(letter == 'N' || letter == 'n'){ v= 0;
				}else if(letter == 'O' || letter == 'o'){ v= 0;
				}else if(letter == 'P' || letter == 'p'){ v= 0;
				}else if(letter == 'Q' || letter == 'q'){ v= 0;
				}else if(letter == 'R' || letter == 'r'){ v= 0;
				}else if(letter == 'S' || letter == 's'){ v= 0;
				}else if(letter == 'T' || letter == 't'){ v= 0;
				}else if(letter == 'U' || letter == 'u'){ v= 0;
				}else if(letter == 'V' || letter == 'v'){ v= 0;
				}else if(letter == 'W' || letter == 'w'){ v= 0;
				}else if(letter == 'X' || letter == 'x'){ v= 0;
				}else if(letter == 'Y' || letter == 'y'){ v= 0;
				}else if(letter == 'Z' || letter == 'z'){ v= 0;
				}else{ word[i]='\n';
				return 0;}
			}else{return 0;}
		}
		return v;
	}
	
	//Cria novo no e adiciona no vetor com a letra qual representa
    void newNodePosition(Node ** n, int p,char l){
		(*n)->letters[p] = (Node*) malloc(sizeof(Node));
		(*n)->letters[p]->letter = l;
		(*n)->letters[p]->finalWord = 0;
		(*n)->letters[p]->letters = (Node**) malloc(sizeof(Node*)*26);
		cleanVector(&(*n)->letters[p],26);
	}
	
	//converte letra em numero codificado de 0 a 26
	int convertLetterInt(char letter){
		int i;
		if(letter == 'A' || letter == 'a'){ i=0;
		}else if(letter == 'B' || letter == 'b'){ i=1; 
		}else if(letter == 'C' || letter == 'c'){ i=2;
		}else if(letter == 'D' || letter == 'd'){ i=3;
		}else if(letter == 'E' || letter == 'e'){ i=4;
		}else if(letter == 'F' || letter == 'f'){ i=5;
		}else if(letter == 'G' || letter == 'g'){ i=6;
		}else if(letter == 'H' || letter == 'h'){ i=7;
		}else if(letter == 'I' || letter == 'i'){ i=8;
		}else if(letter == 'J' || letter == 'j'){ i=9;
		}else if(letter == 'K' || letter == 'k'){ i=10;
		}else if(letter == 'L' || letter == 'l'){ i=11;
		}else if(letter == 'M' || letter == 'm'){ i=12;
		}else if(letter == 'N' || letter == 'n'){ i=13;
		}else if(letter == 'O' || letter == 'o'){ i=14;
		}else if(letter == 'P' || letter == 'p'){ i=15;
		}else if(letter == 'Q' || letter == 'q'){ i=16;
		}else if(letter == 'R' || letter == 'r'){ i=17;
		}else if(letter == 'S' || letter == 's'){ i=18;
		}else if(letter == 'T' || letter == 't'){ i=19;
		}else if(letter == 'U' || letter == 'u'){ i=20;
		}else if(letter == 'V' || letter == 'v'){ i=21;
		}else if(letter == 'W' || letter == 'w'){ i=22;
		}else if(letter == 'X' || letter == 'x'){ i=23;
		}else if(letter == 'Y' || letter == 'y'){ i=24;
		}else if(letter == 'Z' || letter == 'z'){ i=25;
		}
		return i;
	}
	
	//retorna tamanho da palavra
	int wordSize(char * word){
		int i =0;
		while(word[i]!='\n'){
			i++;
		}
		return i;
	}
	//se exite retorna 1 caso contrário retorna 0
	int searchWord(Node ** trie, char * word){
		if(search(trie, word, 0)){
			return 1;
		}
		return 0;
	}
	//função recursica para busca na arvore trie
	int search(Node ** n, char * word, int p){
		int nValue = convertLetterInt(word[p]);
		if((*n)->letters[nValue]==NULL || (word[p+1]=='\n' && (*n)->finalWord==0))
			return 0;
		if(word[p+1]=='\n' && (*n)->finalWord==1)
			return 1;
		
		return (search(&(*n)->letters[nValue], word, p+1));
	}
	
	
	void freeMemory(Node ** trie, int sizel){
		int i=0;
		for(;i<sizel;i++){
			if((*trie)->letters[i]!=NULL){
				freeMemory((*trie)->letters+i, sizel);
			}
		}
		free((*trie)->letters);
		free((*trie));
	}