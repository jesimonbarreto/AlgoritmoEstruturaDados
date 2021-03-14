#include <stdio.h>
#include <math.h>
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


//Projetos dos métodos(funções) presentes no arquivo

void avisoErro(int vErro);
bool retirarEspacos(char * entrada);
bool verificarDualidadeSinal(char * entrada);
bool multiIndicadorExpre(char * entrada);
struct expressao extrairInformacoesExpressao1(char * entrada);
char extrairInformacoesOperacao(char * entrada,int posicao);
struct expressao extrairInformacoesExpressao2(char * entrada,char operacao, int posicao);
struct expressao converterRetangParaPolar(struct expressao expressaoLocal);
struct expressao converterPolarParaRetang(struct expressao expressaoLocal);
struct expressao somaRetang(struct expressao expressao1, struct expressao expressao2);
struct expressao subRetang(struct expressao expressao1, struct expressao expressao2);
struct expressao multiPolar(struct expressao expressao1, struct expressao expressao2);
struct expressao potenciaPolar(struct expressao expressao1, int potencia);
struct expressao divPolar(struct expressao expressao1, struct expressao expressao2);




//---------------------------- STRUCT EXPRESSAO--------------------------------------------------------------------------------------------------

//Criar struct para as expressoes onde codigo é chamado do caractere que acompanha a expressao para indicar o tipo, pode ser i (I) ou p (P)
struct expressao{
	int primeiroValor;//Pode ser o valor real caso Retangular ou pode ser o conjugado se for na forma Polar
	int segundoValor;//Pode ser o valor imaginário caso seja Retangular ou pode ser  
	char codigo;//i ou p
	int posicaoFinalString;//Ponto onde acaba a expressao na string geral
};


//----------------------------------------Aviso de Erro ------------------------------------------------------------------------
//FAzer função contem registros de erroAvisos que recebe um valor e exibe o erroAviso para o usuário, na tabela indica qual erroAviso aconteceu
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
}


//--------------------------------------MÉTODO RETIRAR ESPAÇOS-----------------------------------------------------------------------------------
//Metodo para retirar espaços e tudo que estiver depois do '='
bool retirarEspacos(char * entrada){
	int i=0,j=0;
	//Deve ser igual a quantidade da string principal
	char auxiliar[40];
	bool erro=false;
	//for que anda o vetor todo
	for(;i<tamanhoString;i++){
		//Se a entrada for igual a espaço em branco então
		 if(entrada[i]!=' '){
			//Se caractere diferente de espaço entao passa para variavel
			auxiliar[j]=entrada[i];
			j++;	
		}		
	}
	i=0;
	
	while(entrada[i]!='='){
		entrada[i]=auxiliar[i];
		//Se chegar ao final do vetor sem encontrar o caractere '=' então dará erroAviso
		if(i==tamanhoString-1){
			//chamar um metodo para retornar erroAviso
			//printf("Erro Cod 1: Nao foi digitado o caracter =\n");
			avisoErro(1);
			//Ir para o inicio do laço
			erro=true;
			break;
		}
		i++;
	}
	//Adiciona o 
	//Fecha a string
	entrada[i]='=';
	entrada[i+1]='\0';
	return erro;
	
}

//-------------------------------------------------MÉTODO VERIFICAR DUALIDADE DE SINAL------------------------------------------------------------
//Verificar se tem dois sinais juntos
//retornar true ou 1 caso aconteça o erroAviso
bool verificarDualidadeSinal(char * entrada){
	int i, numeroSinalSeguidos=0;
	bool DualidadeSinal=false;
	for(i=0;i<tamanhoString;i++){
		//Nao é um numero então pode ser um sinal ou indicador de tipo de equação
		//Verificador de Operaçao
			//Se for um sinal soma 1 em numeroSinalSeguidos se passar de 1 é porque está errado
			if(entrada[i]=='-'){
				numeroSinalSeguidos++;
			}else if(entrada[i]=='+'){
				numeroSinalSeguidos++;
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
			DualidadeSinal=true;
		}
		
	}
	return DualidadeSinal;
}

