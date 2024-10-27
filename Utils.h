// importações
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Definições erro falha ou incongruência
#define MATRICULA_NAO_ENCONTRADA (-11)
#define CODIGO_NAO_ENCONTRADO (-12)
#define LISTA_VAZIA (-13)

// Definições de invalidade
#define CPF_INVALIDO (-31)
#define DATA_INVALIDA (-32)
#define NUMERO_INVALIDO (-33)
#define CHAR_INVALIDO (-34)

// Definições de validade
#define ALUNO_VALIDO (-41)
#define DISCIPLINA_VALIDA (-42)
#define PROFESSOR_VALIDO (-43)
#define CPF_VALIDO (-44)
#define DATA_VALIDA (-45)
#define CHAR_VALIDO (-46)

// Definições de sucesso
#define REMOCAO_SUCESSO (-65)
#define CADASTRO_SUCESSO (-66)
#define INSERCAO_SUCESSO (-67)
#define LISTAGEM_SUCESSO (-68)

// Definições de fracasso
#define CADASTRO_FRACASSO (-70)

// Número de linhas para a função "imprimir_linhas"
#define NUM_LINHAS (20)

void qnt_algarismos_int (int* qnt, int num);
char* int_para_string (int num);
void string_para_int (int* num, char* string);
void multiplicacao_sucessiva (int* num, int pot, int count);
void ler_string(char* string, int tam);
void imprimir_linhas(int num);
void imprimir_campo(char* campo, char* valor);
void aviso_usuario(char* string);
void receber_matricula(int* mat);
void limpar (void);
