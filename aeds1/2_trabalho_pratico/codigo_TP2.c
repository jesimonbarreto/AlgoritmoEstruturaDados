#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//definindo uma constante
#define PI 3.14159265

// Permitindo a sua declaração como um tipo bool
typedef  enum boolean  bool;

//Criando a variavel constante conforme o tamanho da string 
const int tamanhoString=40;

// Criando a enumeração para usar como verdadeiro ou falso, variavel boolean
enum boolean {
    true = 1, false = 0
}; 

//---------------------------- STRUCT EXPRESSAO--------------------------------------------------------------------------------------------------

//Criar struct para as expressoes onde codigo é chamado do caractere que acompanha a expressao para indicar o tipo, pode ser i (I) ou p (P)
typedef struct expressao{
	int primeiroValor;//Pode ser o valor real caso Retangular ou pode ser o conjugado se for na forma Polar
	int segundoValor;//Pode ser o valor imaginário caso seja Retangular ou pode ser  
	char codigo;//i ou p
	int posicaoFinalString;//Ponto onde acaba a expressao na string geral
} numeroC;
//------------------------------------------------------------------------------------------------------------------------------------
//Projetos dos métodos(funções) presentes no arquivo
bool abrirArquivo(FILE ** arquivo, char * diretorio, char * modo);
void fecharArquivo(FILE * arquivo);
void leitor(char * entradaArq, char * calculo);
void gravarArquivo(FILE * arquivo, char * calc, numeroC * result);
bool proximoCalculoEntrada(FILE * arquivo, char ** calculo);
void avisoErro(int vErro);
void retirarEspacos(char * entrada,bool * erro);
void verificarDualidadeSinal(char * entrada, bool * erro);
void multiIndicadorExpre(char * entrada, bool * erro);
void extrairInformacoesExpressao1(char * entrada,numeroC ** result,bool * erro);
void extrairInformacoesOperacao(char * entrada,int posicao,char * operacao,bool * erro);
void extrairInformacoesExpressao2(char * entrada,char operacao, int posicao, numeroC ** result,bool * erro);
void converterRetangParaPolar(numeroC ** result);
void converterPolarParaRetang(numeroC ** result);
void somaRetang(numeroC expressao1, numeroC expressao2, numeroC ** result);
void subRetang(numeroC expressao1, numeroC expressao2, numeroC ** result);
void multiPolar(numeroC expressao1, numeroC expressao2, numeroC ** result);
void potenciaPolar(numeroC expressao1, int potencia, numeroC ** result);
void divPolar(numeroC expressao1, numeroC expressao2, numeroC ** result);




//----------------------------------------Aviso de Erro ------------------------------------------------------------------------
//Fazer função contem registros de erroAvisos que recebe um valor e exibe o erroAviso para o usuário, na tabela indica qual erro aconteceu
void avisoErro(int vErro){
	//erroAviso 1, o usuário digita uma string sem o caracter '='
	if(vErro==1){
		printf("Erro Cod. 1: Nao foi digitado o caracter =, nao foi digitado nada, ou excedeu o Vetor\n");
	}
	//erroAviso quando tiver duplicidade de sinal
	else if(vErro==2){
		printf("Erro Cod. 2: Foi digitado um sinal de operacao em seguida do outro\n");	
	}
	//erroAviso quando tiver mais letras que o necessário ou letras diferentes
	else if(vErro==3){
		printf("Erro Cod. 3: Foi digitado letras a mais ou letras diferentes dos codigos para expressao\n");
	}
	//Caso passe tipos diferentes para soma
	else if(vErro==4){
		printf("Erro Cod. 4: Soma, Tipos diferentes de expressoes\n");
	}
	//Caso passe tipos diferentes para subtracao
	else if(vErro==5){
		printf("Erro Cod. 5: Subtracao, Tipos diferentes de expressoes\n");
	}
	//Caso passe tipos diferentes para Multiplicacao
	else if(vErro==6){
		printf("Erro Cod. 6: Multiplicacao, Tipos diferentes de expressoes\n");
	}
	//Caso passe tipos diferentes para Potencia
	else if(vErro==7){
		printf("Erro Cod. 7: Potencia, Tipos diferentes de expressoes\n");
	}
	//Caso passe tipos diferentes para Divisao
	else if(vErro==8){
		printf("Erro Cod. 8: Divisao, Tipos diferentes de expressoes\n");
	}
	//Caso seja digitado um valor sem o primeiro valor 
	else if(vErro==9){
		printf("Erro Cod. 9: Nao foi digitado no formato correto\n");
	}
	else if(vErro==10){
		printf("Erro Cod. 10: Nao foi possivel abrir o arquivo\n");
	}
	else if(vErro==11){
		printf("Erro Cod. 11: Nao foi possivel alocar memoria\n");
	}
	
}
//-----------------------------Leitura de Arquivo de entrada ------------------------------------------------------------------------------------
//Generico pois precisarei o arquivo de entrada e de resultado 
bool abrirArquivo(FILE ** arquivo, char * diretorio, char * modo){
	bool erro=false;
	*arquivo=fopen(diretorio,modo);
	if(*arquivo==NULL){
		avisoErro(10);
		erro=true;
	}
	return erro;
}

