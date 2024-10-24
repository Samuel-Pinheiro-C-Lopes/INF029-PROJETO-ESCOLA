#include "Aluno.h"
#include "Utils.h"


void mainAluno (Aluno **inicio_aluno, int* opcao)
{
  do 
  {
	system("clear");
    menu_Aluno(opcao);
    switch (*opcao * -1)
    {
      case (OPCAO_CADASTRAR):
      {
        printf("\nOPCAO_CADASTRAR\n");
		if (cadastrar_aluno(inicio_aluno) == CADASTRO_SUCESSO)
			printf("Cadastro realizado com sucesso!\nEntre com qualquer tecla para continuar...\n");
		getchar();
        break;   
      }
      case (OPCAO_LISTAR):
      {
        printf("\nOPCAO_LISTAR\n");
		listar_alunos(*inicio_aluno);
        break;   
      }
      case (OPCAO_REMOVER):
      {
        printf("OPCAO_REMOVER");
        break;   
      }
      case (OPCAO_ALTERAR):
      {
        printf("OPCAO_ALTERAR");
        break;   
      }
    }
  } while (*opcao != OPCAO_SAIR);
  *opcao = 1;

  system("clear");
}

void menu_Aluno (int* opcao)
{
  printf("\n###MÓDULO ALUNO###\n\n");
  printf("Opções:\n");
  printf("0 - Sair\n");
  printf("1 - Cadastrar aluno\n");
  printf("2 - Listar alunos\n");
  printf("3 - Remover aluno\n");
  printf("4 - Alterar aluno\n");
  printf("\nEntre com a opção desejada: ");
  scanf(" %d", opcao);
  getchar();
}

int inserir_lista_aluno (Aluno** inicio_aluno, Info_Aluno nova_info_aluno)
{
	Aluno* novo_aluno = (Aluno*) malloc(sizeof(Aluno));
	novo_aluno->info = nova_info_aluno;
	novo_aluno->prox = *inicio_aluno;
	*inicio_aluno = novo_aluno;

	return INSERCAO_SUCESSO;
}

int cadastrar_aluno (Aluno** inicio_aluno)
{
	Info_Aluno nova_info_aluno;

	system("clear");
	imprimir_linhas(10);
	printf("\nEntre com o nome do aluno: ");
	ler_string(nova_info_aluno.nome, 50);
	printf("\nEntre com a matricula do aluno: ");
	scanf(" %d", &nova_info_aluno.matricula);
	printf("\nEntre com o sexo do aluno [M ou F]: ");
	scanf(" %c", &nova_info_aluno.sexo);
	imprimir_linhas(10);
	system("clear");
	getchar();

	if (inserir_lista_aluno(inicio_aluno, nova_info_aluno) == INSERCAO_SUCESSO)	
		return CADASTRO_SUCESSO;
	else
		return DATA_INVALIDA;
}

int listar_alunos (Aluno* atual_aluno)
{
	if (atual_aluno == NULL)
		return LISTA_VAZIA;
	
	imprimir_linhas(10);
	imprimir_campo("Matrícula", int_para_string(atual_aluno->info.matricula));
	imprimir_campo("Nome", atual_aluno->info.nome);
	imprimir_campo("Sexo", &atual_aluno->info.sexo);
	imprimir_linhas(10);

	printf("\n");

	if (atual_aluno->prox != NULL)
		listar_alunos(atual_aluno->prox);

	return LISTAGEM_SUCESSO;
}

/* CONTINUAR
int remover_aluno_matricula (Aluno** inicio_aluno, int matricula)
{
	if (inicio_aluno == NULL)
		return LISTA_VAZIA;

	while ((*inicio_aluno)->prox->info.matricula != matricula && inicio_aluno != NULL)
		inicio_aluno = &((*inicio_aluno)->prox);

	if (inicio_aluno == NULL)
		return MATRICULA_NAO_ENCONTRADA;

	free(*((*inicio_aluno)->prox));
	*inicio_aluno 

}
CONTINUAR
*/

/*
void inserir_aluno (Aluno** inicio_aluno, Info_Aluno* nova_info_aluno);
void cadastrar_aluno (Aluno** inicio_aluno);
void remover_aluno_matricula (Aluno** inicio_aluno, int matricula);
void listar_alunos (Aluno** inicio_aluno);
void buscar_aluno_matricula (Aluno** inicio_aluno, int matricula);
*/
