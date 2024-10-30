#ifndef ALUNO_HEADER
#define ALUNO_HEADER

#include "Utils.h"
#include "AlunoData.h"
#include "ProfessorData.h"
#include "DisciplinaData.h"

void main_aluno (Aluno** inicio_aluno, Professor** inicio_professor, Disciplina** inicio_disciplina, int* matricula_aluno_incr, int* opcao);

void menu_Aluno (int* opcao);

int inserir_aluno (Aluno** inicio_aluno, Info_Aluno nova_info_aluno);
int cadastrar_aluno (Aluno** inicio_aluno, Professor** inicio_professor, int* matricula_aluno_incr);
int remover_aluno_matricula (Aluno** inicio_aluno, Disciplina** inicio_disciplina, int matricula);
void listar_alunos (Aluno* inicio_aluno);
void buscar_aluno_matricula (Aluno* atual_aluno, Aluno** aluno_alvo, int matricula);
int alterar_aluno_matricula(Aluno** inicio_aluno, int matricula);
void mostrar_aluno(Aluno* aluno_alvo);
int validar_info_aluno(Aluno** inicio_aluno, Professor** inicio_professor, Info_Aluno nova_info_aluno);
void quantidade_aluno_lista (Aluno* atual_aluno, int* qnt);
void aluno_listar_por_sexo (Aluno* inicio_aluno);
void aluno_listar_por_data (Aluno** inicio_aluno);
void aluno_listar_por_substring (Aluno** inicio_aluno);
void aluno_ordenar_por_nomes (Aluno** inicio_aluno);
void aluno_listar_aniversariantes (Aluno** inicio_aluno);
void remover_disciplina_aluno (Aluno* inicio_aluno, Disciplina** inicio_disciplina);

#endif
