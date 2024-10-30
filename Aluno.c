#include "Aluno.h"
#include "Utils.h"


void main_aluno (Aluno **inicio_aluno, Professor** inicio_professor, int* matricula_aluno_incr, int* opcao)
{
	int mat;
	do 
	{
		menu_Aluno(opcao);
		system("clear");
		switch (*opcao * -1)
		{
			case (-8):
			{
				ordenar_por_nomes(inicio_aluno);
				getchar();
				break;
			}
			case (OPCAO_CADASTRAR):
			{
				switch (cadastrar_aluno(inicio_aluno, inicio_professor, matricula_aluno_incr))
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

int cadastrar_aluno (Aluno** inicio_aluno, Professor** inicio_professor, int* matricula_aluno_incr)
{
	Info_Aluno nova_info_aluno;
	int retorno = INFO_VALIDA;
	
	do
	{
		imprimir_linhas(NUM_LINHAS);
		printf("\nEntre com o nome do aluno: ");
		ler_string_f(nova_info_aluno.nome, 50);
		printf("\nEntre com o cpf do aluno (Formato: [xxx.xxx.xxx-xx]): ");
		ler_string_f(nova_info_aluno.cpf, 15);
		printf("\nEntre com a data de nascimento do aluno (Formato: [dd/mm/yyyy]): ");
		ler_string_f(nova_info_aluno.data_nascimento, 11);
		printf("\nEntre com o sexo do aluno [M ou F]: ");
		ler_string_f(nova_info_aluno.sexo, 2);
		imprimir_linhas(NUM_LINHAS);

		retorno = INFO_VALIDA; // validar_info_aluno(inicio_aluno, inicio_professor, nova_info_aluno);

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
 		novo_identificador((&nova_info_aluno.matricula), matricula_aluno_incr);
		if (inserir_aluno (inicio_aluno, nova_info_aluno) == INSERCAO_SUCESSO)	
			return CADASTRO_SUCESSO;
	}
	
	return CADASTRO_FRACASSO;
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


void verificar_alunos_cpf (Aluno* aluno_atual, int* tem_cpf, char* cpf)
{
	printf("\nENTREI AQUI\n");	
	getchar();
	if (aluno_atual == NULL)
		return;
	else
		verificar_string(cpf, aluno_atual->info.cpf, tem_cpf);

	if (*tem_cpf != CPF_ENCONTRADO)
		verificar_alunos_cpf(aluno_atual->prox, tem_cpf, cpf);
}

int validar_info_aluno(Aluno** inicio_aluno, Professor** inicio_professor, Info_Aluno nova_info_aluno)
{
	int retorno = INFO_VALIDA;
	int tem_cpf = CPF_NAO_ENCONTRADO;
	verificar_alunos_cpf(*inicio_aluno, &tem_cpf, nova_info_aluno.cpf);

	if (validar_data(nova_info_aluno.data_nascimento) != DATA_VALIDA)
		retorno = DATA_INVALIDA;
	else if (validar_cpf(nova_info_aluno.cpf) != CPF_VALIDO)
		retorno = CPF_INVALIDO;
	else if (validar_nome(nova_info_aluno.nome) != FORMATACAO_VALIDA)
		retorno = FORMATACAO_INVALIDA;
	else if (validar_sexo(nova_info_aluno.sexo) != FORMATACAO_VALIDA)
		retorno = FORMATACAO_INVALIDA;
	else if (tem_cpf != CPF_NAO_ENCONTRADO)
		retorno = CPF_ENCONTRADO;

	tem_cpf = CPF_NAO_ENCONTRADO;
	verificar_professores_cpf(*inicio_professor, &tem_cpf, nova_info_aluno.cpf);
	if (tem_cpf != CPF_NAO_ENCONTRADO)
		retorno = CPF_ENCONTRADO;

	return retorno;
}

void quantidade_aluno_lista (Aluno* atual_aluno, int* qnt)
{
	if (atual_aluno == NULL)
		return;
	else
	{
		*qnt += 1;
		quantidade_aluno_lista (atual_aluno->prox, qnt);
	}
}

float valor_data (char* data)
{ 
	int dia;
	int mes;
	int ano;	

	ext_string_para_int(&dia, data);
	ext_string_para_int(&mes, (data + 3));
	ext_string_para_int(&ano, (data + 6));

	return (float) (dia + (ano * 365) + (mes * 30));
}

void listar_por_data (Aluno** inicio_aluno)
{
	int qnt_alunos = 0;
	quantidade_aluno_lista (*inicio_aluno, &qnt_alunos);
	Aluno aluno_arr[qnt_alunos];
	Aluno novo_aluno_arr[qnt_alunos];
	Aluno* aluno_atual = *inicio_aluno;
	Aluno aluno_aux;
	int trocou, i;
	int valor_data_atl, valor_data_ant;

	// preenche aluno_arr com os alunos da lista
	for (i = 0; i < qnt_alunos && aluno_atual != NULL; i++)
	{
		aluno_arr[i] = *aluno_atual;
		aluno_atual = aluno_atual->prox;
	}

	// preenche novo_aluno_arr com o conteúdo de aluno_arr
	for (i = 0; i < qnt_alunos; i++)
		novo_aluno_arr[i] = aluno_arr[i];
	
	do
	{
		trocou = 0;
		for (i = 1; i < qnt_alunos; i++)
		{
			valor_data_ant = valor_data(novo_aluno_arr[i - 1].info.data_nascimento);
			valor_data_atl = valor_data(novo_aluno_arr[i].info.data_nascimento); 
			if (valor_data_ant > valor_data_atl)
			{
				aluno_aux = novo_aluno_arr[i];
				novo_aluno_arr[i] = novo_aluno_arr[i - 1];
				novo_aluno_arr[i - 1] = aluno_aux;
				trocou = 1;
			}
		}
	} while (trocou);

	for (i = 0; i < qnt_alunos; i++)
		printf("aluno: %s, \n data: %s\n", novo_aluno_arr[i].info.nome, novo_aluno_arr[i].info.data_nascimento);

}

void listar_por_sexo (Aluno* inicio_aluno)
{
	printf("\nM:");
	Aluno* atual_aluno = inicio_aluno;
	while (atual_aluno != NULL)
	{
		if (atual_aluno->info.sexo[0] == 'M')
			printf("\nmat: %d", atual_aluno->info.matricula);
		atual_aluno = atual_aluno->prox;
	}
	printf("\nF:");
	atual_aluno = inicio_aluno;
	while (atual_aluno != NULL)
	{
		if (atual_aluno->info.sexo[0] == 'F')
			printf("\nmat: %d", atual_aluno->info.matricula);
		atual_aluno = atual_aluno->prox;
	}

}

void listar_por_substring (Aluno** inicio_aluno)
{
	int i;
	char substring_busca[4];

	printf("\nEntre com a substring de busca: ");
	ler_string_f(substring_busca, 4);

	Aluno* atual_aluno = *inicio_aluno;

	while (atual_aluno != NULL)
	{
		for (i = 0; i < 4; i++)
			if (*(substring_busca + i) != *(atual_aluno->info.nome + i))
				break;

		if (substring_busca[i] == '\0')
			mostrar_aluno(atual_aluno);

		atual_aluno = atual_aluno->prox;
	}
}

void ordenar_por_nomes (Aluno** inicio_aluno)
{
	if (*inicio_aluno == NULL)
		return;
	else
	{
		int qnt_alunos = 0;
		quantidade_aluno_lista (*inicio_aluno, &qnt_alunos);
		Aluno novo_arr_aluno[qnt_alunos];
		Aluno aluno_aux;
		Aluno* aluno_atual = *inicio_aluno;
		int letra = 0;
		int proxima_letra;
		int i;
		int trocou = 1; 

		for (i = 0; i < qnt_alunos && aluno_atual != NULL; i++)
		{
			novo_arr_aluno[i] = *aluno_atual;
			aluno_atual = aluno_atual->prox;
		}

		while (trocou)
		{
			trocou = 0;
			proxima_letra = 0;
			for (i = 1; i < qnt_alunos; i++)
			{
				if (novo_arr_aluno[i - 1].info.nome[letra] > novo_arr_aluno[i].info.nome[letra])
				{
					aluno_aux = novo_arr_aluno[i];
					novo_arr_aluno[i] = novo_arr_aluno[i - 1];
					novo_arr_aluno[i - 1] = aluno_aux;
					trocou = 1;
				}
				else if (novo_arr_aluno[i - 1].info.nome[letra] == novo_arr_aluno[i].info.nome[letra])
				{
					do
						proxima_letra++;
					while (novo_arr_aluno[i - 1].info.nome[proxima_letra] == novo_arr_aluno[i].info.nome[proxima_letra]);

					if (novo_arr_aluno[i - 1].info.nome[proxima_letra] > novo_arr_aluno[i].info.nome[proxima_letra])
					{
						aluno_aux = novo_arr_aluno[i];
						novo_arr_aluno[i] = novo_arr_aluno[i - 1];
						novo_arr_aluno[i - 1] = aluno_aux;
						trocou = 1;
					}
				}
			}
		}
		for (i = 0; i < qnt_alunos; i++)
			mostrar_aluno(novo_arr_aluno + i);

		aviso_usuario_l("LISTAGEM POR ORDEM ALFABÉTICA FINALIZADA");
	}
}

void listar_aniversariantes (Aluno** inicio_aluno)
{
	int mes;
	printf("\nEntre com o mês de aniversário que quer conferir: ");
	ext_ler_int_f(&mes, 2);

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
