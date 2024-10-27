#include "Disciplina.h"
#include "Utils.h"


void mainDisciplina (Disciplina** inicio_disciplina, Aluno** inicio_aluno, Professor** inicio_professor, int* opcao)
{
	int retorno;
	int cod;
	do 
	{
		system("clear");
		menu_Disciplina(opcao);
		switch (*opcao * -1)
		{
			case (OPCAO_CADASTRAR):
			{
				retorno = cadastrar_disciplina(inicio_disciplina, inicio_professor);
				limpar();
				switch (retorno)
				{
					case (CADASTRO_SUCESSO):
					{
						aviso_usuario("CADASTRO REALIZADO COM SUCESSO!");
						break;
					}
					case (MATRICULA_NAO_ENCONTRADA):
					{
						aviso_usuario("NÃO HÁ PROFESSOR COM A MATRÍCULA ESPECIFICADA");
						break;
					}
					case (NUMERO_INVALIDO):
					{
						aviso_usuario("NÚMERO DO SEMESTRE INVÁLIDO");
						break;
					}
				}
			break;   
			}
			case (OPCAO_LISTAR):
			{
				if (*inicio_disciplina == NULL)
				{
					aviso_usuario("NÃO HÁ DISCIPLINAS MATRICULADOS NO MOMENTO");
					break;
				}
				else 
				{
					listar_disciplinas(*inicio_disciplina);
					aviso_usuario("LISTAGEM REALIZADA COM SUCESSO!");
				}
				break;   
			}
			case (OPCAO_REMOVER):
			{
 				receber_codigo(&cod);
				switch (remover_disciplina_codigo(inicio_disciplina, cod))
				{
					case (REMOCAO_SUCESSO):
					{
						aviso_usuario("REMOÇÃO SUCESSO");
						break;
					}
					case (LISTA_VAZIA):
					{
						aviso_usuario("ATUALMENTE NÃO HÁ DISCIPLINAS PARA REMOVER");
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
			case (CADASTRAR_DISCIPLINA_ALUNO):
			{
				retorno = cadastrar_disciplina_aluno(inicio_disciplina, inicio_aluno);
				limpar();
				switch (retorno)
				{
					case (MATRICULA_NAO_ENCONTRADA):
					{
						aviso_usuario("A MATRICULA INSERIDA NÃO PERTENCE A NENHUM ALUNO CADASTRADO");
						break;
					}
					case (CODIGO_NAO_ENCONTRADO):
					{
						aviso_usuario("O CÓDIGO INSERIDO NÃO PERTENCE A NENHUMA DISCIPLINA CADASTRADA");
						break;
					}
					case (CADASTRO_SUCESSO):
					{
						aviso_usuario("CADASTRO DO ALUNO NA DISCIPLINA REALIZADO COM SUCESSO!");
						break;
					}
				}
			}
			case (DETALHAR_DISCIPLINA):
			{
				break;	
			}
		}
	} while (*opcao != OPCAO_SAIR);
	*opcao = 1;
}

void menu_Disciplina (int* opcao)
{
	printf("###MÓDULO DISCIPLINA###\n\n");
	printf("Opções:\n");
	printf("0 - Sair\n");
	printf("1 - Cadastrar disciplina\n");
	printf("2 - Listar disciplinas\n");
	printf("3 - Remover disciplina\n");
	printf("4 - Alterar disciplina\n");
	printf("5 - Cadastrar aluno em disciplina\n");
	printf("6 - Detalhar disciplina\n");
	printf("\nEntre com a opção desejada: ");
	scanf(" %d", opcao);
	limpar();
}

void inserir_disciplina (Disciplina** inicio_disciplina, Info_Disciplina nova_info_disciplina)
{
	Disciplina* nova_disciplina = (Disciplina*) malloc(sizeof(Disciplina));

	if (*inicio_disciplina != NULL)
		(*inicio_disciplina)->ant = nova_disciplina;

	nova_disciplina->info = nova_info_disciplina;
	nova_disciplina->prox = *inicio_disciplina;
	nova_disciplina->ant = NULL;

	*inicio_disciplina = nova_disciplina;
}

int cadastrar_disciplina (Disciplina** inicio_disciplina, Professor** inicio_professor)
{
	Info_Disciplina nova_info_disciplina;
	int mat;
	int validade_info_disciplina;

	imprimir_linhas(NUM_LINHAS);
	printf("\nEntre com o nome do disciplina: ");
	ler_string(nova_info_disciplina.nome, 50);
	printf("\nEntre com a codigo do disciplina: ");
	scanf(" %d", &nova_info_disciplina.codigo);
	printf("\nEntre com a matrícula do professor da disciplina: ");
	scanf(" %d", &mat);
	nova_info_disciplina.professor = buscar_professor_matricula(*inicio_professor, mat);
	printf("\nEntre com o semestre da disciplina: ");
	scanf(" %d", &nova_info_disciplina.semestre);
	imprimir_linhas(NUM_LINHAS);

	validade_info_disciplina = validar_info_disciplina(&nova_info_disciplina);

	if (validade_info_disciplina == DISCIPLINA_VALIDA)
	{
		nova_info_disciplina.disciplina_aluno = NULL;
		inserir_disciplina(inicio_disciplina, nova_info_disciplina);
		return CADASTRO_SUCESSO;
	}
	else
	{
		return validade_info_disciplina;
	}
}

int cadastrar_disciplina_aluno (Disciplina** inicio_disciplina, Aluno** inicio_aluno)
{
	Disciplina* disciplina;
	Aluno* aluno;
	int cod;
	int mat;

	imprimir_linhas(NUM_LINHAS);
	printf("\nEntre com o código da disciplina o qual você quer cadastrar um aluno: ");
	scanf(" %d", &cod);
	printf("\nEntre com a matrícula do aluno que deseja cadastrar na disciplina: ");
	scanf(" %d", &mat);
	imprimir_linhas(NUM_LINHAS);

	aluno = buscar_aluno_matricula(*inicio_aluno, mat);

	if (aluno == NULL)
		return MATRICULA_NAO_ENCONTRADA;

	disciplina = buscar_disciplina_codigo(*inicio_disciplina, cod);

	if (disciplina == NULL)
		return CODIGO_NAO_ENCONTRADO;
	
	inserir_disciplina_aluno(disciplina, aluno);

	return CADASTRO_SUCESSO;
}

void inserir_disciplina_aluno (Disciplina* disciplina, Aluno* aluno)
{
	Disciplina_Aluno* nova_disciplina_aluno = (Disciplina_Aluno*) malloc(sizeof(Disciplina_Aluno));

	nova_disciplina_aluno->aluno = aluno;
	nova_disciplina_aluno->prox = disciplina->info.disciplina_aluno;
	nova_disciplina_aluno->ant = NULL;

	disciplina->info.disciplina_aluno->ant = nova_disciplina_aluno; 
	disciplina->info.disciplina_aluno = nova_disciplina_aluno;
}

int validar_info_disciplina (Info_Disciplina* info_disciplina)
{
	if (info_disciplina->professor == NULL)
		return MATRICULA_NAO_ENCONTRADA;
	else if (info_disciplina->semestre < 1)
		return NUMERO_INVALIDO;
	else 
		return DISCIPLINA_VALIDA;
}

void listar_disciplinas (Disciplina* atual_disciplina)
{
	if (atual_disciplina == NULL)
		return;

	imprimir_linhas(NUM_LINHAS);
	imprimir_campo("Nome", atual_disciplina->info.nome);
	imprimir_campo("Código", int_para_string(atual_disciplina->info.codigo));
	imprimir_campo("Professor", atual_disciplina->info.professor->info.nome);
	imprimir_campo("Semestre", int_para_string(atual_disciplina->info.semestre));
	imprimir_linhas(NUM_LINHAS);

	printf("\n");

	listar_disciplinas(atual_disciplina->prox);
}

int remover_disciplina_codigo (Disciplina** inicio_disciplina, int codigo)
{
	if (inicio_disciplina == NULL)
		return LISTA_VAZIA;
		
	Disciplina* disciplina_alvo = buscar_disciplina_codigo((*inicio_disciplina), codigo);

	if (disciplina_alvo == NULL)
		return MATRICULA_NAO_ENCONTRADA;

	if (disciplina_alvo->ant != NULL)
		disciplina_alvo->ant->prox = disciplina_alvo->prox;
	else
		(*inicio_disciplina) = disciplina_alvo->prox;

	if (disciplina_alvo->prox != NULL)
		disciplina_alvo->prox->ant = disciplina_alvo->ant; 

	free(disciplina_alvo);

	return REMOCAO_SUCESSO;
}

Disciplina* buscar_disciplina_codigo (Disciplina* atual_disciplina, int codigo)
{
	if (atual_disciplina == NULL)
		return NULL;

	if (atual_disciplina->info.codigo == codigo)
		return atual_disciplina;

	buscar_disciplina_codigo(atual_disciplina->prox, codigo);

	return NULL;
}


void receber_codigo (int* cod)
{
	printf("Entre com o número de código: ");
	scanf(" %d", cod); limpar();
}