//verificar essa função
void fecharArquivo(FILE * arquivo){
	fclose(arquivo);
	arquivo=NULL;
}

void gravarArquivo(FILE * arquivo, char * calc, numeroC * result){
	int sttgrava=fprintf(arquivo,"%s = %d %d %c",(*result).primeiroValor,(*result).segundoValor,(*result).codigo);
	if(sttgrava<0){
		printf("\nErro na Gravacao\n");
	}
}

bool proximoCalculoEntrada(FILE * arquivo, char ** calculo){
	bool fimArquivo=false;
	*calculo = (char*) malloc(sizeof(char));
			if((*calculo)==NULL){
				printf("Erro de Alocacao de memoria para char calculo\n");
			}
		int i = 0;
		char ch=fgetc(arquivo);
		while(ch != EOF && ch != '='){
			//se ch for diferente de espaço armazena valor
			if(ch != ' '){
				(*calculo)[i]=ch;
				i++;
				(*calculo)=(char*) realloc((*calculo),(i+1)*sizeof(char));
				if((*calculo)==NULL){
					avisoErro(10);
				}
			}
			ch=fgetc(arquivo);
		}
		if(ch==EOF){
			fimArquivo=true;
		}
		
		//Adiciona a ultima para colocar o /0
		(*calculo)[i]='=';
		i++;
		(*calculo)=(char*) realloc((*calculo),(i+1)*sizeof(char));
		(*calculo)[i]='\0';
		
		return fimArquivo;
}

//-------------------------------------------------MÉTODO VERIFICAR DUALIDADE DE SINAL------------------------------------------------------------
//Verificar se tem dois sinais juntos
//retornar true ou 1 caso aconteça o erroAviso
void verificarDualidadeSinal(char * entrada, bool * erro){
	int i, numeroSinalSeguidos=0;
	bool dualidadeSinal=false;
	for(i=0;i<tamanhoString;i++){
		//Nao é um numero então pode ser um sinal ou indicador de tipo de equação
		//Verificador de Operaçao
			//Se for um sinal soma 1 em numeroSinalSeguidos se passar de 1 é porque está errado
			//Como agora o programa poderá ter dois sinais juntos de + ou de -
			if(entrada[i]=='-'){
				if(i>0){
					//reconhecendo se a operação entre as expressões 
						if((entrada[i-1]!='*' && entrada[i-1]!='/' && entrada[i-1]!='^' && entrada[i]!='-' && entrada[i]!='+')){
							numeroSinalSeguidos++;
						}	
				}else{
					if(entrada[i]!='-' && entrada[i]!='+'){
							numeroSinalSeguidos++;
					}
					
				}
			}else if(entrada[i]=='+'){
				if(i>0){
					//reconhecendo se a operação entre as expressões 
							if((entrada[i-1]=='*' && entrada[i-1]=='/' && entrada[i-1]=='^' && entrada[i]!='-' && entrada[i]!='+')){
								numeroSinalSeguidos++;
							}
				}else{
					if(entrada[i]!='-' && entrada[i]!='+'){
							numeroSinalSeguidos++;
					}
				}
			} else if(entrada[i]=='*'){
				numeroSinalSeguidos++;
			}else if(entrada[i]=='/'){
				numeroSinalSeguidos++;
			}else if(entrada[i]=='^'){
				numeroSinalSeguidos++;
			}else{
				numeroSinalSeguidos=0;
			}
		//Se tiver mais de um numero seguido então retorna erroAviso e finaliza o laço
		if(numeroSinalSeguidos>1){
			//erroAviso de duplicidade de sinal
			avisoErro(2);
			//Finaliza laço
			i=tamanhoString+1;
			//Variavel de erroAviso 
			dualidadeSinal=true;
		}
		
	}
	(*erro)=dualidadeSinal;
}
//-----------------------------------------------MÉTODO INDICAR VARIAS LETRAS--------------------------------------------------------------
//Caso o 'i' ou 'p' (indicadores de expressao) sejam mais que 2 
//Verifica quantidade de letras na string
void multiIndicadorExpre(char * entrada, bool * erro){
	int i=0,contIndicadoresI=0,contIndicadoresP=0,contLetras=0;
	bool multIndicador=false;
	
	while(entrada[i]!='='){
		//Verificar se a string tem mais de 2 letras, tanto maiusculas quanto minusculas ou tem caracteres estranhos
		if(entrada[i]>'A' && entrada[i]<'Z'){
			if(entrada[i]=='I'){
				contIndicadoresI++;
			}else if(entrada[i]=='P'){
				contIndicadoresP++;
			}else{
					contLetras++;
			}
		
		}else if(entrada[i]>'a' && entrada[i]<'z'){
				//Registrar quantidade de i ou de I
				if(entrada[i]=='i'){
					contIndicadoresI++;
				//Registrar quantidade de p ou P
				}else if(entrada[i]=='p'){
					contIndicadoresP++;
				}else{
					contLetras++;
				}
		}
		
		
		i++;
	}
	//Verifica quantidade de indicadores de p e i e confirma se a quantidade confere com a quantidade de expressões
	//em conjunto com a quantidade de letras diferentes de i,I,p,P.
	int indicadores=contIndicadoresI+contIndicadoresP;
	if(indicadores>2 || indicadores<1 || contLetras>0){
		multIndicador=true;
		//erroAviso3;
		avisoErro(3);	
	}
	//Retorna false caso a expressao esteja correta, e true caso tenha mais letras do que necessário ou letras diferentes do código
	(*erro)=multIndicador;
}

