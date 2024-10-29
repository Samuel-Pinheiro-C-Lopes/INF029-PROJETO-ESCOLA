#include "Professor.h"
#include "Utils.h"


void main_professor (Professor** inicio_professor, Aluno** inicio_aluno, int* matricula_professor_incr, int* opcao)
{
	int mat;
	do 
	{
		menu_Professor(opcao);
		system("clear");
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
					listar_professores(*inicio_professor);
					aviso_usuario_l("LISTAGEM REALIZADA COM SUCESSO!");
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

	if (validar_data(nova_info_professor.data_nascimento) == DATA_INVALIDA)
		retorno = DATA_INVALIDA;
	else if (validar_cpf(nova_info_professor.cpf) == CPF_INVALIDO)
		retorno = CPF_INVALIDO;
	else if (validar_nome(nova_info_professor.nome) == FORMATACAO_INVALIDA)
		retorno = FORMATACAO_INVALIDA;
	else if (validar_sexo(nova_info_professor.sexo) == FORMATACAO_INVALIDA)
		retorno = FORMATACAO_INVALIDA;
	else if (tem_cpf == CPF_ENCONTRADO)
		retorno = CPF_ENCONTRADO;
	
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


