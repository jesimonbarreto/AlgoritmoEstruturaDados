#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file.h"


	//Abre arquivo, se tiver erro retorna -1 
	int openFile(FILE ** file, char * dir, char * mode){
		int erro=0;
		(*file)=fopen(dir,mode);
		if((*file)==NULL){
			erro=-1;
		}
		return erro;
	}
	//passar struct como parametro
	//pega os dados do arquivo, salva os valores em ordem em um vetor double e a data em uma matriz int

	int readData(FILE * file, Data ** dataF){
		int erro = 0,i=0;
		char line[100];
		//numero de dias a serem lidos no arquivo
		int size = 0;
		//pegar uma linha
		while (i<6){
			fgets(line, sizeof(line), file);
			if(i==3){
				int j=0;
				while(line[j]<'0' || line[j]>'9'){
					j++;
				}
				while(line[j]>='0' && line[j]<='9'){
					size*=10;
					size+=line[j]-'0';
					j++;
				}
			}
			i++;
		}
		(*dataF)->nCitys = size;
		
		(*dataF)->cdnt = (Coordinate*) malloc(sizeof(Coordinate)*size);

		//captura os dados do arquivo, dias e valores, no caso de dias converte para inteiro e salva no vetor 
		int j;
		for(j=0;j<size;j++){
			int cid = 0;
			float citX,citY;
			fscanf(file,"%d %f %f",&cid,&citX,&citY);	
			(*dataF)->cdnt[j].x = citX;
			(*dataF)->cdnt[j].y = citY;
		}
		//neste ponto tenho um vetor value com valores double e um vetor days inteiro com a data no formato inteiro aaaammdd
		
		return erro;
	}

void writeFile(int ** vector, int size,float time,int distanceT){
	FILE *out=NULL;
	openFile(&out,"saida.txt","w");
	
	fprintf(out,"Solucao: %d\n",distanceT);
	fprintf(out,"Tempo : %.4fs\n",time);
	fprintf(out,"Rota :");
	
	int i=0;
		fprintf(out,"\n");
		for(;i<size;i++){
				fprintf(out,"%d \n",(*vector)[i]);
		}
		fprintf(out,"\n");
	closeFile(out);
}

	//Fecha um arquivo
	void closeFile(FILE * file){
		fclose(file);
	}