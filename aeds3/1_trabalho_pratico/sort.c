// =----------------------------------------------------------=
// =                           AVISO:                         =
// =                   MODIFIQUE ESTE ARQUIVO!                =
// = Aqui, você deve implementar, obrigatoriamente, essas     =
// = duas funções:                                            =
// =     - `a_menor_que_b`: deve retornar quando uma string   =
// =        é menor que a outra (ambos com o mesmo tamanho);  =
// =     - `external_sort`: aqui, você deverá implementar o   =
// =        seu trabalho. Ordene os registros em `input_file` =
// =        e escreva-os em `output_file`, usando somente     =
// =        `memory` KB de memória.                           =
// =                                                          =
// = Instruções:                                              =
// =     - use a função `mathias_malloc` ao invés de          =
// =       `malloc`;                                          =
// =     - use a função `mathias_free` ao invés de `free`;    =
// =     - lembre-se que você tem somente `memory` KB de      =
// =       memória;                                           =
// =     - note que a sua implementação de `a_menor_que_b`    =
// =       afetará o resultado da verificação da resposta.    =
// =                                                          =
// = Dicas:                                                   =
// =     - você pode usar a sua função `a_menor_que_b` em     =
// =       sua implementação da função `external_sort`;       =
// =                                                          =
// =                      BOM TRABALHO!                       =
// =----------------------------------------------------------=

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mem.h"

// Parâmetros:
//     - a: uma cadeia de caracteres de tamanho `len`;
//     - b: uma cadeia de caracteres de tamanho `len`;
//     - len: o tamanho (quantidade de bytes) de `a` e `b`.
// Essa função deve retornar 1, se `a` é menor que `b` (`a` deve vir antes de `b` no
// arquivo), e 0 caso contrário.
// Ela também é usada para verificação da ordenação! Então, se você implementá-la
// erroneamente, a verificação também estará errada! 
int a_menor_que_b(char* a, char* b, int len) {
	int i = 0;
	while(i<len){
		if(a[i] < b[i]){
			return 1;
		}else if(a[i] > b[i]){
			return 0;
		}
		i++;
	}
	return 0;
}

