#include "Disciplina.h"
#include "Utils.h"


void main_disciplina (Disciplina** inicio_disciplina, Aluno** inicio_aluno, Professor** inicio_professor, int* codigo_disciplina_incr, int* opcao)
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
			// CADASTRAR DISCIPLINA
			case (OPCAO_CADASTRAR):
			{
				retorno = cadastrar_disciplina(inicio_disciplina, inicio_professor, codigo_disciplina_incr);
				switch (retorno)
				{
					case (CADASTRO_SUCESSO):
					{
						aviso_usuario_c("CADASTRO REALIZADO COM SUCESSO!");
						break;
					}
					case (MATRICULA_NAO_ENCONTRADA):
					{
						aviso_usuario_c("NÃO HÁ PROFESSOR COM A MATRÍCULA ESPECIFICADA");
						break;
					}
					case (NUMERO_INVALIDO):
					{
						aviso_usuario_c("NÚMERO DO SEMESTRE INVÁLIDO");
						break;
					}
				}
			break;   
			}
			// ALTERAR DISCIPLINA
			case (OPCAO_ALTERAR):
			{
				do
				{
					menu_alterar(opcao);

					switch (*opcao * -1)
					{
						// CADASTRAR ALUNO EM DISCIPLINA
						case (OPCAO_CADASTRAR):
						{
							switch (cadastrar_disciplina_aluno(inicio_disciplina, inicio_aluno))
							{
								case (MATRICULA_NAO_ENCONTRADA):
								{
									aviso_usuario_c("A MATRICULA INSERIDA NÃO PERTENCE A NENHUM ALUNO CADASTRADO");
									break;
								}
								case (CODIGO_NAO_ENCONTRADO):
								{
									aviso_usuario_c("O CÓDIGO INSERIDO NÃO PERTENCE A NENHUMA DISCIPLINA CADASTRADA");
									break;
								}
								case (CADASTRO_SUCESSO):
								{
									aviso_usuario_c("CADASTRO DO ALUNO NA DISCIPLINA REALIZADO COM SUCESSO!");
									break;
								}
							}
							break;
						}
						// ALTERAR DADOS DE UMA DISCIPLINA
						case (OPCAO_ALTERAR):
						{
							receber_codigo(&cod);
							switch(alterar_disciplina_matricula(inicio_disciplina, inicio_professor, cod))
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
						// REMOVER ALUNO CADASTRADO EM UMA DISCIPLINA
						case (OPCAO_REMOVER):
						{
							receber_codigo(&cod);
							receber_matricula(&mat);
							buscar_disciplina_codigo(*inicio_disciplina, &disciplina_alvo_menu, cod);
							switch (remover_disciplina_aluno_matricula(disciplina_alvo_menu, mat))
							{
								case (REMOCAO_SUCESSO):
								{
									aviso_usuario_c("REMOÇÃO SUCESSO");
									break;
								}
								case (LISTA_VAZIA):
								{
									aviso_usuario_c("ATUALMENTE NÃO HÁ DISCIPLINAS PARA REMOVER");
									break;
								}
								case (MATRICULA_NAO_ENCONTRADA):
								{
									aviso_usuario_c("A MATRICULA INSERIDA NÃO FOI ENCONTRADA");
									break;
								}
							}
						}
					}
				} while (*opcao != OPCAO_SAIR);

				*opcao = 1;
				break;   
			}
			// REMOVER UMA DISCIPLINA
			case (OPCAO_REMOVER):
			{
 				receber_codigo(&cod);
				switch (remover_disciplina_codigo(inicio_disciplina, cod))
				{
					case (REMOCAO_SUCESSO):
					{
						aviso_usuario_c("REMOÇÃO SUCESSO");
						break;
					}
					case (LISTA_VAZIA):
					{
						aviso_usuario_c("ATUALMENTE NÃO HÁ DISCIPLINAS PARA REMOVER");
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
			// LISTAR AS DISCIPLINAS
			case (OPCAO_LISTAR):
			{
				if (*inicio_disciplina == NULL)
				{
					aviso_usuario_c("NÃO HÁ DISCIPLINAS MATRICULADOS NO MOMENTO");
					break;
				}
				else 
				{
					int opt_alt;
					do
					{
						system("clear");
						printf("\nENTRE COM A OPÇÃO:\n\n");
						printf("0 - SAIR\n");
						printf("1 - LISTAR POR EXTRAPOLAÇÃO\n");
						printf("2 - LISTAR POR NÚMERO MÁXIMO  DE MATRÍCULA\n");
						printf("3 - LISTAR TODOS\n");
						printf("\nOpção: ");
						ext_ler_int_f(&opt_alt, CASAS_INT_GERAL);
						system("clear");

						switch(opt_alt * 120)
						{
							case (120):
							{
								listar_disciplinas_extr('<', inicio_disciplina);
								break;
							}
							case (240):
							{
								listar_disciplinas_extr('>', inicio_disciplina);
								break;
							}
							case (360):
							{
								listar_disciplinas(*inicio_disciplina);
								aviso_usuario_l("LISTAGEM REALIZADA COM SUCESSO!");
								break;
							}
						}
					} while (opt_alt != OPCAO_SAIR);
				}
				break;   
			}
			// DETALHAR UMA DISCIPLINA (mostra alunos)
			case (DETALHAR_DISCIPLINA):
			{
				receber_codigo(&cod);
				buscar_disciplina_codigo(*inicio_disciplina, &disciplina_alvo_menu, cod);

				switch (detalhar_disciplina(disciplina_alvo_menu))
				{
					case (CODIGO_NAO_ENCONTRADO):
					{
						aviso_usuario_c("CÓDIGO NÃO PERTENCE A NENHUMA DISCIPLINA");
						break;
					}
					case (LISTAGEM_SUCESSO):
					{
						aviso_usuario_l("LISTAGEM REALIZADA COM SUCESSO!");
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
	system("clear");
	printf("###MÓDULO DISCIPLINA###\n\n");
	printf("Opções:\n");
	printf("0 - Sair\n");
	printf("1 - Cadastrar disciplina\n");
	printf("2 - Alterar disciplina\n");
	printf("3 - Remover disciplina\n");
	printf("4 - Listar disciplinas\n");
	printf("5 - Detalhar disciplina\n");
	printf("\nEntre com a opção desejada: ");
	ext_ler_int_f(opcao, CASAS_INT_MENU);
	system("clear");
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
	ext_ler_int_f(opcao, CASAS_INT_MENU);
	system("clear");
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

int cadastrar_disciplina (Disciplina** inicio_disciplina, Professor** inicio_professor, int* codigo_disciplina_incr)
{
	Info_Disciplina nova_info_disciplina;
	int mat;
	int validade_info_disciplina;

	imprimir_linhas(NUM_LINHAS);
	printf("\nEntre com o nome do disciplina: ");
	ler_string_f(nova_info_disciplina.nome, 50);
	printf("\nEntre com a matrícula do professor da disciplina: ");
	ext_ler_int_f(&mat, CASAS_INT_GERAL);
	nova_info_disciplina.professor = NULL;
 	buscar_professor_matricula(*inicio_professor, &(nova_info_disciplina.professor), mat);
	printf("\nEntre com o semestre da disciplina: ");
	ext_ler_int_f(&nova_info_disciplina.semestre, CASAS_INT_GERAL);
	imprimir_linhas(NUM_LINHAS);

	validade_info_disciplina = validar_info_disciplina(&nova_info_disciplina);

	if (validade_info_disciplina == DISCIPLINA_VALIDA)
	{
		novo_identificador(&(nova_info_disciplina.codigo), codigo_disciplina_incr);  
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
	ext_ler_int_f(&cod, CASAS_INT_GERAL);
	printf("\nEntre com a matrícula do aluno que deseja cadastrar na disciplina: ");
	ext_ler_int_f(&mat, CASAS_INT_GERAL);
	imprimir_linhas(NUM_LINHAS);

	buscar_aluno_matricula(*inicio_aluno, &aluno, mat);

	if (aluno == NULL)
		return MATRICULA_NAO_ENCONTRADA;

 	buscar_disciplina_codigo(*inicio_disciplina, &disciplina, cod);

	if (disciplina == NULL)
		return CODIGO_NAO_ENCONTRADO;

	Disciplina_Aluno* atual_disciplina_aluno = disciplina->info.disciplina_aluno;

	while (atual_disciplina_aluno != NULL)
	{
		if (atual_disciplina_aluno->aluno->info.matricula == mat)
			return MATRICULA_NAO_ENCONTRADA;
		else
			atual_disciplina_aluno = atual_disciplina_aluno->prox;
	}
	
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

	Professor* professor_disciplina = atual_disciplina->info.professor;

	imprimir_linhas(NUM_LINHAS);
	imprimir_campo("Nome", atual_disciplina->info.nome);
	imprimir_campo("Código", int_para_string(atual_disciplina->info.codigo));
	imprimir_campo("Professor", (professor_disciplina != NULL ? professor_disciplina->info.nome : "PROFESSOR REMOVIDO..."));
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

	while (disciplina_alvo->info.disciplina_aluno->prox != NULL)
	{
		disciplina_alvo->info.disciplina_aluno = disciplina_alvo->info.disciplina_aluno->prox;
		free(disciplina_alvo->info.disciplina_aluno->ant);
	}

	free(disciplina_alvo->info.disciplina_aluno);

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
	else if (atual_disciplina->info.codigo == codigo)
		*disciplina_alvo = atual_disciplina;
	else
		buscar_disciplina_codigo(atual_disciplina->prox, disciplina_alvo, codigo);
}

void buscar_disciplina_aluno_matricula (Disciplina_Aluno* atual_disciplina_aluno, Disciplina_Aluno** disciplina_aluno_alvo, int matricula)
{
	if (atual_disciplina_aluno == NULL)
		return;
	else if (atual_disciplina_aluno->aluno->info.matricula == matricula)
		*disciplina_aluno_alvo = atual_disciplina_aluno;
	else
		buscar_disciplina_aluno_matricula(atual_disciplina_aluno->prox, disciplina_aluno_alvo, matricula);
}

int alterar_disciplina_matricula (Disciplina** inicio_disciplina, Professor** inicio_professor, int codigo)
{
	if (*inicio_disciplina == NULL)
		return LISTA_VAZIA;
		
	Disciplina* disciplina_alvo = NULL;
	buscar_disciplina_codigo((*inicio_disciplina), &disciplina_alvo, codigo);


	if (disciplina_alvo == NULL)
		return MATRICULA_NAO_ENCONTRADA;
	else
	{
		int opcao;

		mostrar_disciplina(disciplina_alvo);
		
		imprimir_linhas(NUM_LINHAS);

		mudar_campo_str(disciplina_alvo->info.nome, "nome", sizeof(disciplina_alvo->info.nome), &opcao);

		int retorno;
		do
		{
			retorno = mudar_disciplina_professor(disciplina_alvo, inicio_professor, &opcao);
			
			switch (retorno)
			{
				case (LISTA_VAZIA):
				{
					aviso_usuario_l("NÃO HÁ PROFESSORES MATRICULADOS NO MOMENTO");
					break;
				}
				case (MATRICULA_NAO_ENCONTRADA):
				{
					aviso_usuario_l("NÃO HÁ PROFESSOR COM A MATRÍCULA INSERIDA");
					break;
				}
				case (ALTERACAO_SUCESSO):
				{
					aviso_usuario_l("PROFESSOR ALTERADO COM SUCESSO!");
					break;
				}

			}
		} while (retorno != OPCAO_SAIR && retorno != ALTERACAO_SUCESSO);

		mudar_campo_int(&(disciplina_alvo->info.semestre), "semestre", CASAS_INT_GERAL, &opcao);
	
		return ALTERACAO_SUCESSO;
	}
}

int mudar_disciplina_professor (Disciplina* disciplina, Professor** inicio_professor, int* opcao)
{
	do
	{
		printf("\nMudar o professor?\n[1 para sim; 0 para não]: ");	
		ext_ler_int_f(opcao, CASAS_INT_MENU);
		if (*opcao == 0)
			return OPCAO_SAIR;
		system("clear");
	} while (*opcao != 1);

	int mat;

	if (inicio_professor == NULL)
		return LISTA_VAZIA;

	Professor* professor_alvo = NULL;
	printf("Entre com a matrícula do novo professor: ");
	ext_ler_int_f(&mat, CASAS_INT_GERAL);

	buscar_professor_matricula(*inicio_professor, &professor_alvo, mat);

	if (professor_alvo == NULL)
		return MATRICULA_NAO_ENCONTRADA;

	disciplina->info.professor = professor_alvo;

	return ALTERACAO_SUCESSO;
}

void mostrar_disciplina (Disciplina* disciplina_alvo)
{	

	imprimir_linhas(NUM_LINHAS);
	imprimir_campo("Código", int_para_string(disciplina_alvo->info.codigo));
	imprimir_campo("Nome", disciplina_alvo->info.nome);
	imprimir_campo("Professor", disciplina_alvo->info.professor->info.nome);
	imprimir_campo("Semestre", int_para_string(disciplina_alvo->info.semestre));
	imprimir_linhas(NUM_LINHAS);

	printf("\n");
}

void listar_disciplinas_extr (char sinal, Disciplina** inicio_disciplina)
{
	int num_extr, count;
	printf("\nEntre com o número delimitador para os alunos matrículados na disciplina para o filtro: ");
	ext_ler_int_f(&num_extr, CASAS_INT_GERAL);

	Disciplina* atual_disciplina = *inicio_disciplina;
	Disciplina_Aluno* atual_disciplina_aluno = NULL;

	while (atual_disciplina != NULL)
	{
		count = 0;
		atual_disciplina_aluno = atual_disciplina->info.disciplina_aluno;

		for (;atual_disciplina_aluno != NULL; atual_disciplina_aluno = atual_disciplina_aluno->prox, count++);

		if (sinal == '>')
		{
			if (count > num_extr)
			{
				mostrar_disciplina(atual_disciplina);
				imprimir_linhas(NUM_LINHAS);
				imprimir_campo("Quantidade", int_para_string(count));
				imprimir_linhas(NUM_LINHAS);
				printf("\n\n");
			}
		}
		else if (sinal == '<')
		{
			if (count < num_extr)
			{
				mostrar_disciplina(atual_disciplina);
				imprimir_linhas(NUM_LINHAS);
				imprimir_campo("Quantidade", int_para_string(count));
				imprimir_linhas(NUM_LINHAS);
				printf("\n\n");
			}
		}

		atual_disciplina = atual_disciplina->prox;
	}

	aviso_usuario_l("LISTAGEM REALIZADA COM SUCESSO!");
}

/*
void atualizar_disciplinas_alunos (Disciplina** inicio_disciplina, Aluno** inicio_aluno)
{
	Disciplina* atual_disciplina = *inicio_disciplina;
	Disciplina_Aluno* atual_disciplina_aluno = NULL;
	Aluno* aluno_encontrado = NULL;

	while (atual_disciplina != NULL)
	{
		printf("\nNão foi aqui 1...");
		atual_disciplina_aluno = atual_disciplina->info.disciplina_aluno;
		while (atual_disciplina_aluno != NULL)
		{
			printf("\nNão foi aqui 2...");
			printf("\n %d NÃO É ISSO EIN\n",  atual_disciplina_aluno->aluno->info.matricula);
			buscar_aluno_matricula(*inicio_aluno, &aluno_encontrado, atual_disciplina_aluno->aluno->info.matricula);

			if (aluno_encontrado == NULL)
				remover_disciplina_aluno_matricula(atual_disciplina, atual_disciplina_aluno->aluno->info.matricula);

			atual_disciplina_aluno = atual_disciplina_aluno->prox;
		}
		atual_disciplina = atual_disciplina->prox;
	}
}
*/
