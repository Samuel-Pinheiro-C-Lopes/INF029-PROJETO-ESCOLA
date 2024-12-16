#ifndef ESCOLA_HEADER
#define ESCOLA_HEADER

#include "Utils.h"

// Definições de opções para menu
#define OPCAO_MODULO_ALUNO (-1)
#define OPCAO_MODULO_PROFESSOR (-2)
#define OPCAO_MODULO_DISCIPLINAS (-3)
#define OPCAO_SAIR (0)

void menu_main (int* opcao);

void liberar_alunos (Aluno* aluno_atual);
void liberar_professores (Professor* professor_atual);
void liberar_disciplinas (Disciplina* disciplina_atual);

#endif
