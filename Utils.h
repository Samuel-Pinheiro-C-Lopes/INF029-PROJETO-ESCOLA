// importações
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Definições erro de busca
#define MATRICULA_NAO_ENCONTRADA (-11)
#define LISTA_VAZIA (-12)

// Definições sucesso de busca
#define LISTAGEM_SUCESSO (-21)

// Definições erro de cadastro
#define DISCIPLINA_JA_EXISTE (-30)
#define CPF_INVALIDO (-31)
#define DATA_INVALIDA (-32)

// Definições de sucesso de cadastro
#define CADASTRO_SUCESSO (-40)
#define ALUNO_VALIDO (-41)
#define CPF_VALIDO (-42)
#define DATA_VALIDA (-43)

// Definições de sucesso de inserção
#define INSERCAO_SUCESSO (-60)

// Definições de erro de miscelâneos
#define CHAR_NAO_NUMERO (-70)

// Definições de sucesso de miscelâneos
#define CHAR_NUMERO (-80)

void qnt_algarismos_int (int* qnt, int num);
char* int_para_string (int num);
void string_para_int (int* num, char* string);
void multiplicacao_sucessiva (int* num, int pot, int count);
void ler_string(char* string, int tam);
void imprimir_linhas(int num);
void imprimir_campo(char* campo, char* valor);