//------------------------------------METODOs EXTRAIR INFORMACOES-------------------------------------------------------------------------------------
//Da expressao 1
void extrairInformacoesExpressao1(char * entrada,numeroC ** result,bool * erro){
	int i,valor1Expre=0, valor2Expre=0,contMais=0,contMenos=0;
	//valor do indicador da expressao 1 
	char codigo;
	erro = false;
	//----------------------------------Primeiro Valor---Primeira Expressao----------------------------
	i=0;
	//Verifica se o primerio caracter é aceito e se é um + ou - é necessário para atribuir valor
	while(entrada[i]<'0'|| entrada[i]>'9'){
		if(entrada[i]=='+'){
			contMais++;
		}else if(entrada[i]=='-'){
			contMenos++;
		}
		i++;
	} 
	//Vai converte para inteiro todo o valor ate que apareça um sinal
	while(entrada[i]!='+' && entrada[i]!='-'){
		if(valor1Expre>0){
			valor1Expre*=10;
		}
		if(entrada[i]=='i' || entrada[i]=='I' || entrada[i]=='p' || entrada[i]=='P'){
			//entao não foi digitado no formato certo
			avisoErro(9);
			(*erro)=true;
		}
		valor1Expre+=entrada[i]-'0';
		i++;
	}
	
	//Se o primeiro caracter == '-' então é necessário multiplicar o primeiro valor da expressao 1 por -1;
	if(contMenos%2==1 && contMenos!=0){
		valor1Expre*=(-1);
	}
	//Se a o ponteiro da string parou em um sinal de soma ou subtraçao quer dizer que os dois valores da expressão foram postos 
	//por exemplo " 2'+'3i " caso contrário, se parar em um indicador de expressão 'i' ou 'p', o valor da primeira expressão não foi colocado e nesse caso entende-se como 0 
	//por exemplo " +3'i' "
	
		contMenos=0;
		contMais=0;
		while(entrada[i]<'0'|| entrada[i]>'9'){
			if(entrada[i]=='+'){
				contMais++;
			}else if(entrada[i]=='-'){
				contMenos++;
			}
			i++;
		} 
	
		//Pular o sinal, pois só será usado depois de adicionar o valor na variavel inteira
		while((entrada[i]!='i' && entrada[i]!='I') && (entrada[i]!='p' && entrada[i]!='P')){
			if(valor2Expre>0){
				valor2Expre*=10;
			}
			valor2Expre+=entrada[i]-'0';
			i++;
		}
		//Se o primeiro caracter == '-' então é necessário multiplicar o primeiro valor da expressao 1 por -1;
		if(contMenos%2==1 && contMenos!=0){
			valor2Expre*=(-1);
		}
	
		//--------------------------------------Valor indicador da primeira expressao------------------------
		codigo=entrada[i];
		
	//Fechando primeira expressão
	(*result)=(numeroC *) malloc(sizeof(numeroC));
	if((*result)==NULL){
		avisoErro(11);
		(*erro)=true;
	}
	(*result)->primeiroValor=valor1Expre;
	(*result)->segundoValor=valor2Expre;
	(*result)->codigo=codigo;
	(*result)->posicaoFinalString=i; //A posicao i nesta parte será a ultima posicao da expressao na string
}

//Entrada é a String, Posicao é o valor do ponto em que a expressao parou no outro metodo
void extrairInformacoesOperacao(char * entrada,int posicao,char * operacao,bool * erro){
	//Somo mais 1 pois o valor passado é o final da primeira operacao
	(*erro)=false;
	posicao++;
	(*operacao)=entrada[posicao];
	if((*operacao)!='+' && (*operacao)!='-' && (*operacao)!='*' && (*operacao)!='/' && (*operacao)!='^' && (*operacao)!='='){
		//Erro de nao foi digitado errado
		(*erro)= true;
	}
	int i = posicao,cont=0;
	i++;
	if((*operacao)=='/' || (*operacao)=='*'){
		while(entrada[i]!='='){
			if(entrada[i]=='i' || entrada[i]=='I' || entrada[i]=='p' || entrada[i]=='P'){
				cont++;
			}
			i++;
		}
		if(cont==0){
			(*erro)=true;
		}
	}
}

