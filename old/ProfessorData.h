#ifndef PROFESSOR_DATA_HEADER
#define PROFESSOR_DATA_HEADER

typedef struct info_professor Info_Professor;
typedef struct professor Professor;

struct info_professor
{
  int matricula;
  char nome[50];
  char sexo[2];
  char data_nascimento[11];
  char cpf[15];
};

struct professor 
{
  Info_Professor info;
  Professor* prox;
  Professor* ant;
};

void verificar_professores_cpf(Professor* atual_professor, int* tem_cpf, char* cpf);
#endif