// Parâmetros:
//     - input_file: o nome do arquivo com os registros de entrada;
//     - output_file: o nome do arquivo com os registros de entrada ordenados;
//     - memory: o limite de memória a ser usado.
// Essa função deverá ler todos registros do arquivo `input_file`, ordená-los e
// escrevê-los em `output_file`, usando memória menor ou igual a `memory`. Lembre-se
// de fechar todos os arquivos que você usar por aqui!!
void external_sort(const char* input_file, const char* output_file, unsigned int memory) {
	
	FILE * in, *out, *fita1, *fita2, *fita3, *fita4;
	int nCharL, pStrG = 0, capac, size = 0, exec = 0, indic = 1, nLines=0, fitaOrd = 1, sizeMarcador = 3, ordenado = 0;
	char *line, *strG, marcador[] = "J B";
	
	in = fopen(input_file,"r");
	
	fita1 = fopen("fita1.txt","w");	
	fita2 = fopen("fita2.txt","w");
	

	fscanf(in,"%d",&nCharL);
	capac = memory/nCharL;
	capac--;
	int sizeMax = capac * nCharL;

	line = (char*) mathias_malloc(nCharL+1);
	strG = (char*) mathias_malloc(sizeMax+1);

	//caso so tenha espaço para as duas linhas, aumenta tamanho do sizeMax
	if(sizeMax == nCharL){
		sizeMax *= 2; 
	}	

	char * v = fgets(line, nCharL+1, in);
	v = fgets(line, nCharL+1, in);

	while(v != NULL){
//ler dados ate encher strG ou acabar arquivo ==============================================
		while(v != NULL && size < sizeMax - nCharL){
			int pLine = 0;
			while(pLine < nCharL){
				strG[pStrG] = line[pLine];
				pLine++;
				pStrG++;	
			}
			size+=nCharL;
			if(size<sizeMax) strG[pStrG] = '\0';
			nLines++;
			v = fgets(line, nCharL+1, in);
			v = fgets(line, nCharL+1, in);
		}
//Ordena o que esta em memoria principal====================================================

		int i, j, n = size/nCharL;
    		for (i=0; i<n; i++){
    			for (j=0; j<n-1; j++){
            			if (!a_menor_que_b(strG+(j*nCharL), strG+((j+1)*nCharL),nCharL)){
            				int pLine = 0;
					char aux;
					while(pLine < nCharL){
						aux = strG[(j*nCharL) + pLine];
						strG[(j*nCharL) + pLine] = strG[(j+1)*nCharL + pLine];
						strG[(j+1)*nCharL + pLine] = aux;
						pLine++;	
					}
				}
    			}	
    		}
//salva em memoria secundaria o que estava em memoria principal==============================
//Salvando como arquivo final caso o dado caiba todo na memoria principal--------------------
		if(v==NULL && !exec){
			out = fopen(output_file,"w");
			fprintf(out, "%d\n", nCharL);
			int pL = 0;
			while(pL < size){
				if(pL%nCharL == 0 && pL != 0)fprintf(out, "\n");
				fprintf(out, "%c", strG[pL]);
				pL++;
			}
			fprintf(out, "\n");
			fclose(out);
			ordenado = 1;
			break;
//caso contrario o dado eh salvo para ser ordenado pelo metodo===============================
		}else{	
			
			if(indic == 2 ){
				fprintf(fita2, "%s", strG);
				fprintf(fita2, "%s\n", marcador);
				indic = 1;
			}else{
				fprintf(fita1, "%s", strG);	
				fprintf(fita1, "%s\n", marcador);
				indic = 2;		
			}
			//dados em strG e esta cheio ou com todos os dados
			//ordenar em memoria principal e guardar
			pStrG=0;
			size=0;
		}
		exec++;

	}

//Ordenacao externa Intercalacao balanceada de varios caminhos============================
// So executa se o arquivo nao caiba todo na memoria principal
	
	fclose(fita1);
	fclose(fita2);
	

	fita1 = fopen("fita1.txt","r");	
	fita2 = fopen("fita2.txt","r");
	fita3 = fopen("fita3.txt","w");
	fita4 = fopen("fita4.txt","w");
	indic = 3;

	if(!ordenado){

		char *retf1 = fgets(line, nCharL +1, fita1);
		char *retf2 = fgets(strG, nCharL +1, fita2);
	line[nCharL +1] = '\0';
	strG[nCharL +1] = '\0';
//Enquanto o segundo arquivo ainda tiver com dados a execuçao continua
		while(retf2 != NULL && strncmp(strG, marcador, sizeMarcador) != 0){

//Enquanto um dos arquivos tiver dados entao continua a intercalaçao, passando dos arquivo fita1 e fita2 para o fita3 e fita 4		
			while(retf1 != NULL && retf2 != NULL){
				//verifica se um dos ponteiros chegou no marcador, ou seja, chegou ao final da linha
				//se chegou copia todo o outro na continuaçao da linha pois ja esta ordenado
				if(strncmp(line, marcador, sizeMarcador) == 0 && strncmp(strG, marcador, sizeMarcador) != 0){
					if(indic == 3){ 
						while(strncmp(strG, marcador, sizeMarcador) != 0 && retf2 != NULL){
							fprintf(fita3, "%s", strG);
							retf2 = fgets(strG, nCharL +1, fita2);			
						}

						fprintf(fita3, "%s\n", marcador);
						retf1 = fgets(line, nCharL +1, fita1);
			 			retf2 = fgets(strG, nCharL +1, fita2);

						indic = 4;
					}else{
						while(strncmp(strG, marcador, sizeMarcador) != 0 && retf2 != NULL){
							fprintf(fita4, "%s", strG);
							retf2 = fgets(strG, nCharL +1, fita2);			
						}

						fprintf(fita4, "%s\n", marcador);
						retf1 = fgets(line, nCharL +1, fita1);
			 			retf2 = fgets(strG, nCharL +1, fita2);
						indic = 3;
					}

				}else if(strncmp(line, marcador, sizeMarcador) != 0 && strncmp(strG, marcador, sizeMarcador) == 0){
					if(indic == 3){ 
						while(strncmp(line, marcador, sizeMarcador) != 0 && retf1 != NULL){
							fprintf(fita3, "%s", line);
							retf1 = fgets(line, nCharL +1, fita1);		
						}
						retf1 = fgets(line, nCharL +1, fita1);
				 		retf2 = fgets(strG, nCharL +1, fita2);
						fprintf(fita3, "%s\n", marcador);
						indic = 4;
					}else{ 
						while(strncmp(line, marcador, sizeMarcador) != 0 && retf1 != NULL){
							fprintf(fita4, "%s", line);
							retf1 = fgets(line, nCharL +1, fita1);		
						}
						retf1 = fgets(line, nCharL +1, fita1);
				 		retf2 = fgets(strG, nCharL +1, fita2);
						fprintf(fita4, "%s\n", marcador);
						indic =3;
					}

				}else if(strncmp(line,marcador, sizeMarcador) == 0 && strncmp(strG,marcador, sizeMarcador) == 0){
					if(indic == 3){			
						fprintf(fita3, "%s\n", marcador);
						indic = 4;
					}else{ 
						fprintf(fita4, "%s\n", marcador);				
						indic =3;
					}
					retf1 = fgets(line, nCharL +1, fita1);
				 	retf2 = fgets(strG, nCharL +1, fita2);
				}

//Se chegou no final do arquivo copia o que tem no outro na continuaçao pois esta ordenado
				if(retf2 == NULL){
					if(indic == 3){ 
						while(strncmp(line, marcador, sizeMarcador) != 0 && retf1 != NULL){
							fprintf(fita3, "%s", line);
							retf1 = fgets(line, nCharL +1, fita1);		
						}
						fprintf(fita3, "%s\n", marcador);
						indic = 4;
					}else{ 
						while(strncmp(line, marcador, sizeMarcador) != 0 && retf1 != NULL){
							fprintf(fita4, "%s", line);
							retf1 = fgets(line, nCharL +1, fita1);		
						}
						fprintf(fita4, "%s\n", marcador);
						indic = 3;
					}

					break;

				} else if(retf1 == NULL){
					if(indic == 3){ 
						while(strncmp(strG, marcador, sizeMarcador) != 0 && retf2 != NULL){
							fprintf(fita3, "%s", strG);
							retf2 = fgets(strG, nCharL +1, fita2);			
						}

						fprintf(fita3, "%s\n", marcador);
						indic = 4;
					}else{
						while(strncmp(strG, marcador, sizeMarcador) != 0 && retf2 != NULL){
							fprintf(fita4, "%s", strG);
							retf2 = fgets(strG, nCharL +1, fita2);			
						}

						fprintf(fita4, "%s\n", marcador);
						indic = 3;
					}

					break;

				}
			
//Verifica entre as duas linhas qual eh menor, escreve e le o proximo da mesma fita

				if(a_menor_que_b(line, strG, nCharL)){
					if(indic == 3)	fprintf(fita3, "%s", line);
					else fprintf(fita4, "%s", line);

					retf1 = fgets(line, nCharL+1, fita1);
				}else{
					if(indic == 3)	fprintf(fita3, "%s", strG);
					else 	fprintf(fita4, "%s", strG);

					retf2 = fgets(strG, nCharL+1, fita2);
				}	
		
			}


			fclose(fita1);
			fclose(fita2);
			fclose(fita3);
			fclose(fita4);

			fita1 = fopen("fita1.txt","w");	
			fita2 = fopen("fita2.txt","w");
			fita3 = fopen("fita3.txt","r");
			fita4 = fopen("fita4.txt","r");

			retf1 = fgets(line, nCharL +1, fita3);
			retf2 = fgets(strG, nCharL +1, fita4);
			line[nCharL +1] = '\0';
			strG[nCharL +1] = '\0';
//Se o arquivo 4 nao tem mais dados entao acabou a intercalaçao	
			if(retf2 == NULL || strncmp(strG, marcador, sizeMarcador) == 0){

				fitaOrd = 3;
				break;
			}
	
//Enquanto um dos arquivos tiver dados entao continua a intercalaçao, passando dos arquivo fita3 e fita4 para o fita1 e fita 2
			indic = 1;
			while(retf1 != NULL && retf2 != NULL){
				if(strncmp(line, marcador, sizeMarcador) == 0 && strncmp(strG, marcador, sizeMarcador) != 0){
					if(indic == 1){ 
						while(strncmp(strG, marcador, sizeMarcador) != 0 && retf2 != NULL){
							fprintf(fita1, "%s", strG);
							retf2 = fgets(strG, nCharL +1, fita4);			
						}

						fprintf(fita1, "%s\n", marcador);
						retf1 = fgets(line, nCharL +1, fita3);
			 			retf2 = fgets(strG, nCharL +1, fita4);
						indic = 2;
					}else{
						while(strncmp(strG, marcador, sizeMarcador) != 0 && retf2 != NULL){
							fprintf(fita2, "%s", strG);
							retf2 = fgets(strG, nCharL +1, fita4);			
						}

						fprintf(fita2, "%s\n", marcador);
						retf1 = fgets(line, nCharL +1, fita3);
			 			retf2 = fgets(strG, nCharL +1, fita4);
						indic = 1;
					}

				}else if(strncmp(line, marcador, sizeMarcador) != 0 && strncmp(strG, marcador, sizeMarcador) == 0){
					if(indic == 1){ 
						while(strncmp(line, marcador, sizeMarcador) != 0 && retf1 != NULL){
							fprintf(fita1, "%s", line);
							retf1 = fgets(line, nCharL +1, fita3);		
						}
						retf1 = fgets(line, nCharL +1, fita3);
				 		retf2 = fgets(strG, nCharL +1, fita4);
						fprintf(fita1, "%s\n", marcador);
						indic = 2;
					}else{ 
						while(strncmp(line, marcador, sizeMarcador) != 0 && retf1 != NULL){
							fprintf(fita2, "%s", line);
							retf1 = fgets(line, nCharL +1, fita3);		
						}
						retf1 = fgets(line, nCharL +1, fita3);
				 		retf2 = fgets(strG, nCharL +1, fita4);
						fprintf(fita2, "%s\n", marcador);
						indic = 1;
					}

				}else if(strncmp(line,marcador, sizeMarcador) == 0 && strncmp(strG,marcador, sizeMarcador) == 0){
					if(indic == 1){			
						fprintf(fita1, "%s\n", marcador);
						indic = 2;
					}else{ 
						fprintf(fita2, "%s\n", marcador);				
						indic = 1;
					}
					retf1 = fgets(line, nCharL +1, fita3);
				 	retf2 = fgets(strG, nCharL +1, fita4);
				}


				if(retf2 == NULL){
					if(indic == 1){ 
						while(strncmp(line, marcador, sizeMarcador) != 0 && retf1 != NULL){
							fprintf(fita1, "%s", line);
							retf1 = fgets(line, nCharL +1, fita3);		
						}
						fprintf(fita1, "%s\n", marcador);
						indic = 2;
					}else{ 
						while(strncmp(line, marcador, sizeMarcador) != 0 && retf1 != NULL){
							fprintf(fita2, "%s", line);
							retf1 = fgets(line, nCharL +1, fita3);		
						}
						fprintf(fita2, "%s\n", marcador);
						indic = 1;
					}

					break;

				} else if(retf1 == NULL){
					if(indic == 1){ 
						while(strncmp(strG, marcador, sizeMarcador) != 0 && retf2 != NULL){
							fprintf(fita1, "%s", strG);
							retf2 = fgets(strG, nCharL +1, fita4);			
						}

						fprintf(fita1, "%s\n", marcador);
						indic = 2;
					}else{
						while(strncmp(strG, marcador, sizeMarcador) != 0 && retf2 != NULL){
							fprintf(fita2, "%s", strG);
							retf2 = fgets(strG, nCharL +1, fita4);			
						}

						fprintf(fita2, "%s\n", marcador);
						indic = 1;
					}

					break;

				}
			


				if(a_menor_que_b(line, strG, nCharL)){
					if(indic == 1)	fprintf(fita1, "%s", line);
					else fprintf(fita2, "%s", line);

					retf1 = fgets(line, nCharL+1, fita3);
				}else{
					if(indic == 1)	fprintf(fita1, "%s", strG);
					else 	fprintf(fita2, "%s", strG);

					retf2 = fgets(strG, nCharL+1, fita4);
				}	

			}
			fclose(fita1);
			fclose(fita2);
			fclose(fita3);
			fclose(fita4);

			fita1 = fopen("fita1.txt","r");	
			fita2 = fopen("fita2.txt","r");
			fita3 = fopen("fita3.txt","w");
			fita4 = fopen("fita4.txt","w");
			indic = 3;

			retf1 = fgets(line, nCharL +1, fita1);
			retf2 = fgets(strG, nCharL +1, fita2);
					line[nCharL +1] = '\0';
						strG[nCharL +1] = '\0';
//Se o arquivo 2 estiver nulo ou so com marcador eh porque a intercalaçao acabou e esta no arquivo 1
		
		}
		out = fopen(output_file,"w");
		fprintf(out, "%d\n", nCharL);
	//print no arquivo de saida final=======================================================================================
		int cont = 0;
		while(strncmp(line,marcador, sizeMarcador) != 0 && cont < nLines){
			fprintf(out, "%s\n", line);

			if(fitaOrd == 1) fgets(line, nCharL +1, fita1);
			else fgets(line, nCharL +1, fita3);
		
			cont++;
		}
		fclose(out);
	}
//finaliza===================================================================================
	
	fclose(in);
	fclose(fita1);
	fclose(fita2);
	fclose(fita3);
	fclose(fita4);
	remove("fita1.txt");
	remove("fita2.txt");
	remove("fita3.txt");
	remove("fita4.txt");
	mathias_free(strG);
	mathias_free(line);
}