//Entrada são a String, Posicao é o valor do ponto em que a expressao parou no outro metodo e operacao é a operacao entre funcoes
void extrairInformacoesExpressao2(char * entrada,char operacao, int posicao, numeroC ** result,bool * erro){
	int valor1Expre=0, valor2Expre=0,posicaoSinal=0,contMais=0,contMenos=0;
	char codigo;
	posicao++;
	(*erro)=false;
	int i = posicao,contCodigo=0;
	//Procurar por um indicador de expressão "i ou p" caso nao exista a expressão 1 só tem um valor
	while(entrada[i]!='='){
		if(entrada[i]=='i' || entrada[i]=='p' || entrada[i]=='I' || entrada[i]=='P'){
			contCodigo++;
		}
		i++;
	}
	
	//Se for potencia é necessario apenas colocar pegar o numero ao qual quer elevar
	//Nesse caso o valor irá na primeira posicao do Struct e a segunda sera 0
	if(contCodigo==0){
		
		//Verifica se o primerio caracter é aceito e se é um + ou - é necessário para atribuir valor
		while(entrada[posicao]<'0'|| entrada[posicao]>'9'){
			if(entrada[posicao]=='+'){
				contMais++;
			}else if(entrada[posicao]=='-'){
				contMenos++;
			}
			posicao++;
		} 
	
		
		while(entrada[posicao]!='='){
			if(valor1Expre>0){
				valor1Expre*=10;
			}
			valor1Expre+=entrada[posicao]-'0';
			posicao++;
		}
		//Verificação de sinal da potencia
		if(contMenos%2==1 && contMenos!=0){
			valor1Expre*=(-1);
		}
		
	}else{
		contMais=0;
		contMenos=0;
		while(entrada[posicao]<'0'|| entrada[posicao]>'9'){	
			if(entrada[posicao]=='+'){
				contMais++;
			}else if(entrada[posicao]=='-'){
				contMenos++;
			}
			posicao++;
		} 
		
		//Vai converte para inteiro todo o valor ate que apareça um sinal ou um indicador 
		while(entrada[posicao]!='+' && entrada[posicao]!='-' && entrada[posicao]!='i' && entrada[posicao]!='I' && entrada[posicao]!='p' && entrada[posicao]!='P'){
			if(valor1Expre>0){
				valor1Expre*=10;
			}
			valor1Expre+=entrada[posicao]-'0';
			posicao++;
		}

		//Verificação de sinal da primeira posicao
		if((contMenos%2==1 || contMenos==1) && contMenos!=0){
			valor1Expre*=(-1);
		}
		//---------------------------------------segundo valor indicador segunda expressao----------------------------------------------
		contMais=0;
		contMenos=0;
			while(entrada[posicao]<'0'|| entrada[posicao]>'9'){	
				if(entrada[posicao]=='+'){
					contMais++;
				}else if(entrada[posicao]=='-'){
					contMenos++;
				}
				posicao++;
			} 
			//salvando posicao do sinal
		//	posicaoSinal=posicao;
			//Pular o sinal, pois só será usado depois de adicionar o valor na variavel inteira
			while(entrada[posicao]!='i' && entrada[posicao]!='I' && entrada[posicao]!='p' && entrada[posicao]!='P'){
				if(valor2Expre>0){
					valor2Expre*=10;
				}
				valor2Expre+=entrada[posicao]-'0';
				posicao++;
			}
		//Se o primeiro caracter == '-' então é necessário multiplicar o primeiro valor da expressao 1 por -1;
			if(contMenos%2==1 && contMenos!=0){
				valor2Expre*=(-1);
			}
			codigo=entrada[posicao];
	}
	(*result)=(numeroC *) malloc(sizeof(numeroC));
	if((*result)==NULL){
		avisoErro(11);
		(*erro)=true;
	}
	(*result)->primeiroValor=valor1Expre;
	(*result)->segundoValor=valor2Expre;
	(*result)->codigo=codigo;
	(*result)->posicaoFinalString=posicao;
}

