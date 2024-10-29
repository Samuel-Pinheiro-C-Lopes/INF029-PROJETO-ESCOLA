#ifndef PROFESSOR_HEADER
#define PROFESSOR_HEADER

#include "Utils.h"
#include "AlunoData.h"
#include "ProfessorData.h"

void main_professor (Professor** inicio_professor, Aluno** inicio_aluno, int* matricula_professor_incr, int* opcao);

void menu_Professor (int* opcao);

int inserir_professor (Professor** inicio_professor, Info_Professor nova_info_professor);
int cadastrar_professor (Professor** inicio_professor, Aluno** inicio_aluno, int* matricula_professor_incr);
int remover_professor_matricula (Professor** inicio_professor, int matricula);
void listar_professores (Professor* inicio_professor);
void buscar_professor_matricula (Professor* inicio_professor, Professor** professor_alvo, int matricula);
int alterar_professor_matricula (Professor** inicio_professor, int matricula);
void mostrar_professor (Professor* professor_alvo);
int validar_info_professor(Professor** inicio_professor, Aluno** inicio_aluno, Info_Professor nova_info_professor);

#endif
