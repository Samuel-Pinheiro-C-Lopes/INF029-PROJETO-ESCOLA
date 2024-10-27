#include "Utils.h"
#include "Professor.h"
#include "Aluno.h"

// Definições de opções para menu
#define OPCAO_CADASTRAR (-1)
#define OPCAO_LISTAR (-2)
#define OPCAO_REMOVER (-3)
#define OPCAO_ALTERAR (-4)
#define CADASTRAR_DISCIPLINA_ALUNO (-5)
#define DETALHAR_DISCIPLINA (-6)
#define OPCAO_SAIR (0)

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

void mainDisciplina (Disciplina** inicio_disciplina, Aluno** inicio_aluno, Professor** inicio_professor, int* opcao);
void menu_Disciplina (int* opcao);
void inserir_disciplina (Disciplina** inicio_disciplina, Info_Disciplina nova_info_disciplina);
int cadastrar_disciplina (Disciplina** inicio_disciplina, Professor** inicio_professor);
int remover_disciplina_codigo (Disciplina** inicio_disciplina, int codigo);
void listar_disciplinas (Disciplina* inicio_disciplina);
Disciplina* buscar_disciplina_codigo (Disciplina* inicio_disciplina, int codigo);
void receber_codigo (int* cod);
int validar_info_disciplina(Info_Disciplina* info_disciplina);
void inserir_disciplina_aluno (Disciplina* disciplina, Aluno* aluno);
int cadastrar_disciplina_aluno (Disciplina** inicio_disciplina, Aluno** inicio_aluno);