//---------------------------------------------METODO PARA CONVERTER DE RETANGULO PARA POLAR--------------------------------------------
//retorna um struct expressão com o resultado a conversão
void converterRetangParaPolar(numeroC ** result){
	int real=(*result)->primeiroValor, imag=(*result)->segundoValor;
	char tipo=(*result)->codigo;
	
	//pela formula raiz quadrada de valor real ao quadrado + raiz quadrada do valor imaginario ao quadrado
	(*result)->primeiroValor=0;
	(*result)->segundoValor=0;
	(*result)->codigo='0';
	//pela formula raiz quadrada de valor real ao quadrado + raiz quadrada do valor imaginario ao quadrado
	if(tipo=='i'  || tipo=='I'){
		//valores double?
		//pela formula raiz quadrada de valor real ao quadrado + raiz quadrada do valor imaginario ao quadrado
		(*result)->primeiroValor= sqrt((real*real + imag*imag));
		//Divide por 180 converter para radianos
		float rad=(imag/(real*1.0));
		//multiplica por 180 para converter de novo para graus
		int graus=atan(rad)*180/M_PI;
		(*result)->segundoValor= graus;
		(*result)->codigo='p';
	}else if(tipo=='p'  || tipo=='P'){
		//Se for do tipo i retornará uma expressao comas mesmas caracteristicas
		(*result)->primeiroValor=real;
		(*result)->segundoValor=imag;
		(*result)->codigo='p';
	}
}

//---------------------------------------------METODO PARA CONVERTER DE POLAR PARA RETANGULO-----------------------------------------
//retorna um struct expressão com o resultado a conversão
void converterPolarParaRetang(numeroC ** result){
	
	float conjugado=(*result)->primeiroValor, angulo=(*result)->segundoValor;
	char cod=(*result)->codigo;
	
	(*result)->primeiroValor=0;
	(*result)->segundoValor=0;
	(*result)->codigo=0;
	
	//pela formula raiz quadrada de valor real ao quadrado + raiz quadrada do valor imaginario ao quadrado
	if(cod=='p'  || cod=='P'){
		//conversão para radianos
		//divide por 180 no caso de conversao para radianos
		float cosseno= cos (angulo * PI / 180.0 );
		//multiplica por 180 no caso de conversao para radianos
		(*result)->primeiroValor=(int)conjugado*cosseno;
		//multiplica por 180 para radianos converte denovo para volta 
		float seno= sin (angulo * PI / 180.0 );
		(*result)->segundoValor=(int)conjugado*seno;
		(*result)->codigo='i';
	}else if(cod=='i'  || cod=='I'){
		//Se for do tipo i retornará uma expressao comas mesmas caracteristicas
		(*result)->primeiroValor=conjugado;
		(*result)->segundoValor=angulo;
		(*result)->codigo=cod;
	}
}

//-------------------------------------------METODO DE SOMA NUMEROS COMPLEXOS-------------------------------------------------------
void somaRetang(numeroC expressao1, numeroC expressao2, numeroC ** result){
	int real1=(expressao1).primeiroValor,real2=(expressao2).primeiroValor,imag1=(expressao1).segundoValor,imag2=(expressao2).segundoValor; 
	char cod1=(expressao1).codigo, cod2=(expressao2).codigo;
	
	if((cod1=='i' || cod1=='I' ) && (cod2=='i' || cod2=='I' )){
		(*result)=(numeroC *) malloc(sizeof(numeroC));
		if((*result)==NULL){
			avisoErro(11);
		}
		(*result)->primeiroValor=real1+real2;
		(*result)->segundoValor=imag1+imag2;
		(*result)->codigo=cod1;
	}else{
		//printf("Erro de soma: Tipos diferentes de expressoes");
		avisoErro(4);
		(*result)=(numeroC *) malloc(sizeof(numeroC));
		if((*result)==NULL){
			avisoErro(11);
		}
		(*result)->primeiroValor=0;
		(*result)->segundoValor=0;
		(*result)->codigo='0';
	}
}

//-------------------------------------------METODO DE SUBTRAÇÃO NUMEROS COMPLEXOS--------------------------------------------------
void subRetang(numeroC expressao1, numeroC expressao2, numeroC ** result){
	int real1=(expressao1).primeiroValor,real2=(expressao2).primeiroValor,imag1=(expressao1).segundoValor,imag2=(expressao2).segundoValor; 
	char cod1=(expressao1).codigo, cod2=(expressao2).codigo;
	
	if((cod1=='i' || cod1=='I' ) && (cod2=='i' || cod2=='I' )){
		(*result)=(numeroC *) malloc(sizeof(numeroC));
		if((*result)==NULL){
			avisoErro(11);
		}
		(*result)->primeiroValor=real1-real2;
		(*result)->segundoValor=imag1-imag2;
		(*result)->codigo=cod1;
	}else{
		//printf("Erro na subtracao: Tipos diferentes de expressoes\n");
		avisoErro(5);
		(*result)=(numeroC *) malloc(sizeof(numeroC));
		if((*result)==NULL){
			avisoErro(11);
		}
		(*result)->primeiroValor=0;
		(*result)->segundoValor=0;
		(*result)->codigo='0';
	}
}

