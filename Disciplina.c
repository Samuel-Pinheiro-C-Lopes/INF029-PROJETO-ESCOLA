#include "Disciplina.h"
#include "Utils.h"


void main_disciplina (Disciplina** inicio_disciplina, Aluno** inicio_aluno, Professor** inicio_professor, int* opcao)
{
	Disciplina* disciplina_alvo_menu = NULL;
	int retorno;
	int cod;
	int mat;
	do 
	{
		menu_disciplina(opcao);
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
			case (OPCAO_ALTERAR):
			{
				do
				{
					menu_alterar(opcao);
					if (*opcao * -1 != OPCAO_SAIR)
					{
						receber_codigo(&cod);
						buscar_disciplina_codigo(*inicio_disciplina, &disciplina_alvo_menu, cod);
					}

					switch (*opcao * -1)
					{
						case (OPCAO_CADASTRAR):
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
						case (OPCAO_ALTERAR):
						{
							break;
						}
						case (OPCAO_REMOVER):
						{
							receber_matricula(&mat);
							switch (remover_disciplina_aluno_matricula(disciplina_alvo_menu, mat))
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
						}
					}
				} while (*opcao != OPCAO_SAIR);

				*opcao = 1;
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
			case (DETALHAR_DISCIPLINA):
			{
				receber_codigo(&cod);
				buscar_disciplina_codigo(*inicio_disciplina, &disciplina_alvo_menu, cod);

				switch (detalhar_disciplina(disciplina_alvo_menu))
				{
					case (CODIGO_NAO_ENCONTRADO):
					{
						aviso_usuario("CÓDIGO NÃO PERTENCE A NENHUMA DISCIPLINA");
						break;
					}
					case (LISTAGEM_SUCESSO):
					{
						aviso_usuario("LISTAGEM REALIZADA COM SUCESSO!");
					}
				}

				break;	
			}
		}
	} while (*opcao != OPCAO_SAIR);
	*opcao = 1;
}

void menu_disciplina (int* opcao)
{
	printf("###MÓDULO DISCIPLINA###\n\n");
	printf("Opções:\n");
	printf("0 - Sair\n");
	printf("1 - Cadastrar disciplina\n");
	printf("2 - Alterar disciplina\n");
	printf("3 - Remover disciplina\n");
	printf("4 - Listar disciplinas\n");
	printf("5 - Detalhar disciplina\n");
	printf("\nEntre com a opção desejada: ");
	scanf(" %d", opcao);
	limpar();
}