//-----------------------------------------------MÉTODO INDICAR VARIAS LETRAS--------------------------------------------------------------
//Caso o 'i' ou 'p' (indicadores de expressao) sejam mais que 2 
//Verifica quantidade de letras na string
bool multiIndicadorExpre(char * entrada){
	int i=0,contIndicadoresI=0,contIndicadoresP=0,contLetras=0;
	bool multIndicador=false;
	
	while(entrada[i]!='='){
		//Verificar se a string tem mais de 2 letras, tanto maiusculas quanto minusculas
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
	return multIndicador;
}

//------------------------------------METODOs EXTRAIR INFORMACOES-------------------------------------------------------------------------------------
//Da expressao 1
struct expressao extrairInformacoesExpressao1(char * entrada){
	//Struct que será retornado
	struct expressao expressao1;
	int i, valor1Expre=0, valor2Expre=0;
	//valor do indicador da expressao 1 
	char codigo;
	//----------------------------------Primeiro Valor---Primeira Expressao----------------------------
	i=0;
	//Verifica se o primerio caracter é aceito e se é um + ou - é necessário para atribuir valor
	if(entrada[i]<'0'||entrada[i]>'9'){
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
			struct expressao erro;
			erro.codigo='0';
			return erro;
		}
		
		valor1Expre+=entrada[i]-'0';
		i++;
	}
	
	//Se o primeiro caracter == '-' então é necessário multiplicar o primeiro valor da expressao 1 por -1;
	if(entrada[0]=='-' && valor1Expre!=0){
		valor1Expre*=(-1);
	}
	//-----------------------------------Segundo Valor---Primeira Expressao------------------------------	
	//salvando posicao do sinal
	int posicaoSinal=i;
	//Pular o sinal, pois só será usado depois de adicionar o valor na variavel inteira
	i++;
	while((entrada[i]!='i' && entrada[i]!='I') && (entrada[i]!='p' && entrada[i]!='P')){
		if(valor2Expre>0){
			valor2Expre*=10;
		}
		valor2Expre+=entrada[i]-'0';
		i++;
	}
	//Se o primeiro caracter == '-' então é necessário multiplicar o primeiro valor da expressao 1 por -1;
	if(entrada[posicaoSinal]=='-' && valor2Expre!=0){
		valor2Expre*=(-1);
	}
	
	//--------------------------------------Valor indicador da primeira expressao------------------------
	codigo=entrada[i];
	//Fechando primeira expressão
	expressao1.primeiroValor=valor1Expre;
	expressao1.segundoValor=valor2Expre;
	expressao1.codigo=codigo;
	expressao1.posicaoFinalString=i; //A posicao i nesta parte será a ultima posicao da expressao na string
	
	//Retorna o valor da expressao 1 na  
	return expressao1;
}

//Entrada é a String, Posicao é o valor do ponto em que a expressao parou no outro metodo
char extrairInformacoesOperacao(char * entrada,int posicao){
	//Operaçao Entre os valores complexos
	char operacao;
	//Somo mais 1 pois o valor passado é o final da primeira operacao
	posicao++;
	operacao=entrada[posicao];

	return operacao;
}

//Entrada são a String, Posicao é o valor do ponto em que a expressao parou no outro metodo e operacao é a operacao entre funcoes
struct expressao extrairInformacoesExpressao2(char * entrada,char operacao, int posicao){
	struct expressao expressao2;
	int valor1Expre=0, valor2Expre=0,posicaoSinal=0;
	char codigo;
	posicao++;
	//Se for potencia é necessario apenas colocar pegar o numero ao qual quer elevar
	//Nesse caso o valor irá na primeira posicao do Struct e a segunda sera 0
	if(operacao=='^'){
		while(entrada[posicao]!='='){
			if(valor1Expre>0){
				valor1Expre*=10;
			}
			if(entrada[posicao]=='i' || entrada[posicao]=='I' || entrada[posicao]=='p' || entrada[posicao]=='P'){
				//entao não foi digitado no formato certo
				avisoErro(9);		
				struct expressao erro;
				erro.codigo='0';
				return erro;
			}
			valor1Expre+=entrada[posicao]-'0';
			posicao++;
		}
	}else{
		//Vai converte para inteiro todo o valor ate que apareça um sinal
		while(entrada[posicao]!='+' && entrada[posicao]!='-'){
			if(valor1Expre>0){
				valor1Expre*=10;
			}
			if(entrada[posicao]=='i' || entrada[posicao]=='I' || entrada[posicao]=='p' || entrada[posicao]=='P'){
				//entao não foi digitado no formato certo
				avisoErro(9);			
				struct expressao erro;
				erro.codigo='0';
				return erro;
			}
			valor1Expre+=entrada[posicao]-'0';
			posicao++;
		}
	
		//Não tem como o primeiro numero da segunda parte ser negativo?
	
	//---------------------------------------segundo valor indicador segunda expressao----------------------------------------------
		//salvando posicao do sinal
		posicaoSinal=posicao;
		//Pular o sinal, pois só será usado depois de adicionar o valor na variavel inteira
		posicao++;
		while(entrada[posicao]!='i' && entrada[posicao]!='I' && entrada[posicao]!='p' && entrada[posicao]!='P'){
			if(valor2Expre>0){
				valor2Expre*=10;
			}
			valor2Expre+=entrada[posicao]-'0';
			posicao++;
		}
	//Se o primeiro caracter == '-' então é necessário multiplicar o primeiro valor da expressao 1 por -1;
		if(entrada[posicaoSinal]=='-' && valor2Expre!=0){
			valor2Expre*=(-1);
		}
		codigo=entrada[posicao];
	}
	