//-------------------------------------------METODO DE MULTIPLICAÇÃO NUMEROS COMPLEXOS-------------------------------------------------------
void multiPolar(numeroC expressao1, numeroC expressao2, numeroC ** result){
	int valor1=(expressao1).primeiroValor,valor2=(expressao2).primeiroValor,angulo1=(expressao1).segundoValor,angulo2=(expressao2).segundoValor; 
	char cod1=(expressao1).codigo, cod2=(expressao2).codigo;
	if((cod1=='p' || cod1=='P' ) && (cod2=='p' || cod2=='P' )){
		(*result)=(numeroC *) malloc(sizeof(numeroC));
		if((*result)==NULL){
			avisoErro(11);
		}
		(*result)->primeiroValor=valor1*valor2;
		(*result)->segundoValor=angulo1+angulo2;
		(*result)->codigo=cod1;
	}else{
		//printf("Erro na Multiplica: Tipos diferentes de expressoes");
		avisoErro(6);
		(*result)=(numeroC *) malloc(sizeof(numeroC));
		if((*result)==NULL){
			avisoErro(11);
		}
		(*result)->primeiroValor=0;
		(*result)->segundoValor=0;
		(*result)->codigo='0';
	}
}

//-------------------------------------------METODO DE POTENCIA NUMEROS COMPLEXOS-------------------------------------------------------
void potenciaPolar(numeroC expressao1, int potencia, numeroC ** result){
	int valor1=(expressao1).primeiroValor,angulo1=(expressao1).segundoValor; 
	char cod1=(expressao1).codigo;
	
	if((cod1=='p' || cod1=='P' )){
		(*result)=(numeroC *) malloc(sizeof(numeroC));
		if((*result)==NULL){
			avisoErro(11);
		}
		(*result)->primeiroValor = pow(valor1, potencia);
		(*result)->segundoValor = angulo1 * potencia;
		(*result)->codigo = cod1;
	}else{
		//printf("Erro na Potencia: Tipos diferentes de expressoes");
		avisoErro(7);
		(*result)=(numeroC *) malloc(sizeof(numeroC));
		if((*result)==NULL){
			avisoErro(11);
		}
		(*result)->primeiroValor=0;
		(*result)->segundoValor=0;
		(*result)->codigo='0';
	}
}

//-------------------------------------------METODO DE DIVISÃO NUMEROS COMPLEXOS-------------------------------------------------------
void divPolar(numeroC expressao1, numeroC expressao2, numeroC ** result){
	int valor1=(expressao1).primeiroValor, valor2=(expressao2).primeiroValor, angulo1=(expressao1).segundoValor, angulo2=(expressao2).segundoValor; 
	char cod1=(expressao1).codigo, cod2=(expressao2).codigo;

	
	if((cod1=='p' || cod1=='P' ) && (cod2=='p' || cod2=='P' ) && valor2!=0){
		(*result)=(numeroC *) malloc(sizeof(numeroC));
		if((*result)==NULL){
			avisoErro(11);
		}
		(*result)->primeiroValor=valor1/valor2;
		(*result)->segundoValor=angulo1-angulo2;
		(*result)->codigo=cod1;
	}else{
		//printf("Erro na divisao: Tipos diferentes de expressoes");
		avisoErro(8);
		(*result)=(numeroC *) malloc(sizeof(numeroC));
		if((*result)==NULL){
			avisoErro(11);
		}
		(*result)->primeiroValor=0;
		(*result)->segundoValor=0;
		(*result)->codigo='0';
	}
}
//-----------------------------------------------CÓDIGO DE EXECUÇÃO DO PROGRAMA----------------------------------------------------------

