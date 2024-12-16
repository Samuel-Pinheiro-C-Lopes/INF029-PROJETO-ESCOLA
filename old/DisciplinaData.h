#ifndef DISCIPLINA_DATA_HEADER
#define DISCIPLINA_DATA_HEADER

typedef struct info_disciplina Info_Disciplina;
typedef struct disciplina Disciplina;
typedef struct disciplina_aluno Disciplina_Aluno;

struct info_disciplina
{
  int codigo;
  char nome[50];
  int semestre;
  Professor* professor;
  Disciplina_Aluno* disciplina_aluno;
};

struct disciplina 
{
  Info_Disciplina info;
  Disciplina* prox;
  Disciplina* ant;
};

struct disciplina_aluno 
{
	Aluno* aluno;
	Disciplina_Aluno* prox;
	Disciplina_Aluno* ant;
};

#endif
