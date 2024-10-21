#include "Utils.h"

// Definições de opções para menu
#define OPCAO_CADASTRAR (-1)
#define OPCAO_LISTAR (-2)
#define OPCAO_REMOVER (-3)
#define OPCAO_ALTERAR (-4)
#define OPCAO_SAIR (0)

typedef struct aluno Aluno;
typedef struct lst_Aluno Lst_Aluno;

struct aluno
{
  int matricula;
  char nome[50];
  char sexo;
  char data_nascimento[11];
  char cpf[15];
};

struct lst_Aluno 
{
  Aluno aluno;
  Lst_Aluno *prox;
};

void mainAluno (Lst_Aluno **inicio_aluno, int* opcao);
void menu_Aluno (int* opcao);
