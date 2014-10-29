/*Criando uma biblioteca de funções de compilador para o Projeto Integrador II - Programming Driver*/

#ifndef COMPILADOR_PD_H
#define COMPILADOR_PD_H
#define TAMANHO 200

//--------------------- CAIXA DE TEXTO -------------------------------------------
int esta_vazia(char (*matriz)[TAMANHO]);
int ultima_linha(char (*matriz)[TAMANHO]);
void concatena_strings(char (*matriz)[TAMANHO], char conjunto_string[], int n);

//--------------------- COMPILADOR -----------------------------------------------
int EXECUTA_COMPILADOR(char []);
void imprime_string(char frase[]);

//--------------------- FUNÇÕES ANALÍTICAS DO COMPILADOR -------------------------------------------
int avanca(int, int, int, int);
int vira(int, int, int, int);
int retorna(int, int, int, int);

#endif
