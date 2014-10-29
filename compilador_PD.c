//--------------------------- BIBLIOTECAS USADAS ------------------------------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include <conio.h>
#include "compilador_PD.h"
//Tamanho usado para as funções do compilador
#define TAM 1000
//Tamanho usado para as funções da caixa de texto
#define TAMANHO 200

typedef struct linha_de_comando {
	char instrucao[TAM];
	char parametro[TAM];
}executavel;

typedef struct{
	int x;
	int y;
}coordenadas;


//---------------------------- Carro --------------------------------------//




//---------------------------- FUNÇÕES UTILITÁRIAS DO COMPILADOR --------------------------------------//

/*Função que retorna o tamanho de um vetor*/
int retorna_tamanho(int v[]){
	return (int)(sizeof(v) / sizeof(v[0]));
}

/*Função que retorna o números de linhas usadas numa matriz*/
int retorna_tamanho_matriz(char (*matriz)[TAM]){
	int i;
	
	for(i=0; i<TAM; i++)
		if(matriz[i][0] == '\0')
			return i;

    return -1;
}

/*Função que imprime o conteúdo de uma string*/
void imprime_string(char frase[]){
	int i;
	
	printf("\n");
	
	for(i=0; i<strlen(frase); i++){
		printf("%c", frase[i]);
	}
	
	printf("\n");
}

/*Função que imprime o conteúdo de um vetor*/
void imprime_vetor(int v[], int n){
	int i;
	
	for(i=0; i<n; i++){
		printf("%d\n", v[i]);
	}
	
	printf("\n");
}

/*Função que imprime o conteúdo de uma matriz linha por linha*/
void imprime_matriz(char (*frase)[TAM], int n){
	int i;
	
	printf("\n");
	
	for(i=0; i<n; i++){
		printf("%d %s\n", i+1, frase[i]);
	}

	printf("\n");
}

/*Função que retorna o número de partições na quebra de uma string por um delimitador*/
int retorna_num_particoes(char frase[], char delimitador){
	int quantidade=0, i;
	
	for(i=0; i<strlen(frase); i++){
		if(frase[i] == delimitador)
			if(frase[i-1] != delimitador)
				quantidade++;
	}
	
	if(frase[0] == delimitador)
		quantidade--;
	if(frase[strlen(frase)-1] == delimitador)
		quantidade--;
		
	return quantidade;
}

/*Função que constrói uma frase a partir de um pedaço de uma string*/
void forma_frase(char frase_origem[], char novo[], int inicio, int fim){
	int i, j;
	
	j=0;
	for(i=inicio; i<=fim; i++){
		novo[j] = frase_origem[i];
		j++;
	}
	novo[j]='\0';
}

/*Função que desmembra um texto a partir de um delimitador em uma matriz, desprezando o próprio delimitador*/
int quebra_texto(char frase_origem[], char (*frase_destino)[TAM], char delimitador){
	int i, linha, inicio, quebrou;
	char aux[strlen(frase_origem)];
	
	linha = 0;
	inicio = 0;
	quebrou = 0;
	for(i = 0; i < strlen(frase_origem); i++){
		//A nova string será criada apenas quando o delimitador for achado e existe pelo menos um caractere entre o início e antes do delimitador
		if((frase_origem[i] == delimitador) && (inicio <= i-1)){
			forma_frase(frase_origem, aux, inicio, i-1);
			strcpy(frase_destino[linha], aux);
			inicio = i+1;
			linha++;
			quebrou = 1;
		}
		//Caso houver a ocorrência do delimitador sequencial, o início avança uma posição
		if(frase_origem[inicio] == delimitador)
			inicio++;
	}
	
	//Última partição
	if(inicio <= i-1){
		forma_frase(frase_origem, aux, inicio, i-1);
		strcpy(frase_destino[linha], aux);
	}

	if(quebrou)
		return 0;
	else{
		//strcpy(frase_destino[0], frase_origem);
		return -1;
	}
}

/*Função que elimina os espaços vazios no início e final de uma string*/
void limpa_espacos(char frase[]){
	int i, j;
	
	//Espaços no início da string
	while(frase[0]==' '){
		for(j=0; j<(strlen(frase)); j++){
			frase[j] = frase[j+1];
		}
	}
	
	//Espaços no final da string
	for(i=(strlen(frase)-1); frase[i]==' '; i--);
	frase[i+1] = '\0';
}

