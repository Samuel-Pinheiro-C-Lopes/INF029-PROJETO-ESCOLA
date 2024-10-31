#ifndef PROFESSOR_HEADER
#define PROFESSOR_HEADER

#include "Utils.h"
#include "AlunoData.h"
#include "ProfessorData.h"
#include "DisciplinaData.h"

void main_professor (Professor** inicio_professor, Aluno** inicio_aluno, Disciplina** inicio_disciplina, int* matricula_professor_incr, int* opcao);

void menu_Professor (int* opcao);

int inserir_professor (Professor** inicio_professor, Info_Professor nova_info_professor);
int cadastrar_professor (Professor** inicio_professor, Aluno** inicio_aluno, int* matricula_professor_incr);
int remover_professor_matricula (Professor** inicio_professor, Disciplina** inicio_disciplina, int matricula);
void listar_professores (Professor* inicio_professor);
void buscar_professor_matricula (Professor* inicio_professor, Professor** professor_alvo, int matricula);
int alterar_professor_matricula (Professor** inicio_professor, int matricula);
void mostrar_professor (Professor* professor_alvo);
int validar_info_professor(Professor** inicio_professor, Aluno** inicio_aluno, Info_Professor nova_info_professor);
void professor_listar_por_sexo (Professor* inicio_professor);
void professor_listar_por_data (Professor** inicio_professor);
void professor_listar_por_substring (Professor** inicio_professor);
void professor_ordenar_por_nomes (Professor** inicio_professor);
void professor_listar_aniversariantes (Professor** inicio_professor);
void remover_disciplina_professor_matricula (int matricula, Disciplina* atual_disciplina);

#endif
