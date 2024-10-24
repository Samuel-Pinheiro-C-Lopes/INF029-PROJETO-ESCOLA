#include "Utils.h"

// Definições de opções para menu
#define OPCAO_CADASTRAR (-1)
#define OPCAO_LISTAR (-2)
#define OPCAO_REMOVER (-3)
#define OPCAO_ALTERAR (-4)
#define OPCAO_SAIR (0)

typedef struct info_aluno Info_Aluno;
typedef struct aluno Aluno;

struct info_aluno
{
  int matricula;
  char nome[50];
  char sexo;
  char data_nascimento[11];
  char cpf[15];
};

struct aluno 
{
  Info_Aluno info;
  Aluno* prox;
};

void mainAluno (Aluno** inicio_aluno, int* opcao);
void menu_Aluno (int* opcao);
int inserir_aluno (Aluno** inicio_aluno, Info_Aluno* nova_info_aluno);
int cadastrar_aluno (Aluno** inicio_aluno);
int remover_aluno_matricula (Aluno** inicio_aluno, int matricula);
int listar_alunos (Aluno* inicio_aluno);
int buscar_aluno_matricula (Aluno** inicio_aluno, int matricula);