	expressao2.primeiroValor=valor1Expre;
	expressao2.segundoValor=valor2Expre;
	expressao2.codigo=codigo;
	expressao2.posicaoFinalString=posicao;
	
	return expressao2;
}

//---------------------------------------------METODO PARA CONVERTER DE RETANGULO PARA POLAR--------------------------------------------
//retorna um struct expressão com o resultado a conversão
struct expressao converterRetangParaPolar(struct expressao expressaoLocal){
	int real=(expressaoLocal).primeiroValor, imag=(expressaoLocal).segundoValor;
	char tipo=(expressaoLocal).codigo;
	struct expressao resultado;
	
	//pela formula raiz quadrada de valor real ao quadrado + raiz quadrada do valor imaginario ao quadrado
	resultado.primeiroValor=0;
	resultado.segundoValor=0;
	resultado.codigo='0';
	//pela formula raiz quadrada de valor real ao quadrado + raiz quadrada do valor imaginario ao quadrado
	if(tipo=='i'  || tipo=='I'){
		//valores double?
		//pela formula raiz quadrada de valor real ao quadrado + raiz quadrada do valor imaginario ao quadrado
		resultado.primeiroValor= sqrt((real*real + imag*imag));
		//Divide por 180 converter para radianos
		float rad=(imag/(real*1.0));
		//multiplica por 180 para converter de novo para graus
		int graus=atan(rad)*180/M_PI;
		resultado.segundoValor= graus;
		resultado.codigo='p';
		printf("passou aqui");
	}else if(tipo=='p'  || tipo=='P'){
		//Se for do tipo i retornará uma expressao comas mesmas caracteristicas
		resultado.primeiroValor=real;
		resultado.segundoValor=imag;
		resultado.codigo='p';
		
		//Advertencia
		printf("Ja esta no formato Retangular\n");
	}
	
	return resultado;
}

//---------------------------------------------METODO PARA CONVERTER DE POLAR PARA RETANGULO-----------------------------------------
//retorna um struct expressão com o resultado a conversão
struct expressao converterPolarParaRetang(struct expressao expressaoLocal){
	float conjugado=(expressaoLocal).primeiroValor, angulo=(expressaoLocal).segundoValor;
	char cod=(expressaoLocal).codigo;
	struct expressao convertido;
	
	convertido.primeiroValor=0;
	convertido.segundoValor=0;
	convertido.codigo=0;
	
	//pela formula raiz quadrada de valor real ao quadrado + raiz quadrada do valor imaginario ao quadrado
	if(cod=='p'  || cod=='P'){
		//conversão para radianos
		//divide por 180 no caso de conversao para radianos
		float cosseno= cos (angulo * PI / 180.0 );
		//multiplica por 180 no caso de conversao para radianos
		convertido.primeiroValor=(int)conjugado*cosseno;
		//multiplica por 180 para radianos converte denovo para volta 
		float seno= sin (angulo * PI / 180.0 );
		convertido.segundoValor=(int)conjugado*seno;
		convertido.codigo='i';
	}else if(cod=='i'  || cod=='I'){
		//Se for do tipo i retornará uma expressao comas mesmas caracteristicas
		convertido.primeiroValor=conjugado;
		convertido.segundoValor=angulo;
		convertido.codigo=cod;
		//advertencia
		printf("Ja esta no formato Retangular\n");
	}
	
	return convertido;
	
}

