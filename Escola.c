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
        menu_Main(&opcao);
        switch (opcao * -1)
        {
          case (OPCAO_MODULO_ALUNO):
          {
            mainAluno(&inicio_aluno, &opcao);
            break;   
          }
          case (OPCAO_MODULO_PROFESSOR):
          {
			mainProfessor(&inicio_professor, &opcao);
			break;
          }
          case (OPCAO_MODULO_DISCIPLINAS):
          {
			mainDisciplina(&inicio_disciplina, &inicio_aluno, &inicio_professor, &opcao);
            break;   
          }
        }
    } while (opcao != OPCAO_SAIR);

	system("clear");

    return 1;
}

void menu_Main (int* opcao)
{
	printf("###PROJETO ESCOLA###\n\n");
	printf("Opções:\n");
	printf("0 - Sair\n");
	printf("1 - Módulo Aluno\n");
	printf("2 - Módulo Professor\n");
	printf("3 - Módulo Disciplinas\n");
	printf("\nEntre com a opção desejada: ");
	scanf(" %d", opcao);
	limpar();
}
