#include "Utils.h"
#include "Professor.h"
#include "Aluno.h"

// Definições de opções para menu
#define DETALHAR_DISCIPLINA (-5)

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

void main_disciplina (Disciplina** inicio_disciplina, Aluno** inicio_aluno, Professor** inicio_professor, int* opcao);

void menu_disciplina (int* opcao);
void menu_alterar (int* opcao);

void receber_codigo (int* codigo);

void inserir_disciplina (Disciplina** inicio_disciplina, Info_Disciplina nova_info_disciplina);
void inserir_disciplina_aluno (Disciplina* disciplina, Aluno* aluno);

int cadastrar_disciplina (Disciplina** inicio_disciplina, Professor** inicio_professor);
int cadastrar_disciplina_aluno (Disciplina** inicio_disciplina, Aluno** inicio_aluno);

void listar_disciplinas (Disciplina* atual_disciplina);
void listar_disciplina_alunos (Disciplina_Aluno* atual_disciplina_aluno);

int detalhar_disciplina (Disciplina* disciplina_alvo);

int remover_disciplina_codigo (Disciplina** inicio_disciplina, int codigo);
int remover_disciplina_aluno_matricula (Disciplina* disciplina, int matricula);

void buscar_disciplina_codigo (Disciplina* atual_disciplina, Disciplina** disciplina_alvo, int codigo);
void buscar_disciplina_aluno_matricula (Disciplina_Aluno* atual_disciplina_aluno, Disciplina_Aluno** disciplina_aluno_alvo, int matricula);

int validar_info_disciplina(Info_Disciplina* info_disciplina);

