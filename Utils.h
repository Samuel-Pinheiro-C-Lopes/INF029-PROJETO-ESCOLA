#ifndef UTILS_HEADER
#define UTILS_HEADER
// GUARD

// importações
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Definições de opções para menu
#define OPCAO_CADASTRAR (-1)
#define OPCAO_ALTERAR (-2)
#define OPCAO_REMOVER (-3)
#define OPCAO_LISTAR (-4)
#define OPCAO_SAIR (0)

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
#define ALTERACAO_SUCESSO (-69)

// Definições de fracasso
#define CADASTRO_FRACASSO (-70)

// Número de linhas para a função "imprimir_linhas"
#define NUM_LINHAS (20)
#define CASAS_INT_MENU (2)
#define CASAS_INT_GERAL (5)

// Macros
#define CHAR_NUMERO (CHAR) ((CHAR >= 48) && (CHAR <= 57))

void qnt_algarismos_int (int* qnt, int num);
char* int_para_string (int num);
void string_para_int (int* num, char* string);
void multiplicacao_sucessiva (int* num, int pot, int count);
void ler_string(char* string, int tam);
void ler_string_f(char* string, int tam);
void ler_int(int* int_num, int casas);
void ler_int_f(int* int_num, int casas);
void ext_ler_int_f(int* int_num, int casas);
void imprimir_linhas(int num);
void imprimir_campo(char* campo, char* valor);
void mudar_campo_str(char* campo, char* mensagem, int tamanho_campo, int* opcao);
void mudar_campo_int(int* campo, char* mensagem, int casas_campo, int* opcao);
void aviso_usuario_c(char* string);
void aviso_usuario_l(char* string);
void receber_matricula(int* mat);
void limpar (void);
void flush_stdin();
void receber_string(char* string, int tam);
void receber_codigo (int* cod);
void novo_identificador(int* novo, int* incrementador);
void inicializar_incrementador (int** incrementador);

#endif
