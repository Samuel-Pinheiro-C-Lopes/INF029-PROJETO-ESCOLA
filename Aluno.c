#include "Aluno.h"
#include "Utils.h"


void mainAluno (Aluno **inicio_aluno, int* opcao)
{
	int mat;
	do 
	{
		system("clear");
		menu_Aluno(opcao);
		switch (*opcao * -1)
		{
			case (OPCAO_CADASTRAR):
			{
				switch (cadastrar_aluno(inicio_aluno))
				{
					case (CADASTRO_SUCESSO):
					{
						limpar();
						aviso_usuario("CADASTRO REALIZADO COM SUCESSO!");
						break;
					}
					case (DATA_INVALIDA):
					{
						aviso_usuario("CADASTRO NÃO REALIZADO");
						break;
					}
				}
			break;   
			}
			case (OPCAO_LISTAR):
			{
				if (*inicio_aluno == NULL)
				{
					aviso_usuario("NÃO HÁ ALUNOS MATRICULADOS NO MOMENTO");
					break;
				}
				else 
				{
					listar_alunos(*inicio_aluno);
					aviso_usuario("LISTAGEM REALIZADA COM SUCESSO!");
				}
				break;   
			}
			case (OPCAO_REMOVER):
			{
 				receber_matricula(&mat);
				switch (remover_aluno_matricula(inicio_aluno, mat))
				{
					case (REMOCAO_SUCESSO):
					{
						aviso_usuario("REMOÇÃO SUCESSO");
						break;
					}
					case (LISTA_VAZIA):
					{
						aviso_usuario("ATUALMENTE NÃO HÁ ALUNOS PARA REMOVER");
						break;
					}
					case (MATRICULA_NAO_ENCONTRADA):
					{
						aviso_usuario("A MATRICULA INSERIDA NÃO FOI ENCONTRADA");
						break;
					}
				}
				break;
			}
			case (OPCAO_ALTERAR):
			{
				limpar();
				break;   
			}
		}
	} while (*opcao != OPCAO_SAIR);
	*opcao = 1;
}

void menu_Aluno (int* opcao)
{
	printf("###MÓDULO ALUNO###\n\n");
	printf("Opções:\n");
	printf("0 - Sair\n");
	printf("1 - Cadastrar aluno\n");
	printf("2 - Listar alunos\n");
	printf("3 - Remover aluno\n");
	printf("4 - Alterar aluno\n");
	printf("\nEntre com a opção desejada: ");
	scanf(" %d", opcao);
	limpar();
}

int inserir_aluno (Aluno** inicio_aluno, Info_Aluno nova_info_aluno)
{
	Aluno* novo_aluno = (Aluno*) malloc(sizeof(Aluno));

	if (*inicio_aluno != NULL)
		(*inicio_aluno)->ant = novo_aluno;

	novo_aluno->info = nova_info_aluno;
	novo_aluno->prox = *inicio_aluno;
	novo_aluno->ant = NULL;

	*inicio_aluno = novo_aluno;

	return INSERCAO_SUCESSO;
}

int cadastrar_aluno (Aluno** inicio_aluno)
{
	Info_Aluno nova_info_aluno;

	imprimir_linhas(NUM_LINHAS);
	printf("\nEntre com o nome do aluno: ");
	ler_string(nova_info_aluno.nome, 50);
	printf("\nEntre com a matricula do aluno: ");
	scanf(" %d", &nova_info_aluno.matricula);
	printf("\nEntre com o sexo do aluno [M ou F]: ");
	scanf(" %c", &nova_info_aluno.sexo);
	imprimir_linhas(NUM_LINHAS);

	if (inserir_aluno (inicio_aluno, nova_info_aluno) == INSERCAO_SUCESSO)	
		return CADASTRO_SUCESSO;
	else
		return DATA_INVALIDA;
}

void listar_alunos (Aluno* atual_aluno)
{
	if (atual_aluno == NULL)
		return;

	imprimir_linhas(NUM_LINHAS);
	imprimir_campo("Matrícula", int_para_string(atual_aluno->info.matricula));
	imprimir_campo("Nome", atual_aluno->info.nome);
	imprimir_campo("Sexo", &atual_aluno->info.sexo);
	imprimir_linhas(NUM_LINHAS);

	printf("\n");

	listar_alunos(atual_aluno->prox);
}

int remover_aluno_matricula (Aluno** inicio_aluno, int matricula)
{
	if (inicio_aluno == NULL)
		return LISTA_VAZIA;
		
	Aluno* aluno_alvo = buscar_aluno_matricula((*inicio_aluno), matricula);

	if (aluno_alvo == NULL)
		return MATRICULA_NAO_ENCONTRADA;

	if (aluno_alvo->ant != NULL)
		aluno_alvo->ant->prox = aluno_alvo->prox;
	else
		(*inicio_aluno) = aluno_alvo->prox;

	if (aluno_alvo->prox != NULL)
		aluno_alvo->prox->ant = aluno_alvo->ant; 

	free(aluno_alvo);

	return REMOCAO_SUCESSO;
}

Aluno* buscar_aluno_matricula (Aluno* atual_aluno, int matricula)
{
	if (atual_aluno == NULL)
		return NULL;

	if (atual_aluno->info.matricula == matricula)
		return atual_aluno;

	buscar_aluno_matricula(atual_aluno->prox, matricula);

	return NULL;
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
