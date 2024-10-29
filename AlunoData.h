#ifndef ALUNO_DATA_HEADER
#define ALUNO_DATA_HEADER

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

void verificar_alunos_cpf (Aluno* aluno_atual, int* tem_cpf, char* cpf);

#endif