void inicio(){
	FILE * entradaArq;
	FILE * saidaArq;
	char * calculo;
	char operacao;
	numeroC * expressao1;
	numeroC * expressao2;
	numeroC * resultado;
	
	printf("\n\n---------------Calculadora Complexa-------------------\n");
	printf("\nAluno: Jesimon Barreto Santos ------------------------\n");
	
	bool erroLeitura=abrirArquivo(&entradaArq,"entrada.txt","r");
	bool erroEscrita=abrirArquivo(&saidaArq,"saida.txt","w");
	if(erroLeitura==false && erroEscrita==false){
		
		while(!proximoCalculoEntrada(entradaArq,&calculo)){
			printf("%s Calculando....\n",calculo);
			bool erroLetras;
			//Retorna por meio de referencia
			multiIndicadorExpre(calculo,&erroLetras);
			if(!erroLetras){
				bool erroSinal;
				//Retorna por meio de referencia
				verificarDualidadeSinal(calculo,&erroSinal);
				if(!erroSinal){
					bool erroE1;
					extrairInformacoesExpressao1(calculo,&expressao1,&erroE1);
					//Retirando a operacao
					bool erroO;
					extrairInformacoesOperacao(calculo, (*expressao1).posicaoFinalString,&operacao,&erroO);
					if(!erroO && !erroE1){
						//If para testar se é conversão
						bool erroE2;
						if(operacao!='='){
							//Retirando a segunda operacao usando +1 porque estou usando a informacao da expressao 1
							//Pegando valor de expressão2 
							extrairInformacoesExpressao2(calculo,operacao, (*expressao1).posicaoFinalString+1,&expressao2,&erroE2);
						}
						if(!erroE2){
								switch(operacao){
											case '+':
												//A soma só é feita se as duas forem tipo retangular;
												if(((*expressao1).codigo=='i' || (*expressao1).codigo=='I') && (((*expressao2).codigo=='i' || (*expressao2).codigo=='I'))){
													somaRetang((*expressao1),(*expressao2),&resultado);
												}else{
													converterPolarParaRetang(&expressao1);
													converterPolarParaRetang(&expressao2);
													somaRetang((*expressao1),(*expressao2),&resultado);
												}
												if((*resultado).codigo!='0'){
													int sttgrava=0;
													if((*resultado).segundoValor<0){
														sttgrava=fprintf(saidaArq,"%s %d%d%c;\n",calculo,(*resultado).primeiroValor,
																											(*resultado).segundoValor,(*resultado).codigo);
														printf("%s %d%d%c;\n",calculo,(*resultado).primeiroValor,
																											(*resultado).segundoValor,(*resultado).codigo);
													}else{
														sttgrava=fprintf(saidaArq,"%s %d+%d%c;\n",calculo,(*resultado).primeiroValor,
																											(*resultado).segundoValor,(*resultado).codigo);
														printf("%s %d+%d%c;\n",calculo,(*resultado).primeiroValor,
																											(*resultado).segundoValor,(*resultado).codigo);
													}
													if(sttgrava<0){
														printf("\nErro na Gravacao\n");
													}
												}else{
													int sttgrava=0;
														sttgrava=fprintf(saidaArq,"%s ERRO\n",calculo);
													if(sttgrava<0){
														printf("\nErro na Gravacao\n");
													}
												}
											break;
					
										case '-':
											//A subtracao só é feita se as duas forem tipo retangular;
											if(((*expressao1).codigo=='i' || (*expressao1).codigo=='I') && (((*expressao2).codigo=='i' || (*expressao2).codigo=='I'))){
												subRetang((*expressao1),(*expressao2),&resultado);
											}else{
												//converter a expressao 1 de polar para retangular
												//converter a expressao 2 de polar para retangular
												converterPolarParaRetang(&expressao1);
												converterPolarParaRetang(&expressao2);
												subRetang((*expressao1),(*expressao2),&resultado);
											}
											
											if((*resultado).codigo!='0'){
												int sttgrava=0;
												if((*resultado).segundoValor<0){
													sttgrava=fprintf(saidaArq,"%s %d%d%c;\n",calculo,(*resultado).primeiroValor,
																										(*resultado).segundoValor,(*resultado).codigo);
												}else{
													sttgrava=fprintf(saidaArq,"%s %d+%d%c;\n",calculo,(*resultado).primeiroValor,
																										(*resultado).segundoValor,(*resultado).codigo);
												}
												if(sttgrava<0){
													printf("\nErro na Gravacao\n");
												}
											}else{
												int sttgrava=0;
													sttgrava=fprintf(saidaArq,"%s ERRO\n",calculo);
												if(sttgrava<0){
													printf("\nErro na Gravacao\n");
												}
											}
										break;
						
										case '*':
											//A multiplicação só é feita se as duas forem tipo Polar;
											if(((*expressao1).codigo=='p' || (*expressao1).codigo=='P') && (((*expressao2).codigo=='p' || (*expressao2).codigo=='P'))){
												multiPolar((*expressao1),(*expressao2),&resultado);
											}else{
												//converter a expressao 1 
												//converter a expressao 2 
												converterRetangParaPolar(&expressao1);
												converterRetangParaPolar(&expressao2);
												multiPolar((*expressao1),(*expressao2),&resultado);
											}
											if((*resultado).codigo!='0'){
												int sttgrava=0;
												if((*resultado).segundoValor<0){
													sttgrava=fprintf(saidaArq,"%s %d%d%c;\n",calculo,(*resultado).primeiroValor,
																										(*resultado).segundoValor,(*resultado).codigo);
												}else{
													sttgrava=fprintf(saidaArq,"%s %d+%d%c;\n",calculo,(*resultado).primeiroValor,
																										(*resultado).segundoValor,(*resultado).codigo);
												}
												if(sttgrava<0){
													printf("\nErro na Gravacao\n");
												}
											}else{
												 int sttgrava=0;
													sttgrava=fprintf(saidaArq,"%s ERRO\n",calculo);
												if(sttgrava<0){
													printf("\nErro na Gravacao\n");
												}
											}
										break;
						
										case '/':
											//A divisao só é feita se as duas forem tipo Polar;
											if(((*expressao1).codigo=='p' || (*expressao1).codigo=='P') && (((*expressao2).codigo=='p' || (*expressao2).codigo=='P'))){
												divPolar((*expressao1),(*expressao2),&resultado);
											}else{
												converterRetangParaPolar(&expressao1);
												converterRetangParaPolar(&expressao2);
												divPolar((*expressao1),(*expressao2),&resultado);
												
											}
											if((*resultado).codigo!='0'){
												int sttgrava=0;
												if((*resultado).segundoValor<0){
													sttgrava=fprintf(saidaArq,"%s %d%d%c;\n",calculo,(*resultado).primeiroValor,
																										(*resultado).segundoValor,(*resultado).codigo);
												}else{
													sttgrava=fprintf(saidaArq,"%s %d+%d%c;\n",calculo,(*resultado).primeiroValor,
																										(*resultado).segundoValor,(*resultado).codigo);
												}
												if(sttgrava<0){
													printf("\nErro na Gravacao\n");
												}
											}else{
												 int sttgrava=0;
													sttgrava=fprintf(saidaArq,"%s ERRO\n",calculo);
												if(sttgrava<0){
													printf("\nErro na Gravacao\n");
												}
											}
										break;
					
										case '^':
											//A Potencia só é feita se as duas forem tipo Polar;
											if(((*expressao1).codigo=='p' || (*expressao1).codigo=='P') && (((*expressao2).codigo=='p' || (*expressao2).codigo=='P'))){
												//O padrao escolhido foi colocar o valor da potencia no primeiro valor da segunda expressao
												potenciaPolar((*expressao1),(*expressao2).primeiroValor,&resultado);
											}else{
												//converter a expressao 1  
												converterRetangParaPolar(&expressao1);
												potenciaPolar((*expressao1),(*expressao2).primeiroValor,&resultado);
											}
											if((*resultado).codigo!='0'){
												int sttgrava=0;
												if((*resultado).segundoValor<0){
													sttgrava=fprintf(saidaArq,"%s %d%d%c;\n",calculo,(*resultado).primeiroValor,
																										(*resultado).segundoValor,(*resultado).codigo);
												}else{
													sttgrava=fprintf(saidaArq,"%s %d+%d%c;\n",calculo,(*resultado).primeiroValor,
																										(*resultado).segundoValor,(*resultado).codigo);
												}
												if(sttgrava<0){
													printf("\nErro na Gravacao\n");
												}
											}else{
												int sttgrava=0;
													sttgrava=fprintf(saidaArq,"%s ERRO\n",calculo);
												if(sttgrava<0){
													printf("\nErro na Gravacao\n");
												}
											}
										
										// Erro de tipo i no lugar de p
										break;
					
										case '=':
											if((*expressao1).codigo=='p' || (*expressao1).codigo=='P'){
												converterPolarParaRetang(&expressao1);
											}else{
												converterRetangParaPolar(&expressao1);
											}
											if((*expressao1).codigo!='0'){
												int sttgrava=0;
												if((*expressao1).segundoValor<0){
													sttgrava=fprintf(saidaArq,"%s %d%d%c;\n",calculo,(*expressao1).primeiroValor,
																										(*expressao1).segundoValor,(*expressao1).codigo);
												}else{
													sttgrava=fprintf(saidaArq,"%s %d+%d%c;\n",calculo,(*expressao1).primeiroValor,
																										(*expressao1).segundoValor,(*expressao1).codigo);
												}
												if(sttgrava<0){
													printf("\nErro na Gravacao\n");
												}
											}else{
												int sttgrava=0;
													sttgrava=fprintf(saidaArq,"%s ERRO\n",calculo);
												if(sttgrava<0){
													printf("\nErro na Gravacao\n");
												}
											}
										break;
								}
						}
					}else{
						int sttgrava=0;
							sttgrava=fprintf(saidaArq,"%s ERRO (Sinal ou Operacao entrada errada)\n",calculo);
						if(sttgrava<0){
							printf("\nErro na Gravacao\n");
						}
					}
				}else{
					int sttgrava=0;
						sttgrava=fprintf(saidaArq,"%s ERRO (Sinal)\n",calculo);
					if(sttgrava<0){
						printf("\nErro na Gravacao\n");
					}
				}
			}else{
				int sttgrava=0;
					sttgrava=fprintf(saidaArq,"%s ERRO (Letras a mais)\n)",calculo);
				if(sttgrava<0){
					printf("\nErro na Gravacao\n");
				}
			}
			free(calculo);
			free(expressao1);
			free(expressao2);
			free(resultado);
			calculo=NULL;
			expressao1=NULL;
			expressao2=NULL;
			resultado=NULL;
			printf("\nGravando Resultado....\n",calculo);
		}
		
		fecharArquivo(entradaArq);
		fecharArquivo(saidaArq);
		entradaArq=NULL;
		saidaArq=NULL;
	}
}


//------------------------------------------- METODO PRINCIPAL -------------------------------------------------------------

int main(){
	
	inicio();

	return 0;
}