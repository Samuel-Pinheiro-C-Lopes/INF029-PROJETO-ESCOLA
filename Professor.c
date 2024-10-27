#include "Professor.h"
#include "Utils.h"


void mainProfessor (Professor **inicio_professor, int* opcao)
{
	int mat;
	do 
	{
		system("clear");
		menu_Professor(opcao);
		switch (*opcao * -1)
		{
			case (OPCAO_CADASTRAR):
			{
				switch (cadastrar_professor(inicio_professor))
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
				if (*inicio_professor == NULL)
				{
					aviso_usuario("NÃO HÁ PROFESSORS MATRICULADOS NO MOMENTO");
					break;
				}
				else 
				{
					listar_professores(*inicio_professor);
					aviso_usuario("LISTAGEM REALIZADA COM SUCESSO!");
				}
				break;   
			}
			case (OPCAO_REMOVER):
			{
 				receber_matricula(&mat);
				switch (remover_professor_matricula(inicio_professor, mat))
				{
					case (REMOCAO_SUCESSO):
					{
						aviso_usuario("REMOÇÃO SUCESSO");
						break;
					}
					case (LISTA_VAZIA):
					{
						aviso_usuario("ATUALMENTE NÃO HÁ PROFESSORS PARA REMOVER");
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

void menu_Professor (int* opcao)
{
	printf("###MÓDULO PROFESSOR###\n\n");
	printf("Opções:\n");
	printf("0 - Sair\n");
	printf("1 - Cadastrar professor\n");
	printf("2 - Listar professors\n");
	printf("3 - Remover professor\n");
	printf("4 - Alterar professor\n");
	printf("\nEntre com a opção desejada: ");
	scanf(" %d", opcao);
	limpar();
}

int inserir_professor (Professor** inicio_professor, Info_Professor nova_info_professor)
{
	Professor* novo_professor = (Professor*) malloc(sizeof(Professor));

	if (*inicio_professor != NULL)
		(*inicio_professor)->ant = novo_professor;

	novo_professor->info = nova_info_professor;
	novo_professor->prox = *inicio_professor;
	novo_professor->ant = NULL;

	*inicio_professor = novo_professor;

	return INSERCAO_SUCESSO;
}

int cadastrar_professor (Professor** inicio_professor)
{
	Info_Professor nova_info_professor;

	imprimir_linhas(NUM_LINHAS);
	printf("\nEntre com o nome do professor: ");
	ler_string(nova_info_professor.nome, 50);
	printf("\nEntre com a matricula do professor: ");
	scanf(" %d", &nova_info_professor.matricula);
	printf("\nEntre com o sexo do professor [M ou F]: ");
	scanf(" %c", &nova_info_professor.sexo);
	imprimir_linhas(NUM_LINHAS);

	if (inserir_professor (inicio_professor, nova_info_professor) == INSERCAO_SUCESSO)	
		return CADASTRO_SUCESSO;
	else
		return DATA_INVALIDA;
}

void listar_professores (Professor* atual_professor)
{
	if (atual_professor == NULL)
		return;

	imprimir_linhas(NUM_LINHAS);
	imprimir_campo("Matrícula", int_para_string(atual_professor->info.matricula));
	imprimir_campo("Nome", atual_professor->info.nome);
	imprimir_campo("Sexo", &atual_professor->info.sexo);
	imprimir_linhas(NUM_LINHAS);

	printf("\n");

	listar_professores(atual_professor->prox);
}

int remover_professor_matricula (Professor** inicio_professor, int matricula)
{
	if (inicio_professor == NULL)
		return LISTA_VAZIA;
		
	Professor* professor_alvo = buscar_professor_matricula((*inicio_professor), matricula);

	if (professor_alvo == NULL)
		return MATRICULA_NAO_ENCONTRADA;

	if (professor_alvo->ant != NULL)
		professor_alvo->ant->prox = professor_alvo->prox;
	else
		(*inicio_professor) = professor_alvo->prox;

	if (professor_alvo->prox != NULL)
		professor_alvo->prox->ant = professor_alvo->ant; 

	free(professor_alvo);

	return REMOCAO_SUCESSO;
}

Professor* buscar_professor_matricula (Professor* atual_professor, int matricula)
{
	if (atual_professor == NULL)
		return NULL;

	if (atual_professor->info.matricula == matricula)
		return atual_professor;

	buscar_professor_matricula(atual_professor->prox, matricula);

	return NULL;
}