/*Função que elimina um caractere de uma string*/
void limpa_caractere(char frase[], int q){
	int i, j;
	
	i=0;
	for(i=0; i<strlen(frase); i++){
		if(frase[i] == q){
			for(j=i; j<strlen(frase); j++)
				frase[j]=frase[j+1];
			frase[j] = '\0';
		}
	}
}


void limpa_posicao(char frase[], int i){
    int j;
	
	for(j=i; j<strlen(frase); j++)
		frase[j]=frase[j+1];
}

/*Função que elimina o conteúdo de uma linha de uma matriz*/
void elimina_linha(char (*comando)[TAM], int *p, int linha){
	int i;
	
	for(i=linha; i<*p; i++)
		strcpy(comando[i], comando[i+1]);
	strcpy(comando[*p-1],"\0");
	(*p)--;
}

/*Função que limpa tudo que está após os comentários*/
void limpa_comentarios(char (*comando)[TAM], int *p){
	int i, j;
	char q = '/';
	
	i=0;
	for(i=0; i<*p; i++)
		if((comando[i][0] == q) && (comando[i][1] == q))
				elimina_linha(comando, &(*p), i);
	
	for(i=0; i<*p; i++)
		for(j=1; j<strlen(comando[i]); j++)
			if((comando[i][j] == q) && (comando[i][j+1] == q))
				comando[i][j] = '\0';
}

/*Função que busca e retorna a posição de um caractere específico numa string (a primeira ocorrência)*/
int busca_caractere(char frase[], char q){
	int i;
	
	for(i=0; i<strlen(frase); i++)
		if(frase[i]==q)
			return i;
	
	return -1;
}

/*Função que verifica se existe um caractere específico numa string*/
int existe_caractere(char frase[], char q){
	int i;
	
	for(i=0; i<strlen(frase); i++)
		if(frase[i]==q)
			return 1;
	
	return 0;
}

/*Função que verifica se o caractere é um caractere especial listado*/
int testa_caractere(char c){
	char caractere_especial[] = " ()/;'\"\n";
	int i;
	
	for(i=0; i<strlen(caractere_especial); i++)
		if(caractere_especial[i] == c)
			return 1;
	
	return 0;
}

/*Função que verifica se o caractere é um número*/
int testa_numerico(char c){
	char numero[]= "0123456789";
	int i;
	
	for(i=0; i<strlen(numero); i++)
		if(numero[i] == c)
			return 1;
			
	return 0;
}

/*Função que verifica se o caractere é uma letra listada*/
int testa_letra(char c){
	char letra[]= "abcçdefghijklmnopqrstuvwxyzABCÇDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;
	
	for(i=0; i<strlen(letra); i++)
		if(letra[i] == c)
			return 1;
			
	return 0;
}

/*Função que valida os caracteres de uma string e verifica se constam na lista*/
int caracteres_validos(char comando[]){
	int i, carac_especial, num, letra;
	for(i=0; i<strlen(comando); i++){
		carac_especial = testa_caractere(comando[i]);
		num = testa_numerico(comando[i]);
		letra = testa_letra(comando[i]);
		
		//Caso não seja um caractere especial, número ou letra listados, o caractere é inválido
		if((carac_especial==0) && (num==0) && (letra==0))
			return -1;
	}
	return 0;
}

/*Função que converte uma string inteira para letras maiúsculas*/
void converte_string_maiuscula(char palavra[]){
	int i;

	for(i=0; i<strlen(palavra); i++){
        if((palavra[i] == -89) || (palavra[i] == -121) || (palavra[i] == 135) || (palavra[i] == 128)){ //caso for um cidilha (maiúsculo ou minúsculo)
            palavra[i]='C';
            limpa_posicao(palavra, i-1);//eliminando um lixo adicionado pelo sistema (sinal de interrogação)
            i--;
        }
        else
		    palavra[i] = toupper(palavra[i]);
    }
}
	
