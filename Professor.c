#include "Professor.h"
#include "Utils.h"


void main_professor (Professor** inicio_professor, Aluno** inicio_aluno, int* matricula_professor_incr, int* opcao)
{
	int mat;
	do 
	{
		menu_Professor(opcao);
		switch (*opcao * -1)
		{
			case (OPCAO_CADASTRAR):
			{
				switch (cadastrar_professor(inicio_professor, inicio_aluno, matricula_professor_incr))
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
				if (*inicio_professor == NULL)
				{
					aviso_usuario_c("NÃO HÁ PROFESSORS MATRICULADOS NO MOMENTO");
					break;
				}
				else 
				{
					do
					{
						menu_listar(opcao);
						switch(*(opcao) * -10)	
						{
							case (LISTAR_POR_SEXO):
							{
								professor_listar_por_sexo(*inicio_professor);
								break;
							}
							case (LISTAR_POR_DATA):
							{
								professor_listar_por_data(inicio_professor);
								break;
							}
							case (LISTAR_POR_SUBSTRING):
							{
								professor_listar_por_substring(inicio_professor);
								break;
							}
							case (LISTAR_ANIVERSARIANTES):
							{
								professor_listar_aniversariantes(inicio_professor);
								break;
							}
							case (LISTAR_POR_NOMES):
							{
								professor_ordenar_por_nomes(inicio_professor);
								break;
							}
							case (LISTAR_TODOS):
							{
								if (*inicio_professor == NULL)
									aviso_usuario_c("NÃO HÁ PROFESSORES MATRICULADOS NO MOMENTO");
								else
								{
									listar_professores(*inicio_professor);
									aviso_usuario_l("LISTAGEM DE TODOS REALIZADA COM SUCESSO");
								}
								break;
							}
						}
					} while (*opcao != OPCAO_SAIR);
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
						aviso_usuario_c("REMOÇÃO SUCESSO");
						break;
					}
					case (LISTA_VAZIA):
					{
						aviso_usuario_c("ATUALMENTE NÃO HÁ PROFESSORES PARA REMOVER");
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
				switch (alterar_professor_matricula(inicio_professor, mat))
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

void menu_Professor (int* opcao)
{
	system("clear");
	printf("###MÓDULO PROFESSOR###\n\n");
	printf("Opções:\n");
	printf("0 - Sair\n");
	printf("1 - Cadastrar professor\n");
	printf("2 - Alterar professor\n");
	printf("3 - Remover professor\n");
	printf("4 - Listar professors\n");
	printf("\nEntre com a opção desejada: ");
	ext_ler_int_f(opcao, CASAS_INT_MENU);
	system("clear");
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

int cadastrar_professor (Professor** inicio_professor, Aluno** inicio_aluno, int* matricula_professor_incr)
{
	Info_Professor nova_info_professor;
	int retorno = INFO_VALIDA;
	
	do
	{
		imprimir_linhas(NUM_LINHAS);
		printf("\nEntre com o nome do professor: ");
		ler_string_f(nova_info_professor.nome, 50);
		printf("\nEntre com o cpf do professor (Formato: [xxx.xxx.xxx-xx]): ");
		ler_string_f(nova_info_professor.cpf, 15);
		printf("\nEntre com a data de nascimento do professor (Formato: [dd/mm/yyyy]): ");
		ler_string_f(nova_info_professor.data_nascimento, 11);
		printf("\nEntre com o sexo do professor [M ou F]: ");
		ler_string_f(nova_info_professor.sexo, 2);
		imprimir_linhas(NUM_LINHAS);

		retorno = validar_info_professor(inicio_professor, inicio_aluno, nova_info_professor);

		if (retorno != INFO_VALIDA)
		{
			printf("\nAlguma informação de cadastro não é válida...\n");
			printf("\nAinda deseja realizar o cadastro?\n[1 para sim ou 0 para não]: ");
			ext_ler_int_f(&retorno, CASAS_INT_MENU);
			system("clear");
		}

	} while (retorno != OPCAO_SAIR && retorno != INFO_VALIDA);

	if (retorno == INFO_VALIDA)
	{
 		novo_identificador((&nova_info_professor.matricula), matricula_professor_incr);
		if (inserir_professor (inicio_professor, nova_info_professor) == INSERCAO_SUCESSO)	
			return CADASTRO_SUCESSO;
	}
	
	return CADASTRO_FRACASSO;
}

void listar_professores (Professor* atual_professor)
{
	if (atual_professor == NULL)
		return;

	imprimir_linhas(NUM_LINHAS);
	imprimir_campo("Matrícula", int_para_string(atual_professor->info.matricula));
	imprimir_campo("Nome", atual_professor->info.nome);
	imprimir_campo("CPF", atual_professor->info.cpf);
	imprimir_campo("Data de Nascimento", atual_professor->info.data_nascimento);
	imprimir_campo("Sexo", atual_professor->info.sexo);
	imprimir_linhas(NUM_LINHAS);

	printf("\n");

	listar_professores(atual_professor->prox);
}

int remover_professor_matricula (Professor** inicio_professor, int matricula)
{
	if (inicio_professor == NULL)
		return LISTA_VAZIA;
		
	Professor* professor_alvo = NULL;  

	buscar_professor_matricula((*inicio_professor), &professor_alvo, matricula);

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

void buscar_professor_matricula (Professor* atual_professor, Professor** professor_alvo, int matricula)
{
	if (atual_professor == NULL)
		return;

	if (atual_professor->info.matricula == matricula)
		*professor_alvo = atual_professor;

	buscar_professor_matricula(atual_professor->prox, professor_alvo, matricula);
}

int alterar_professor_matricula (Professor** inicio_professor, int matricula)
{
	if (*inicio_professor == NULL)
		return LISTA_VAZIA;
		
	Professor* professor_alvo = NULL;
	buscar_professor_matricula((*inicio_professor), &professor_alvo, matricula);


	if (professor_alvo == NULL)
		return MATRICULA_NAO_ENCONTRADA;
	else
	{
		int opcao;

		mostrar_professor(professor_alvo);
		
		imprimir_linhas(NUM_LINHAS);

		mudar_campo_str(professor_alvo->info.nome, "nome", sizeof(professor_alvo->info.nome), &opcao);
		mudar_campo_str(professor_alvo->info.cpf, "cpf", sizeof(professor_alvo->info.cpf), &opcao);
		mudar_campo_str(professor_alvo->info.data_nascimento, "data de nascimento", sizeof(professor_alvo->info.data_nascimento), &opcao);
		mudar_campo_str(professor_alvo->info.sexo, "sexo", sizeof(professor_alvo->info.sexo), &opcao);

		return ALTERACAO_SUCESSO;
	}
}

void mostrar_professor (Professor* professor_alvo)
{	

	imprimir_linhas(NUM_LINHAS);
	imprimir_campo("Matrícula", int_para_string(professor_alvo->info.matricula));
	imprimir_campo("Nome", professor_alvo->info.nome);
	imprimir_campo("CPF", professor_alvo->info.cpf);
	imprimir_campo("Data de Nascimento", professor_alvo->info.data_nascimento);
	imprimir_campo("Sexo", professor_alvo->info.sexo);
	imprimir_linhas(NUM_LINHAS);

	printf("\n");
}

int validar_info_professor(Professor** inicio_professor, Aluno** inicio_aluno, Info_Professor nova_info_professor)
{
	int retorno = INFO_VALIDA;
	int tem_cpf = CPF_NAO_ENCONTRADO;

	verificar_professores_cpf(*inicio_professor, &tem_cpf, nova_info_professor.cpf);

	if (validar_data(nova_info_professor.data_nascimento) != DATA_VALIDA)
		retorno = DATA_INVALIDA;
	else if (validar_cpf(nova_info_professor.cpf) != CPF_VALIDO)
		retorno = CPF_INVALIDO;
	else if (validar_nome(nova_info_professor.nome) != FORMATACAO_VALIDA)
		retorno = FORMATACAO_INVALIDA;
	else if (validar_sexo(nova_info_professor.sexo) != FORMATACAO_VALIDA)
		retorno = FORMATACAO_INVALIDA;
	else if (tem_cpf != CPF_NAO_ENCONTRADO)
		retorno = CPF_ENCONTRADO;

	tem_cpf = CPF_NAO_ENCONTRADO;
	verificar_alunos_cpf(*inicio_aluno, &tem_cpf, nova_info_professor.cpf);
	if (tem_cpf != CPF_NAO_ENCONTRADO)
		retorno = CPF_ENCONTRADO;

	printf("RETORNO:%d\n", retorno);
	getchar();

	return retorno;
}

void verificar_professores_cpf (Professor* professor_atual, int* tem_cpf, char* cpf)
{
		
	if (professor_atual == NULL)
		return;
	else
		verificar_string(cpf, professor_atual->info.cpf, tem_cpf);

	if (*tem_cpf != STRING_IGUAL)
		verificar_professores_cpf(professor_atual->prox, tem_cpf, cpf);
}


void quantidade_professor_lista (Professor* atual_professor, int* qnt)
{
	if (atual_professor == NULL)
		return;
	else
	{
		*qnt += 1;
		quantidade_professor_lista (atual_professor->prox, qnt);
	}
}

void professor_listar_por_data (Professor** inicio_professor)
{
	if (*inicio_professor == NULL)
	{
		aviso_usuario_c("NÃO HÁ PROFESSORES MATRICULADOS NO MOMENTO");
		return;
	}

	int qnt_professors = 0;
	quantidade_professor_lista (*inicio_professor, &qnt_professors);
	Professor professor_arr[qnt_professors];
	Professor novo_professor_arr[qnt_professors];
	Professor* professor_atual = *inicio_professor;
	Professor professor_aux;
	int trocou, i;
	int valor_data_atl, valor_data_ant;

	// preenche professor_arr com os professors da lista
	for (i = 0; i < qnt_professors && professor_atual != NULL; i++)
	{
		professor_arr[i] = *professor_atual;
		professor_atual = professor_atual->prox;
	}

	// preenche novo_professor_arr com o conteúdo de professor_arr
	for (i = 0; i < qnt_professors; i++)
		novo_professor_arr[i] = professor_arr[i];
	
	do
	{
		trocou = 0;
		for (i = 1; i < qnt_professors; i++)
		{
			valor_data_ant = valor_data(novo_professor_arr[i - 1].info.data_nascimento);
			valor_data_atl = valor_data(novo_professor_arr[i].info.data_nascimento); 
			if (valor_data_ant > valor_data_atl)
			{
				professor_aux = novo_professor_arr[i];
				novo_professor_arr[i] = novo_professor_arr[i - 1];
				novo_professor_arr[i - 1] = professor_aux;
				trocou = 1;
			}
		}
	} while (trocou);

	for (i = 0; i < qnt_professors; i++)
		mostrar_professor(novo_professor_arr + i);

	aviso_usuario_l("LISTAGEM DOS PROFESSORES POR DATA FEITA COM SUCESSO");

}

void professor_listar_por_sexo (Professor* inicio_professor)
{
	if (inicio_professor == NULL)
	{
		aviso_usuario_c("NÃO HÁ PROFESSORES MATRÍCULADOS NO MOMENTO");
		return;
	}

	printf("\nM:");
	Professor* atual_professor = inicio_professor;
	while (atual_professor != NULL)
	{
		if (atual_professor->info.sexo[0] == 'M')
			printf("\nmat: %d", atual_professor->info.matricula);
		atual_professor = atual_professor->prox;
	}
	printf("\nF:");
	atual_professor = inicio_professor;
	while (atual_professor != NULL)
	{
		if (atual_professor->info.sexo[0] == 'F')
			printf("\nmat: %d", atual_professor->info.matricula);
		atual_professor = atual_professor->prox;
	}

	aviso_usuario_l("LISTAGEM POR SEXO FEITA COM SUCESSO");
}

void professor_listar_por_substring (Professor** inicio_professor)
{
	if (*inicio_professor == NULL)
	{
		aviso_usuario_c("NÃO HÁ PROFESSORES CADASTRADOS NO MOMENTO");
		return;
	}

	int i;
	char substring_busca[4];

	printf("\nEntre com a substring de busca: ");
	ler_string_f(substring_busca, 4);

	Professor* atual_professor = *inicio_professor;

	while (atual_professor != NULL)
	{
		for (i = 0; i < 4; i++)
			if (*(substring_busca + i) != *(atual_professor->info.nome + i))
				break;

		if (substring_busca[i] == '\0')
			mostrar_professor(atual_professor);

		atual_professor = atual_professor->prox;
	}

	aviso_usuario_l("LISTAGEM POR CARACTERES INICIAS FEITA");
}

void professor_ordenar_por_nomes (Professor** inicio_professor)
{
	if (*inicio_professor == NULL)
		return;
	else
	{
		int qnt_professors = 0;
		quantidade_professor_lista (*inicio_professor, &qnt_professors);
		Professor novo_arr_professor[qnt_professors];
		Professor professor_aux;
		Professor* professor_atual = *inicio_professor;
		int letra = 0;
		int proxima_letra;
		int i;
		int trocou = 1; 

		for (i = 0; i < qnt_professors && professor_atual != NULL; i++)
		{
			novo_arr_professor[i] = *professor_atual;
			professor_atual = professor_atual->prox;
		}

		while (trocou)
		{
			trocou = 0;
			proxima_letra = 0;
			for (i = 1; i < qnt_professors; i++)
			{
				if (novo_arr_professor[i - 1].info.nome[letra] > novo_arr_professor[i].info.nome[letra])
				{
					professor_aux = novo_arr_professor[i];
					novo_arr_professor[i] = novo_arr_professor[i - 1];
					novo_arr_professor[i - 1] = professor_aux;
					trocou = 1;
				}
				else if (novo_arr_professor[i - 1].info.nome[letra] == novo_arr_professor[i].info.nome[letra])
				{
					do
						proxima_letra++;
					while (novo_arr_professor[i - 1].info.nome[proxima_letra] == novo_arr_professor[i].info.nome[proxima_letra]);

					if (novo_arr_professor[i - 1].info.nome[proxima_letra] > novo_arr_professor[i].info.nome[proxima_letra])
					{
						professor_aux = novo_arr_professor[i];
						novo_arr_professor[i] = novo_arr_professor[i - 1];
						novo_arr_professor[i - 1] = professor_aux;
						trocou = 1;
					}
				}
			}
		}
		for (i = 0; i < qnt_professors; i++)
			mostrar_professor(novo_arr_professor + i);

		aviso_usuario_l("LISTAGEM POR ORDEM ALFABÉTICA FINALIZADA");
	}
}

void professor_listar_aniversariantes (Professor** inicio_professor)
{
	int mes_entrada, mes_teste;
	printf("\nEntre com o mês de aniversário que quer conferir: ");
	ext_ler_int_f(&mes_entrada, 2);
	Professor* atual_professor = *inicio_professor;

	while (atual_professor != NULL)
	{
		ext_string_para_int(&mes_teste, (atual_professor->info.data_nascimento + 3));
		if (mes_entrada == mes_teste)
			mostrar_professor(atual_professor);

		atual_professor = atual_professor->prox;
	}

	aviso_usuario_l("LISTAGEM DOS ANIVERSARIANTES DO MÊS REALIZADA");
}


