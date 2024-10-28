#include "Aluno.h"
#include "Utils.h"


void main_aluno (Aluno **inicio_aluno, int* matricula_aluno_incr, int* opcao)
{
	int mat;
	do 
	{
		menu_Aluno(opcao);
		system("clear");
		switch (*opcao * -1)
		{
			case (OPCAO_CADASTRAR):
			{
				switch (cadastrar_aluno(inicio_aluno, matricula_aluno_incr))
				{
					case (CADASTRO_SUCESSO):
					{
						aviso_usuario_c("CADASTRO REALIZADO COM SUCESSO!");
						break;
					}
					case (DATA_INVALIDA):
					{
						aviso_usuario_c("CADASTRO NÃO REALIZADO");
						break;
					}
				}
			break;   
			}
			case (OPCAO_LISTAR):
			{
				if (*inicio_aluno == NULL)
				{
					aviso_usuario_c("NÃO HÁ ALUNOS MATRICULADOS NO MOMENTO");
					break;
				}
				else 
				{
					listar_alunos(*inicio_aluno);

					aviso_usuario_l("LISTAGEM REALIZADA COM SUCESSO!");
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
						aviso_usuario_c("REMOÇÃO SUCESSO");
						break;
					}
					case (LISTA_VAZIA):
					{
						aviso_usuario_c("ATUALMENTE NÃO HÁ ALUNOS PARA REMOVER");
						break;
					}
					case (MATRICULA_NAO_ENCONTRADA):
					{
						aviso_usuario_c("A MATRICULA INSERIDA NÃO FOI ENCONTRADA");
						break;
					}
				}
				break;
			}
			case (OPCAO_ALTERAR):
			{
				receber_matricula(&mat);
				switch(alterar_aluno_matricula(inicio_aluno, mat))
				{
					case (ALTERACAO_SUCESSO):
					{
						aviso_usuario_c("ALTERÇÃO SUCESSO!");
						break;
					}

					case (MATRICULA_NAO_ENCONTRADA):
					{
						aviso_usuario_c("A MATRÍCULA INSERIDA NÃO FOI ENCONTRADA");
						break;
					}
					case (LISTA_VAZIA):
					{
						aviso_usuario_c("ATUALMENTE NÃO HÁ PROFESSORES PARA ALTERAR");
						break;
					}
				}
				break;   
			}
		}
	} while (*opcao != OPCAO_SAIR);
	*opcao = 1;
}

void menu_Aluno (int* opcao)
{
	system("clear");
	printf("###MÓDULO ALUNO###\n\n");
	printf("Opções:\n");
	printf("0 - Sair\n");
	printf("1 - Cadastrar aluno\n");
	printf("2 - Alterar aluno\n");
	printf("3 - Remover aluno\n");
	printf("4 - Listar alunos\n");
	printf("\nEntre com a opção desejada: ");
	ext_ler_int_f(opcao, CASAS_INT_MENU);
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

int cadastrar_aluno (Aluno** inicio_aluno, int* matricula_aluno_incr)
{
	Info_Aluno nova_info_aluno;

	imprimir_linhas(NUM_LINHAS);
	novo_identificador(&(nova_info_aluno.matricula), matricula_aluno_incr);

	printf("\nEntre com o nome do aluno: ");
	ler_string_f(nova_info_aluno.nome, sizeof(nova_info_aluno.nome));

	printf("\nEntre com a data de nascimento do aluno (Formato: [dd/mm/yyyy]): ");
	ler_string_f(nova_info_aluno.data_nascimento, sizeof(nova_info_aluno.data_nascimento));

	printf("\nEntre com o cpf do aluno (Formato: [xxx.xxx.xxx-xx]): ");
	ler_string_f(nova_info_aluno.cpf, sizeof(nova_info_aluno.cpf));

	printf("\nEntre com o sexo do aluno [M ou F]: ");
	ler_string_f(nova_info_aluno.sexo, sizeof(nova_info_aluno.sexo));

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
	imprimir_campo("Sexo", atual_aluno->info.sexo);
	imprimir_campo("Cpf", atual_aluno->info.cpf);
	imprimir_campo("Data de Nascimento", atual_aluno->info.data_nascimento);
	imprimir_linhas(NUM_LINHAS);

	printf("\n");

	listar_alunos(atual_aluno->prox);
}

int remover_aluno_matricula (Aluno** inicio_aluno, int matricula)
{
	if (inicio_aluno == NULL)
		return LISTA_VAZIA;
		
	Aluno* aluno_alvo = NULL;

	buscar_aluno_matricula((*inicio_aluno), &aluno_alvo, matricula);

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

void buscar_aluno_matricula (Aluno* atual_aluno, Aluno** aluno_alvo, int matricula)
{
	if (atual_aluno == NULL)
		return;

	if (atual_aluno->info.matricula == matricula)
		*aluno_alvo = atual_aluno;

	buscar_aluno_matricula(atual_aluno->prox, aluno_alvo, matricula);
}

int alterar_aluno_matricula (Aluno** inicio_aluno, int matricula)
{
	if (*inicio_aluno == NULL)
		return LISTA_VAZIA;
		
	Aluno* aluno_alvo = NULL;
	buscar_aluno_matricula((*inicio_aluno), &aluno_alvo, matricula);


	if (aluno_alvo == NULL)
		return MATRICULA_NAO_ENCONTRADA;
	else
	{
		int opcao;

		mostrar_aluno(aluno_alvo);
		
		imprimir_linhas(NUM_LINHAS);

		mudar_campo_str(aluno_alvo->info.nome, "nome", sizeof(aluno_alvo->info.nome), &opcao);
		mudar_campo_str(aluno_alvo->info.cpf, "cpf", sizeof(aluno_alvo->info.cpf), &opcao);
		mudar_campo_str(aluno_alvo->info.data_nascimento, "data de nascimento", sizeof(aluno_alvo->info.data_nascimento), &opcao);
		mudar_campo_str(aluno_alvo->info.sexo, "sexo", sizeof(aluno_alvo->info.sexo), &opcao);

		return ALTERACAO_SUCESSO;
	}
}

void mostrar_aluno (Aluno* aluno_alvo)
{	

	imprimir_linhas(NUM_LINHAS);
	imprimir_campo("Matrícula", int_para_string(aluno_alvo->info.matricula));
	imprimir_campo("Nome", aluno_alvo->info.nome);
	imprimir_campo("CPF", aluno_alvo->info.cpf);
	imprimir_campo("Data de Nascimento", aluno_alvo->info.data_nascimento);
	imprimir_campo("Sexo", aluno_alvo->info.sexo);
	imprimir_linhas(NUM_LINHAS);

	printf("\n");
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
