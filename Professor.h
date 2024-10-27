#include "Utils.h"

// Definições de opções para menu
#define OPCAO_CADASTRAR (-1)
#define OPCAO_LISTAR (-2)
#define OPCAO_REMOVER (-3)
#define OPCAO_ALTERAR (-4)
#define OPCAO_SAIR (0)

typedef struct info_professor Info_Professor;
typedef struct professor Professor;

struct info_professor
{
  int matricula;
  char nome[50];
  char sexo;
  char data_nascimento[11];
  char cpf[15];
};

struct professor 
{
  Info_Professor info;
  Professor* prox;
  Professor* ant;
};

void mainProfessor (Professor** inicio_professor, int* opcao);
void menu_Professor (int* opcao);
int inserir_professor (Professor** inicio_professor, Info_Professor nova_info_professor);
int cadastrar_professor (Professor** inicio_professor);
int remover_professor_matricula (Professor** inicio_professor, int matricula);
void listar_professores (Professor* inicio_professor);
Professor* buscar_professor_matricula (Professor* inicio_professor, int matricula);
