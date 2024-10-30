#include "Utils.h"
#include "Disciplina.h"
#include "Aluno.h"
#include "Professor.h"
#include "Escola.h"

// projeto escola true

int main (void)
{	
    Aluno* inicio_aluno = NULL;
	Professor* inicio_professor = NULL;
	Disciplina* inicio_disciplina = NULL;

	int* matricula_aluno_incr = NULL; inicializar_incrementador (&matricula_aluno_incr);
	int* matricula_professor_incr = NULL; inicializar_incrementador (&matricula_professor_incr);
	int* codigo_disciplina_incr = NULL; inicializar_incrementador (&codigo_disciplina_incr);

    int opcao;

    do {
        menu_main(&opcao);

        switch (opcao * -1)
        {
          case (OPCAO_MODULO_ALUNO):
          {
            main_aluno(&inicio_aluno, &inicio_professor, &inicio_disciplina, matricula_aluno_incr, &opcao);
            break;   
          }
          case (OPCAO_MODULO_PROFESSOR):
          {
			main_professor(&inicio_professor, &inicio_aluno, matricula_professor_incr, &opcao);
			break;
          }
          case (OPCAO_MODULO_DISCIPLINAS):
          {
			main_disciplina(&inicio_disciplina, &inicio_aluno, &inicio_professor, codigo_disciplina_incr, &opcao);
            break;   
          }
        }
    } while (opcao != OPCAO_SAIR);

	system("clear");

	liberar_alunos(inicio_aluno);
	liberar_professores(inicio_professor);
	liberar_disciplinas(inicio_disciplina);

    return 1;
}

void menu_main (int* opcao)
{
	system("clear");
	printf("###PROJETO ESCOLA###\n\n");
	printf("Opções:\n");
	printf("0 - Sair\n");
	printf("1 - Módulo Aluno\n");
	printf("2 - Módulo Professor\n");
	printf("3 - Módulo Disciplinas\n");
	printf("\nEntre com a opção desejada: ");
	ext_ler_int_f(opcao, CASAS_INT_MENU);
}

void liberar_alunos (Aluno* aluno_atual)
{
	if (aluno_atual == NULL)
		return;

	liberar_alunos (aluno_atual->prox);

	free(aluno_atual);
}

void liberar_professores (Professor* professor_atual)
{
	if (professor_atual == NULL)
		return;

	liberar_professores (professor_atual->prox);

	free(professor_atual);
}

void liberar_disciplinas (Disciplina* disciplina_atual)
{
	if (disciplina_atual == NULL)
		return;

	liberar_disciplinas (disciplina_atual->prox);

	free(disciplina_atual);
}
