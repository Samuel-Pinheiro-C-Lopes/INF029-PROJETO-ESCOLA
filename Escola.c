#include "Utils.h"
#include "Disciplina.h"
#include "Escola.h"

// projeto escola true

int main (void)
{	
    Aluno* inicio_aluno = NULL;
	Professor* inicio_professor = NULL;
	Disciplina* inicio_disciplina = NULL;
    int opcao;
    do {
		system("clear");
        menu_main(&opcao);
        switch (opcao * -1)
        {
          case (OPCAO_MODULO_ALUNO):
          {
            main_aluno(&inicio_aluno, &opcao);
            break;   
          }
          case (OPCAO_MODULO_PROFESSOR):
          {
			main_professor(&inicio_professor, &opcao);
			break;
          }
          case (OPCAO_MODULO_DISCIPLINAS):
          {
			main_disciplina(&inicio_disciplina, &inicio_aluno, &inicio_professor, &opcao);
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
	char str[2];
	*opcao = 0;
	printf("###PROJETO ESCOLA###\n\n");
	printf("Opções:\n");
	printf("0 - Sair\n");
	printf("1 - Módulo Aluno\n");
	printf("2 - Módulo Professor\n");
	printf("3 - Módulo Disciplinas\n");
	printf("\nEntre com a opção desejada: ");
	ler_string(str, sizeof(str));
	*opcao = str[0] - 48;
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
