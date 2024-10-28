#include "Utils.h"

typedef struct info_aluno Info_Aluno;
typedef struct aluno Aluno;

struct info_aluno
{
  int matricula;
  char nome[50];
  char sexo[2];
  char data_nascimento[11];
  char cpf[15];
};

struct aluno 
{
  Info_Aluno info;
  Aluno* prox;
  Aluno* ant;
};

void main_aluno (Aluno** inicio_aluno, int* opcao);
void menu_Aluno (int* opcao);
int inserir_aluno (Aluno** inicio_aluno, Info_Aluno nova_info_aluno);
int cadastrar_aluno (Aluno** inicio_aluno, int* matricula_aluno_incr);
int remover_aluno_matricula (Aluno** inicio_aluno, int matricula);
void listar_alunos (Aluno* inicio_aluno);
void buscar_aluno_matricula (Aluno* inicio_aluno, Aluno** aluno_alvo, int matricula);
