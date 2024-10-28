#include "Utils.h"

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

void main_professor (Professor** inicio_professor, int* opcao);
void menu_Professor (int* opcao);
int inserir_professor (Professor** inicio_professor, Info_Professor nova_info_professor);
int cadastrar_professor (Professor** inicio_professor);
int remover_professor_matricula (Professor** inicio_professor, int matricula);
void listar_professores (Professor* inicio_professor);
void buscar_professor_matricula (Professor* inicio_professor, Professor** professor_alvo, int matricula);
