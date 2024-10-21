// importações
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições erro de busca
#define MATRICULA_NAO_ENCONTRADA (-11)
#define LISTA_VAZIA (-12)

// Definições erro de cadastro
#define DISCIPLINA_JA_EXISTE (-20)
#define CPF_INVALIDO (-21)
#define DATA_INVALIDA (-22)

// Definições de sucesso de cadastro
#define CADASTRO_SUCESSO (-30)
#define ALUNO_VALIDO (-31)
#define CPF_VALIDO (-32)
#define DATA_VALIDA (-33)

// Definições de erro de miscelâneos
#define CHAR_NAO_NUMERO (-70)

// Definições de sucesso de miscelâneos
#define CHAR_NUMERO (-80)

void qnt_algarismos_int (int* qnt, int num);
char* int_para_string (int num);
void string_para_int (int* num, char* string);
void multiplicacao_sucessiva (int* num, int pot, int count);
void ler_string(char* string, int tam);