/*Função que verificar se uma instrução é válida*/
int busca_dicionario(char palavra[]){
	converte_string_maiuscula(palavra);
	if(strcmp(palavra, "AVANCAR") == 0)
		return 1;
	if(strcmp(palavra, "VIRAR") == 0)
		return 2;
	if(strcmp(palavra, "RETORNAR") == 0)
		return 3;
		
	return -1;
}

/*Função que converte uma string em um inteiro*/
int converte_p_numero(char palavra[]){ //função similar à: int atoi(string);
    int i, valor=0, potencia=1;
    
	//atingindo o final da parte escrita na string
    for(i=0; palavra[i]!='\0'; i++);
    
	//varrendo desde a unidade do número
    for(i--; i>=0; i--)
    {
		//Tabela ASC II: '0' = 48, '1' = 49, '2' = 50, ...
        //acumulando a multiplicação pela potência correspondente em valor
		valor += (palavra[i]-48) * potencia;
        //acumulando a potência de acordo com a posição dos algarismos (1, 10, 100, 1000, ...)
		potencia *= 10;
    }
    
	//recebendo no ponteiro p o conteúdo de resp
    return valor;
}

/*Função que troca os valores de um vetor*/
void troca_elementos(int v[], int i, int j){
	int aux;

	aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

/*Função que inverte os valores de um vetor*/
void inverte_vetor(int v[], int n){
	int i, j;

	j = n-1;

	for(i=0; i<j; i++){
		troca_elementos(v, i, j);
		j--;
	}
}

/*Função que retorna a maior quantidade de caracteres de uma string em uma matriz*/
int encontra_maior(char (*comando)[TAM], int n){
	int i, maior;
	
	if(n == 0)
		return -1;
	
	maior = strlen(comando[0]);
	for(i=1; i<n; i++)
		if(strlen(comando[i]) > strlen(comando[maior]))
			maior = i;
	
	return maior+1;
}


//--------------------------- FUNÇÕES UTILITÁRIAS PARA A CAIXA DE TEXTO ---------------------------------------//
/*Função que verifica se uma matriz está vazia*/
int esta_vazia(char (*matriz)[TAMANHO]){
	int i;
	
	for(i=0; i<TAMANHO; i++)
		if(matriz[i][0] != '\0')
			return 0;

    return 1;
}

/*Função que retorna a ultima linha ocupada por uma matriz*/
int ultima_linha(char (*matriz)[TAMANHO]){
    int i, ultima=0;

    for(i=0; i<TAMANHO; i++)
        if(matriz[i][0] != '\0')
            ultima=i;

    return ultima;
}

/*Função que concatena uma string a partir de uma matriz*/
void concatena_strings(char (*matriz)[TAMANHO], char conjunto_string[], int n){
    int i;
    strcpy(conjunto_string, "");    
    
    for(i=0; i<n; i++){
        strcat(conjunto_string, matriz[i]);
        strcat(conjunto_string, "\n");       
    }
}

/*
//FUNÇÕES PARA MAPEAR LINHAS DA CAIXA DE TEXTO
int retorna_quantidade_caracteres(char frase[], int q){
	int i, cont=0;

	for(i=0; i<strlen(frase); i++)
		if(frase[i] == q)
			cont++;

	return cont;
}

int quebra_linha(char (*comando)[TAM], int linha, int quantidade){
	int i, j, k=1, resultado;
	char q=';';
	char frase[quantidade][TAM], aux[TAM];

	quebra_texto(comando[linha], frase, q);

	for (i=linha; i<(quantidade-1+linha); i++){
		strcpy(aux, comando[i+1]);
		for(j=(n-1); j>i; j++){
			strcpy(comando[j+1], comando[j]);
		}
		strcpy(comando[i], frase[k]);
		k++;
	}

}

void mapeia_linhas(char (*comando)[TAM], int n){

}
*/

//--------------------------- FUNÇÕES ANALÍTICAS DO COMPILADOR ---------------------------------------//
/*Função que faz a identificação de "tokens", eliminação de espaços vazios e/ou comentários*/
int analise_lexica(char texto[], char (*comando)[TAM], char mensagem[]){
	int i, n;
	char q = '\n'; //delimitador
	
	//token -> \n (quebra de linha)
	if(!existe_caractere(texto, q)){
		strcpy(comando[0], texto);
	}
	else{
		//quebra o texto em cada quebra de linha
		quebra_texto(texto, comando, q);
	}


	n = retorna_tamanho_matriz(comando);
	for(i=0; i<n; i++){
		//elimina os espaços vazios ao início e fim das frases
		limpa_espacos(comando[i]);
		
		//verifica se a cada linha existe o delimitador ;
		if(!existe_caractere(comando[i], ';')){
			//caso a linha esteja completamente vazia, é eliminada
			if(comando[i][0] == '\0')
				elimina_linha(comando, &n, i);
			else{
				sprintf(mensagem, "Erro: Está faltando o delimitador ; na linha %d.", i+1);
				return -1;
			}
		}
	}
	
	return 0;
}

/*Função que faz a validação de um programa*/
int analise_sintatica(char (*comando)[TAM], char (*mensagem)[TAM], int *j){
	int i, k, result, param, n;
	int abre_parenteses, fecha_parenteses, ponto_virgula;
	int composicao_invalida=0, formato_invalido=0, comando_invalido=0;
	//tam = encontra_maior(comando, n);
	char frase[2][TAM];
	
	//Verificando linha a linha
    n = retorna_tamanho_matriz(comando);
    for(i=0; i<n; i++){
		//1. Linha Vazia
		if(comando[i][0] == ';'){
			sprintf(mensagem[*j], "Linha %d: A linha está vazia.", i+1);
			(*j)++;
			comando_invalido=1;
			continue;
		}
		
		//2. Composição ('(', ')')
		result = caracteres_validos(comando[i]);
		if(result == -1){
			sprintf(mensagem[*j], "Linha %d: Caractere(s) inválido(s).", i+1);
			(*j)++;
			composicao_invalida=1;
		}
		result = busca_caractere(comando[i], '(');
		if(result == -1){
			sprintf(mensagem[*j], "Linha %d: A linha não possui o caractere '('.", i+1);
			(*j)++;
			composicao_invalida=1;
		}
		result = busca_caractere(comando[i], ')');
		if(result == -1){
			sprintf(mensagem[*j], "Linha %d: A linha não possui o caractere ')'.", i+1);
			(*j)++;
			composicao_invalida=1;
		}
		if(composicao_invalida==1){
			comando_invalido=1;
			continue;
		}
		
		//3. Formato/Ordem ( <INSTRUÇÃO>(<PARÂMETRO>); )
		abre_parenteses = busca_caractere(comando[i], '(');
		fecha_parenteses = busca_caractere(comando[i], ')');
		ponto_virgula = busca_caractere(comando[i], ';');
		if(abre_parenteses == 0){
			sprintf(mensagem[*j], "Linha %d: Deve haver uma instrução antes do '('.", i+1);
			(*j)++;
			formato_invalido=1;
		}
		if((fecha_parenteses - abre_parenteses) < 2){
			sprintf(mensagem[*j], "Linha %d: O caractere'(' deve estar antes do ')' e deve haver um parâmetro entre ambos.", i+1);
			(*j)++;
			formato_invalido=1;
		}
		if(ponto_virgula < fecha_parenteses){
			sprintf(mensagem[*j], "Linha %d: O caractere';' deve estar após o ')'.", i+1);
			(*j)++;
			formato_invalido=1;
		}
		if(formato_invalido==1){
			comando_invalido=1;
			continue;
		}
		
		//4. Repartir Linha e limpar os espaços
		//Instrução
		forma_frase(comando[i], frase[0], 0, abre_parenteses-1);
		limpa_espacos(frase[0]);
		//Parâmetro
		forma_frase(comando[i], frase[1], abre_parenteses+1, fecha_parenteses-1);
		limpa_espacos(frase[1]);
		
		//5. Validar Instrução
		result = busca_dicionario(frase[0]);
		if(result==-1){
			sprintf(mensagem[*j], "Linha %d: Instrução inválida.\nInstruções válidas: (1) AVANÇAR (2) VIRAR (3) RETORNAR", i+1);
			(*j)++;
			comando_invalido=1;
			continue;
		}

		//6. Parâmetro
		if((result == 1) || (result == 3)){
				for(k=0; k<strlen(frase[1]); k++){
					param = testa_numerico(frase[1][k]);
					if(param==0){
						sprintf(mensagem[*j], "Linha %d: Parâmetro inválido. Deve ser do tipo numérico.", i+1);
						(*j)++;
						comando_invalido=1;
					}
				}
        }
		if(result == 2){
                converte_string_maiuscula(frase[1]);
				if((strcmp(frase[1],"DIREITA")!=0) && (strcmp(frase[1],"ESQUERDA")!=0)){
					sprintf(mensagem[*j], "Linha %d: Parâmetro inválido.\n Parâmetros válidos: (1) DIREITA (2) ESQUERDA", i+1);
					(*j)++;
					comando_invalido=1;
				}
		}
	}
	
	//Retornar resultado da validação
	if(comando_invalido==0)
		return 0;
	else
		return -1;
}

//tornar executável
int analise_semantica(char (*comando)[TAM], executavel programa[]){
	int i, n, abre_parenteses, fecha_parenteses, resultado, param;
	int y = 300;//horizontal
    int x = 630;//vertical
    int estado_carro = 1;

	printf("\n INSTRUÇÕES: \n");
	
	n = retorna_tamanho_matriz(comando);
    for(i=0; i<n; i++){
    	//1. Mapeamento dos pontos de quebra
    	abre_parenteses = busca_caractere(comando[i], '(');
		fecha_parenteses = busca_caractere(comando[i], ')');

    	//2. Armazenamento e Tratamento dos Dados
		//Instrução
		forma_frase(comando[i], programa[i].instrucao, 0, abre_parenteses-1);
		converte_string_maiuscula(programa[i].instrucao);
		limpa_espacos(programa[i].instrucao);
		//Parâmetro
		forma_frase(comando[i], programa[i].parametro, abre_parenteses+1, fecha_parenteses-1);
		converte_string_maiuscula(programa[i].parametro);
		limpa_espacos(programa[i].parametro);

		//3. Execução dos Comandos
		printf("%d. ", i+1);
		resultado = busca_dicionario(programa[i].instrucao);
		switch(resultado){
			case 1:
				param = converte_p_numero(programa[i].parametro);
					if(estado_carro == 1 || estado_carro == 2){
						x = avanca(param, x, y, estado_carro);
					}
					else{
						y = avanca(param, x, y, estado_carro);
					}
				break;
			case 2:
				if(strcmp(programa[i].parametro, "DIREITA")==0){
					estado_carro = vira(1, x, y, estado_carro); 
				}
				else{
					estado_carro = vira(2, x, y, estado_carro);
				}
				break;
			case 3:
				param = converte_p_numero(programa[i].parametro);
				if(estado_carro == 1 || estado_carro == 2){
						x = retorna(param, x, y, estado_carro);
					}
					else{
						y = retorna(param, x, y, estado_carro);
					}
				break;
		}
    }

	return 0;
}


int EXECUTA_COMPILADOR(char texto[]){
	int tamanho, resultado, cont_mensagem=0, comando_valido=0;
	char mensagem[TAM][TAM], comando[TAM][TAM];
	executavel programa[TAM];

	//1. Análise Léxica	
    resultado = analise_lexica(texto, comando, mensagem[0]);
	//imprime_string(texto);

	if(resultado == -1){
		tamanho = retorna_tamanho_matriz(mensagem);
		imprime_matriz(mensagem, tamanho);
	}
	else{
		tamanho = retorna_tamanho_matriz(comando);
		imprime_matriz(comando, tamanho);
        //printf("%s\n",comando[0]);
        
		//2. Análise Sintática
        resultado = analise_sintatica(comando, mensagem, &cont_mensagem);
        if(resultado == 0){
            printf("\nComando válido! Parabéns meu!!!\n");
        	comando_valido = 1;
        }
        else{
            printf("\nErro de Compilação!\n");
            tamanho = retorna_tamanho_matriz(mensagem);
			imprime_matriz(mensagem, tamanho);
            comando_valido = 0;
        }
	}

	//3. Análise Semântica
	if(comando_valido)
		analise_semantica(comando, programa);

	return 0;
}