//-------------------------------------------METODO DE SOMA NUMEROS COMPLEXOS-------------------------------------------------------
struct expressao somaRetang(struct expressao expressao1, struct expressao expressao2){
	int real1=(expressao1).primeiroValor,real2=(expressao2).primeiroValor,imag1=(expressao1).segundoValor,imag2=(expressao2).segundoValor; 
	char cod1=(expressao1).codigo, cod2=(expressao2).codigo;
	struct expressao resultado;
	
	if((cod1=='i' || cod1=='I' ) && (cod2=='i' || cod2=='I' )){
		(resultado).primeiroValor=real1+real2;
		(resultado).segundoValor=imag1+imag2;
		(resultado).codigo=cod1;
	}else{
		//printf("Erro de soma: Tipos diferentes de expressoes");
		avisoErro(4);
	}
	return resultado;
}

//-------------------------------------------METODO DE SUBTRAÇÃO NUMEROS COMPLEXOS--------------------------------------------------
struct expressao subRetang(struct expressao expressao1, struct expressao expressao2){
	int real1=(expressao1).primeiroValor,real2=(expressao2).primeiroValor,imag1=(expressao1).segundoValor,imag2=(expressao2).segundoValor; 
	char cod1=(expressao1).codigo, cod2=(expressao2).codigo;
	struct expressao resultado;
	
	if((cod1=='i' || cod1=='I' ) && (cod2=='i' || cod2=='I' )){
		(resultado).primeiroValor=real1-real2;
		(resultado).segundoValor=imag1-imag2;
		(resultado).codigo=cod1;
	}else{
		//printf("Erro na subtracao: Tipos diferentes de expressoes\n");
		avisoErro(5);
	}
	return resultado;
	
}

//-------------------------------------------METODO DE MULTIPLICAÇÃO NUMEROS COMPLEXOS-------------------------------------------------------
struct expressao multiPolar(struct expressao expressao1, struct expressao expressao2){
	int valor1=(expressao1).primeiroValor,valor2=(expressao2).primeiroValor,angulo1=(expressao1).segundoValor,angulo2=(expressao2).segundoValor; 
	char cod1=(expressao1).codigo, cod2=(expressao2).codigo;
	struct expressao resultado;
	(resultado).primeiroValor=0;
	(resultado).segundoValor=0;
	(resultado).codigo='0';
	
	if((cod1=='p' || cod1=='P' ) && (cod2=='p' || cod2=='P' )){
		(resultado).primeiroValor=valor1*valor2;
		(resultado).segundoValor=angulo1+angulo2;
		(resultado).codigo=cod1;
	}else{
		//printf("Erro na Multiplica: Tipos diferentes de expressoes");
		avisoErro(6);
	}
	
	return resultado;
}

//-------------------------------------------METODO DE POTENCIA NUMEROS COMPLEXOS-------------------------------------------------------
struct expressao potenciaPolar(struct expressao expressao1, int potencia){
	int valor1=(expressao1).primeiroValor,angulo1=(expressao1).segundoValor; 
	char cod1=(expressao1).codigo;
	struct expressao resultado;
	
	
	(resultado).primeiroValor = 0;
	(resultado).segundoValor = 0;
	(resultado).codigo = '0';
	
	if((cod1=='p' || cod1=='P' )){
		(resultado).primeiroValor = pow(valor1, potencia);
		(resultado).segundoValor = angulo1 * potencia;
		(resultado).codigo = cod1;
	}else{
		//printf("Erro na Potencia: Tipos diferentes de expressoes");
		avisoErro(7);
	}
	
	return resultado;
}

//-------------------------------------------METODO DE DIVISÃO NUMEROS COMPLEXOS-------------------------------------------------------
struct expressao divPolar(struct expressao expressao1, struct expressao expressao2){
	int valor1=(expressao1).primeiroValor, valor2=(expressao2).primeiroValor, angulo1=(expressao1).segundoValor, angulo2=(expressao2).segundoValor; 
	char cod1=(expressao1).codigo, cod2=(expressao2).codigo;
	struct expressao resultado;
		(resultado).primeiroValor=0;
		(resultado).segundoValor=0;
		(resultado).codigo='0';
	if((cod1=='p' || cod1=='P' ) && (cod2=='p' || cod2=='P' )){
		(resultado).primeiroValor=valor1/valor2;
		(resultado).segundoValor=angulo1-angulo2;
		(resultado).codigo=cod1;
	}else{
		//printf("Erro na divisao: Tipos diferentes de expressoes");
		avisoErro(8);
	}
	