void menu_alterar (int* opcao)
{
	system("clear");
	printf("###ALTERAR DISCIPLINA\n\n###");
	printf("Opções:\n");
	printf("1 - Cadastrar aluno em um disciplina\n");
	printf("2 - Alterar dados da disciplina\n");
	printf("3 - Remover cadastro de aluno de uma disciplina\n");
	printf("0 - Sair\n");
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

void inserir_disciplina_aluno (Disciplina* disciplina, Aluno* aluno)
{
	Disciplina_Aluno* nova_disciplina_aluno = (Disciplina_Aluno*) malloc(sizeof(Disciplina_Aluno));

	if (disciplina->info.disciplina_aluno != NULL)
		disciplina->info.disciplina_aluno->ant = nova_disciplina_aluno; 

	nova_disciplina_aluno->aluno = aluno;
	nova_disciplina_aluno->prox = disciplina->info.disciplina_aluno;
	nova_disciplina_aluno->ant = NULL;

	disciplina->info.disciplina_aluno = nova_disciplina_aluno;
}

int cadastrar_disciplina (Disciplina** inicio_disciplina, Professor** inicio_professor)
{
	Info_Disciplina nova_info_disciplina;
	int mat;
	int validade_info_disciplina;

	imprimir_linhas(NUM_LINHAS);
	printf("\nEntre com o nome do disciplina: ");
	ler_string(nova_info_disciplina.nome, 50);
	printf("\nEntre com a matrícula do professor da disciplina: ");
	ler_int(&mat);
 	buscar_professor_matricula(*inicio_professor, &(nova_info_disciplina.professor), mat);
	printf("\nEntre com o semestre da disciplina: ");
	ler_int(&nova_info_disciplina.semestre);
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
	Disciplina* disciplina = NULL;
	Aluno* aluno = NULL;
	int cod;
	int mat;

	imprimir_linhas(NUM_LINHAS);
	printf("\nEntre com o código da disciplina o qual você quer cadastrar um aluno: ");
	ler_int(&cod);
	printf("\nEntre com a matrícula do aluno que deseja cadastrar na disciplina: ");
	ler_int(&mat);
	imprimir_linhas(NUM_LINHAS);

	buscar_aluno_matricula(*inicio_aluno, &aluno, mat);

	if (aluno == NULL)
		return MATRICULA_NAO_ENCONTRADA;

 	buscar_disciplina_codigo(*inicio_disciplina, &disciplina, cod);

	if (disciplina == NULL)
		return CODIGO_NAO_ENCONTRADO;
	
	inserir_disciplina_aluno(disciplina, aluno);

	return CADASTRO_SUCESSO;
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

void listar_disciplina_alunos (Disciplina_Aluno* atual_disciplina_aluno)
{
	if (atual_disciplina_aluno == NULL)
		return;

	imprimir_linhas(NUM_LINHAS);
	imprimir_campo("Matrícula", int_para_string(atual_disciplina_aluno->aluno->info.matricula));
	imprimir_campo("Nome", atual_disciplina_aluno->aluno->info.nome);
	imprimir_campo("Sexo", atual_disciplina_aluno->aluno->info.sexo);
	imprimir_campo("CPF", atual_disciplina_aluno->aluno->info.cpf);
	imprimir_campo("Data de Nascimento", atual_disciplina_aluno->aluno->info.data_nascimento);
	imprimir_linhas(NUM_LINHAS);

	printf("\n");

	listar_disciplina_alunos(atual_disciplina_aluno->prox);
}

int detalhar_disciplina (Disciplina* disciplina_alvo)
{
	if (disciplina_alvo == NULL)
		return CODIGO_NAO_ENCONTRADO;

	imprimir_linhas(NUM_LINHAS);
	printf("#DISCIPLINA#\n\n");
	imprimir_campo("Nome", disciplina_alvo->info.nome);
	imprimir_campo("Código", int_para_string(disciplina_alvo->info.codigo));
	imprimir_campo("Professor", disciplina_alvo->info.professor->info.nome);
	imprimir_campo("Semestre", int_para_string(disciplina_alvo->info.semestre));
	imprimir_linhas(NUM_LINHAS);

	printf("#ALUNOS CADASTRADOS#\n\n");

	listar_disciplina_alunos(disciplina_alvo->info.disciplina_aluno);

	if (disciplina_alvo->info.disciplina_aluno == NULL)
		printf("Não há alunos cadastrados nesta disciplina no momento...\n\n");

	return LISTAGEM_SUCESSO;
}

int remover_disciplina_codigo (Disciplina** inicio_disciplina, int codigo)
{
	if (inicio_disciplina == NULL)
		return LISTA_VAZIA;
		
	Disciplina* disciplina_alvo = NULL;
	buscar_disciplina_codigo((*inicio_disciplina), &disciplina_alvo, codigo);

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

int remover_disciplina_aluno_matricula (Disciplina* disciplina, int matricula)
{
	Disciplina_Aluno* disciplina_aluno_alvo = NULL;
	buscar_disciplina_aluno_matricula(disciplina->info.disciplina_aluno, &disciplina_aluno_alvo, matricula);

	if (disciplina_aluno_alvo == NULL)
		return MATRICULA_NAO_ENCONTRADA;

	if (disciplina_aluno_alvo->ant != NULL)
		disciplina_aluno_alvo->ant->prox = disciplina_aluno_alvo->prox;
	else
		disciplina->info.disciplina_aluno = disciplina_aluno_alvo->prox;

	if (disciplina_aluno_alvo->prox != NULL)
		disciplina_aluno_alvo->prox->ant = disciplina_aluno_alvo->ant;

	free(disciplina_aluno_alvo);

	return REMOCAO_SUCESSO;
}

void buscar_disciplina_codigo (Disciplina* atual_disciplina, Disciplina** disciplina_alvo, int codigo)
{
	if (atual_disciplina == NULL)
		return;

	if (atual_disciplina->info.codigo == codigo)
		*disciplina_alvo = atual_disciplina;

	buscar_disciplina_codigo(atual_disciplina->prox, disciplina_alvo, codigo);
}

void buscar_disciplina_aluno_matricula (Disciplina_Aluno* atual_disciplina_aluno, Disciplina_Aluno** disciplina_aluno_alvo, int matricula)
{
	if (atual_disciplina_aluno == NULL)
		return;

	if (atual_disciplina_aluno->aluno->info.matricula == matricula)
		*disciplina_aluno_alvo = atual_disciplina_aluno;

	buscar_disciplina_aluno_matricula(atual_disciplina_aluno->prox, disciplina_aluno_alvo, matricula);
}

void receber_codigo (int* cod)
{
	printf("Entre com o número de código da disciplina: ");
	scanf(" %d", cod);
	limpar();
}