#ifndef ALUNO_HEADER
#define ALUNO_HEADER

#include "Utils.h"
#include "AlunoData.h"
#include "ProfessorData.h"

void main_aluno (Aluno** inicio_aluno, Professor** inicio_professor, int* matricula_aluno_incr, int* opcao);

void menu_Aluno (int* opcao);

int inserir_aluno (Aluno** inicio_aluno, Info_Aluno nova_info_aluno);
int cadastrar_aluno (Aluno** inicio_aluno, Professor** inicio_professor, int* matricula_aluno_incr);
int remover_aluno_matricula (Aluno** inicio_aluno, int matricula);
void listar_alunos (Aluno* inicio_aluno);
void buscar_aluno_matricula (Aluno* atual_aluno, Aluno** aluno_alvo, int matricula);
int alterar_aluno_matricula(Aluno** inicio_aluno, int matricula);
void mostrar_aluno(Aluno* aluno_alvo);
int validar_info_aluno(Aluno** inicio_aluno, Professor** inicio_professor, Info_Aluno nova_info_aluno);

#endif
