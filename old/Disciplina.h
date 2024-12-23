#ifndef DISCIPLINA_HEADER
#define DISCIPLINA_HEADER
// GUARD

#include "Utils.h"
#include "Professor.h"
#include "Aluno.h"
#include "DisciplinaData.h"

// Definições de opções para menu
#define DETALHAR_DISCIPLINA (-5)

void main_disciplina (Disciplina** inicio_disciplina, Aluno** inicio_aluno, Professor** inicio_professor, int* codigo_disciplina_incr, int* opcao);

void menu_disciplina (int* opcao);
void menu_alterar (int* opcao);

void inserir_disciplina (Disciplina** inicio_disciplina, Info_Disciplina nova_info_disciplina);
void inserir_disciplina_aluno (Disciplina* disciplina, Aluno* aluno);

int cadastrar_disciplina (Disciplina** inicio_disciplina, Professor** inicio_professor, int* codigo_disciplina_incr);
int cadastrar_disciplina_aluno (Disciplina** inicio_disciplina, Aluno** inicio_aluno);

void listar_disciplinas (Disciplina* atual_disciplina);
void listar_disciplina_alunos (Disciplina_Aluno* atual_disciplina_aluno);
void mostrar_disciplina (Disciplina* disciplina_alvo);

int detalhar_disciplina (Disciplina* disciplina_alvo);

int remover_disciplina_codigo (Disciplina** inicio_disciplina, int codigo);
int remover_disciplina_aluno_matricula (Disciplina* disciplina, int matricula);

int alterar_disciplina_matricula (Disciplina** inicio_disciplina, Professor** inicio_professor, int codigo);
int mudar_disciplina_professor(Disciplina* disciplina_alvo, Professor** inicio_professor, int* opcao);

void buscar_disciplina_codigo (Disciplina* atual_disciplina, Disciplina** disciplina_alvo, int codigo);
void buscar_disciplina_aluno_matricula (Disciplina_Aluno* atual_disciplina_aluno, Disciplina_Aluno** disciplina_aluno_alvo, int matricula);

int validar_info_disciplina(Info_Disciplina* info_disciplina);

void atualizar_disciplinas_alunos (Disciplina** inicio_disciplina, Aluno** inicio_aluno);

void listar_disciplinas_extr (char sinal, Disciplina** inicio_disciplina);
#endif
