#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "matriz.h"

	
	typedef struct node{
		 char letter; //letra ao qual o nó se refere
		 int finalWord; //0 ou 1 para indicar se é ultima letra da palavra
		 struct node ** letters;
	} Node;
	
	//inicializa as palavras da trie de consulta
	void initialize(Node ** trie, char * nameF);
	//criar nova argore TRIE e passa o endereço por trie
	void newTRIE(Node ** trie);
	//limpa o vetor (usado no vetor de letras em cada Node)
	void cleanVector(Node ** vec, int size);
	//insere palavra word na arvore trie
	void insertWord(char * word, Node ** trie);
	int filterString(char * word);
	//função recursiva que insere palavra
	void insert(Node ** n, char * word, int p);	
	//Cria novo no e adiciona no vetor com a letra qual representa
    void newNodePosition(Node ** n, int p,char l);
	//converte letra em numero codificado de 0 a 26
	int convertLetterInt(char letter);
	//retorna tamanho da palavra
	int wordSize(char * word);
	//se exite retorna 1 caso contrário retorna 0
	int searchWord(Node ** trie, char * word);
	//função recursica para busca na arvore trie
	int search(Node ** Node, char * word, int p);
	//libera memoria da trie
	void freeMemory(Node ** trie, int sizel);


#endif