	return resultado;
}

//------------------------------------------- METODO PRINCIPAL -------------------------------------------------------------

int main(){
	char valorDigitado[40];
	char operacao;
	struct expressao expressao1;
	struct expressao expressao2;
	struct expressao resultado;
	
	printf("\n\n---------------Calculadora Complexa-------------------\n");
	printf("\nAluno: Jesimon Barreto Santos ------------------------\n");
	printf("Calculo com NUMEROS INTEIROS \n");
	printf("\nExemplo de valores aceitos nessa primeira versao eh:");	
	printf("\n Soma(2+3i+3+4p)\n Subtracao(2+3i-3+4p)\n Multiplicacao(2+3i*3+4p)\n Divisao(2+3i/3+4p)\n Potencia por um natural (2+3i^3=)\n");
	printf("\n Digite o calculo desejado ate 40 caracteres (para finalizar digite 'S' ou 's'):  ");
	scanf("%[^\n]s", valorDigitado);
		while(valorDigitado[0]!= 's' && valorDigitado[0]!='S'){
			//Retira os espaços e verifica se existe o caractere '='
			bool erroEspaco=retirarEspacos(valorDigitado);
			if(!erroEspaco){
				//verifica se há letras erradas ou a mais 
				//retorna 1 ou 0
				bool erroLetras=multiIndicadorExpre(valorDigitado);
				if(!erroLetras){
					//Verifica se tem mais de um sinal
					//retorna 1 ou 0
					bool erroSinal=verificarDualidadeSinal(valorDigitado);
					if(!erroSinal){
			
						//Codigo para calcular expressao
				
						//Retirando as informações da primeira expressao da equacao
							expressao1=extrairInformacoesExpressao1(valorDigitado);
							//Retirando a operacao
							operacao=extrairInformacoesOperacao(valorDigitado, expressao1.posicaoFinalString);
							if(operacao!='='){
								//Retirando a segunda operacao usando +1 porque estou usando a informacao da expressao 1
								expressao2=extrairInformacoesExpressao2(valorDigitado,operacao, expressao1.posicaoFinalString+1);
							}
							//Erro de valor digitado fora do formato
							if(expressao1.codigo!='0' && expressao2.codigo!='0'){
					
								switch(operacao){
									case '+':
										//A soma só é feita se as duas forem tipo retangular;
										if((expressao1.codigo=='i' || expressao1.codigo=='I') && ((expressao2.codigo=='i' || expressao2.codigo=='I'))){
											resultado=somaRetang(expressao1,expressao2);
										}else{
										//converter a expressao 1 de polar para retangular
										struct expressao expressao1Retang=converterPolarParaRetang(expressao1);
										//converter a expressao 2 de polar para retangular
										struct expressao expressao2Retang=converterPolarParaRetang(expressao2);
										resultado=somaRetang(expressao1Retang,expressao2Retang);
									}
								
									printf("\n\nO resultado de %s eh : valor real: %d; valor imaginario: %d %c;\n",valorDigitado,resultado.primeiroValor,
																							resultado.segundoValor,resultado.codigo);
								break;
			
								case '-':
									//A subtracao só é feita se as duas forem tipo retangular;
									if((expressao1.codigo=='i' || expressao1.codigo=='I') && ((expressao2.codigo=='i' || expressao2.codigo=='I'))){
										resultado=subRetang(expressao1,expressao2);
									}else{
										//converter a expressao 1 de polar para retangular
										//converter a expressao 2 de polar para retangular
										struct expressao expressao1Retang=converterPolarParaRetang(expressao1);
										struct expressao expressao2Retang=converterPolarParaRetang(expressao2);
										resultado=subRetang(expressao1Retang,expressao2Retang);
										}
									
									printf("\n\nO resultado de %s: valor real: %d; valor imaginario: %d %c;\n", valorDigitado,resultado.primeiroValor,
																								resultado.segundoValor,resultado.codigo);
								break;

								case '*':
									//A multiplicação só é feita se as duas forem tipo Polar;
									if((expressao1.codigo=='p' || expressao1.codigo=='P') && ((expressao2.codigo=='p' || expressao2.codigo=='P'))){
										resultado=multiPolar(expressao1,expressao2);
									}else{
										//converter a expressao 1 
										//converter a expressao 2 
										struct expressao expressao1Polar=converterRetangParaPolar(expressao1);
										struct expressao expressao2Polar=converterRetangParaPolar(expressao2);
										resultado=multiPolar(expressao1Polar,expressao2Polar);
									}
									if(resultado.segundoValor<0){
										printf("\n\nO resultado na forma Polar de %s :  %d %d%c\n", valorDigitado,resultado.primeiroValor,resultado.segundoValor,resultado.codigo);
									}else{
										printf("\n\nO resultado na forma Polar de %s :  %d+%d%c\n", valorDigitado,resultado.primeiroValor,resultado.segundoValor,resultado.codigo);
									}
				
								break;
				
								case '/':
									//A divisao só é feita se as duas forem tipo Polar;
									if((expressao1.codigo=='p' || expressao1.codigo=='P') && ((expressao2.codigo=='p' || expressao2.codigo=='P'))){
										resultado=divPolar(expressao1,expressao2);
									}else{
										//converter a expressao 1 
										//converter a expressao 2 
										struct expressao expressao1Polar=converterRetangParaPolar(expressao1);
										struct expressao expressao2Polar=converterRetangParaPolar(expressao2);
										resultado=divPolar(expressao1Polar,expressao2Polar);
									}
									if(resultado.segundoValor<0){
										printf("\n\nO resultado na forma Polar de %s :  %d %d%c\n", valorDigitado,resultado.primeiroValor,resultado.segundoValor,resultado.codigo);
									}else{
										printf("\n\nO resultado na forma Polar de %s :  %d+%d%c\n", valorDigitado,resultado.primeiroValor,resultado.segundoValor,resultado.codigo);
									}
								break;
			
								case '^':
									//A Potencia só é feita se as duas forem tipo Polar;
									if((expressao1.codigo=='p' || expressao1.codigo=='P') && ((expressao2.codigo=='p' || expressao2.codigo=='P'))){
										//O padrao escolhido foi colocar o valor da potencia no primeiro valor da segunda expressao
										resultado=potenciaPolar(expressao1,expressao2.primeiroValor);
									}else{
										//converter a expressao 1 
										//converter a expressao 2 
										struct expressao expressao1Polar=converterRetangParaPolar(expressao1);
										resultado=potenciaPolar(expressao1Polar,expressao2.primeiroValor);
									}
									if(resultado.segundoValor<0){
										printf("\n\nO resultado na forma Polar de %s :  %d %d%c\n", valorDigitado,resultado.primeiroValor,resultado.segundoValor,resultado.codigo);
									}else{
										printf("\n\nO resultado na forma Polar de %s :  %d+%d%c\n", valorDigitado,resultado.primeiroValor,resultado.segundoValor,resultado.codigo);
									}
								
								// Erro de tipo i no lugar de p
								break;
			
								case '=':
									if(expressao1.codigo=='p' || expressao1.codigo=='P'){
										resultado=converterPolarParaRetang(expressao1);
									}else{
										resultado=converterRetangParaPolar(expressao1);
									}
									if(resultado.segundoValor<0){
										printf("\n\nO A conversao de %s:  %d %d%c\n", valorDigitado,resultado.primeiroValor,resultado.segundoValor,resultado.codigo);
									}else{
										printf("\n\nO A conversao de %s:  %d+%d%c\n", valorDigitado,resultado.primeiroValor,resultado.segundoValor,resultado.codigo);
									}
								break;
							}
						}
					}
					
				}	
			}else{
				//Erros encontrados
				printf("\n\nErros encontrados, Por favor, Tente novamente!\n\n");
			}
			//limpar a string antes de receber um novo valor
			int i=0;
			for(;i<tamanhoString;i++){
				valorDigitado[i]=' ';
			}
			setbuf(stdin, NULL);
			printf("\nExemplo de valores aceitos nessa primeira verao eh:");	
			printf("\n Soma(2+3i+3+4p)\n Subtracao(2+3i-3+4p)\n Multiplicacao(2+3i*3+4p)\n Divisao(2+3i/3+4p)\n Potencia por um natural (2+3i^3=)\n");
			printf("\n Digite o calculo desejado ate 40 caracteres (para finalizar digite 'S' ou 's'):  ");
			scanf("%[^\n]s", valorDigitado);
		}
		printf("\n\n---------------Calculadora Complexa-------------------\n");
		printf("\nAluno: Jesimon Barreto Santos ------------------------\n");
		printf("\n\n Obrigado pelo Uso!\n\n");
	return 0;
}