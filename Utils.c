#include "Utils.h"

// CONVERSÕES

char* int_para_string (int num)
{
	char* string;
    int qnt = 0;
    qnt_algarismos_int(&qnt, num);

	if (num < 0)
	{
	    string = (char*) malloc((qnt + 2) * sizeof(char));
		*string = '-';
		num *= -1;

		for (int i = 0; i < qnt; i++)
		{
			*((string + 1) + ((qnt - 1) - i)) = (num % 10) + 48;
			num /= 10;
		}

		string[qnt + 1] = '\0';
	}
	else 
	{
		string = (char*) malloc((qnt + 1) * sizeof(char));

		for (int i = 0; i < qnt; i++)
		{
			*(string + ((qnt - 1) - i)) = (num % 10) + 48;
			num /= 10;
		}
		
		string[qnt] = '\0';
	}

    return string;
}

// Transfere o equivalente numérico dos caracteres de uma string para um número (requer que num == 0)
void string_para_int (int* num, char* string)
{
    // caso string esteja no final
    if (*string < 48 || *string > 57)
		return;

	*num *= 10;

	if (*num < 0) // número teve final negativo
		*num -= *(string) - 48;
    else if (*string == '-') // sinal negativo
	{
		string += 1;
        *num -= *(string) - 48;
    }
	else // número é positivo 
		*num += *(string) - 48;

	string_para_int(num, string + 1);
}

// Extensor de string_para_int que inicializa o número para o valor esperado
void ext_string_para_int (int* num, char* string)
{
	*num = 0;

	string_para_int(num, string);
}

// MATH

// Multiplica um número qualquer por outro número uma determinada quantidade de vezes
void multiplicacao_sucessiva (int* num, int mult, int count)
{
    if (count == 0)
		return;

	*num *= mult;

  	multiplicacao_sucessiva(num, mult, count - 1);
}

// Designa a um inteiro de quantidade a quantidade de algarismos de um número inteiro
void qnt_algarismos_int (int* qnt, int num)
{
	num /= 10;
    *qnt = *qnt + 1;

    if (num == 0)
        return;

    qnt_algarismos_int (qnt, num);
}

// SAÍDA

// Imprime n número de linhas
void imprimir_linhas (int num)
{
	if (num <= 0)
	{
		printf("\n");
		return;
	}

	printf("-");

	imprimir_linhas(--num);
}

// imprime um campo no formato "campo: valor"
void imprimir_campo (char* campo, char* valor)
{
	printf("%s: %s\n", campo, valor);
}

// avisa o usuário sem limpar a tela e esperando retorno
void aviso_usuario_l (char* string)
{
	printf("%s\n", string);
	printf("Entre com qualquer tecla para continuar...");
	getchar();
}

// avisa o usuário limpando a tela e esperando retorno
void aviso_usuario_c (char* string)
{
	system("clear");
	printf("%s\n", string);
	printf("Entre com qualquer tecla para continuar...");
	getchar();
}

// INPUT

// Lê uma string sem poluir o buffer (passar tamanho como 'sizeof(string)' preferencialmente)
void ler_string_f (char* string, int tam)
{
	{
		char entrada = getchar(); // Recebe char

		if (entrada == 10) // entrada é 'enter'
		{
			*string = '\0'; // terminador nulo
			return; // fim recursão
		}
		else if (tam > sizeof(char)) // ainda há caracteres para preencher
		{
			*string = entrada; // caracter atual
			string++; // próximo do ponteiro
			tam -= sizeof(char); // -1 caracter para preencher
		}
	}

	ler_string_f (string, tam);
}

// Lê um inteiro com determinado número de casas específicadas sem poluir o buffer
void ler_int_f (int* int_num, int casas)
{
	{
		int temp_char = getchar(); // recebe caracter
		
		if  (temp_char < 48 || temp_char > 57) // entrada não é um número
		{
			if (temp_char == 10) // entrada foi 'enter'
				return; // fim recursão
			else if (temp_char == '-' && casas > 0) // entrada foi '-' e número ainda é 0
			{
				temp_char = getchar();
				if (temp_char >= 48 && temp_char <= 57) // entrada foi um número
				{
					(*int_num) -= (temp_char - 48); // número recebe próximo algarismo como negativo
					casas--; // -1 casa decimal
				}
				else if (temp_char == 10) // entrada foi 'enter'
					return; // fim recursão
			}
		}
		else if (casas > 0) // char é número e ainda há casas
		{
			(*int_num) *= 10; // move algarismos para a esquerda
			(*int_num) += (*int_num) >= 0 ? (temp_char - 48) : ((temp_char - 48) * -1); // preenche novo digito com base no sinal
			casas--; // -1 casa decimal
		}
	}

	ler_int_f (int_num, casas);
}

// Extensor do ler_int_f para ler inteiro e inicializar apropriadamente (int_num = 0)
void ext_ler_int_f (int* int_num, int casas)
{
	*int_num = 0;
	ler_int_f(int_num, casas);
}

// Recebe uma matrícula
void receber_matricula (int* mat)
{
	printf("Entre com o número de matrícula: ");
	ext_ler_int_f(mat, CASAS_INT_GERAL);
}

// Recebe um código
void receber_codigo (int* cod)
{
	printf("Entre com o código da disciplina: ");
	ext_ler_int_f(cod, CASAS_INT_GERAL);
}

void mudar_campo_int (int* campo, char* nome_campo, int casas_campo, int* opcao)
{	
	do
	{
		printf("\nMudar o %s?\n[1 para sim; 0 para não]: ", nome_campo);	
		ext_ler_int_f(opcao, CASAS_INT_MENU);
		if (*opcao == 0)
			return;
	} while (*opcao != 1);

	printf("Entre com o novo %s: ", nome_campo);
	ext_ler_int_f(campo, casas_campo);
}

void mudar_campo_str (char* campo, char* nome_campo, int tamanho_campo, int* opcao)
{
	do
	{
		printf("\nMudar o %s?\n[1 para sim; 0 para não]: ", nome_campo);	
		ext_ler_int_f(opcao, CASAS_INT_MENU);
		if (*opcao == 0)
			return;
	} while (*opcao != 1);

	printf("Entre com o novo %s: ", nome_campo);
	ler_string_f(campo, tamanho_campo);
}

// VALIDAR CPF

int validar_cpf (char* cpf)
{
	int retorno;

	retorno = validar_cpf_formatacao(cpf);
	if (retorno != FORMATACAO_VALIDA)
		return retorno;
	
	retorno = validar_cpf_digitos(cpf);
	if (retorno != DIGITO_VALIDO)
		return retorno;

	return CPF_VALIDO;
}

int validar_cpf_digitos(char* cpf)
{
	int digito_1 = cpf[12] - 48;
	int digito_2 = cpf[13] - 48;
	int soma1 = 0;
	int soma2 = 0;
	int i, j;
	char atual;

	i = 0; j = 0;
	while (*(cpf + i) != '-')
	{
		atual = *(cpf + i);
		if (atual != 46)
			soma1 += (atual - 48) * (++j);
		i++;
	}
	
	if (!(digito_1 == ((soma1 % 11) % 10)))
		return DIGITO_INVALIDO;

	i = 0; j = 0;
	while (*(cpf + i) != '-')
	{
		atual = *(cpf + i);
		if (atual != 46)
			soma2 += (atual - 48) * j++;
		i++;
	}

	soma2 += digito_1 * j;

	if (!(digito_2 == ((soma2 % 11) % 10)))
		return DIGITO_INVALIDO;

	return DIGITO_VALIDO;
}

int validar_cpf_formatacao (char* cpf)
{
	char atual;
	for (int i = 0; *(cpf + i) != '\0'; i++)
	{
		atual = *(cpf + i);
		if (i == 3 || i == 7)
		{
			if (atual !=  '.')
				return FORMATACAO_INVALIDA;
		}
		else if (i == 11)
		{
			if (atual != '-')
				return FORMATACAO_INVALIDA;
		}
		else 
		{
			if (atual > 57 || atual < 48)
				return FORMATACAO_INVALIDA;
		}
	}

	return FORMATACAO_VALIDA;
}

// VALIDAR DATA

int validar_data (char* data)
{
	int retorno;

	retorno = validar_data_formatacao(data);
	if (retorno != FORMATACAO_VALIDA)
		return retorno;

	int dia, mes, ano;
	ext_string_para_int(&dia, data);
	ext_string_para_int(&mes, (data + 3));
	ext_string_para_int(&ano, (data + 6));

	retorno = validar_data_dia(dia, mes, ano);
	if (retorno != DIA_VALIDO)
		return retorno;

	retorno = validar_data_mes(mes);
	if (retorno != MES_VALIDO)
		return retorno;

	return DATA_VALIDA;
}

int validar_data_dia (int dia, int mes, int ano)
{
	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
	{
		if (dia > 31)
			return DIA_INVALIDO;
	}
	else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
	{
		if (dia > 30)
			return DIA_INVALIDO;
	}
	else if (ano % 4 == 0 && ano % 100 != 0)
	{
		if (dia > 29)
			return DIA_INVALIDO;
	}
	else
		if (dia > 28)
			return DIA_INVALIDO;

	return DIA_VALIDO;
}

int validar_data_mes (int mes)
{
	if (mes > 12 || mes < 1)
		return MES_INVALIDO;
	else 
		return MES_VALIDO;
}

int validar_data_formatacao (char* data)
{
	char atual;
	for (int i = 0; *(data + i) != '\0'; i++)
	{
		atual = *(data + i);
		if (i == 2 || i == 5)
		{
			if (atual != '/')
				return FORMATACAO_INVALIDA;
		}
		else if (atual < 48 || atual > 57)
			return FORMATACAO_VALIDA;
	}

	return FORMATACAO_VALIDA;
}

int validar_nome(char* nome)
{
	int i;
	for (i = 0; *(nome + i) != '\0'; i++)
		if (((*(nome + i) < 65 || *(nome + i) > 90) && (*(nome + i) < 97 || *(nome + i) > 122)) || *(nome + i) == 32)
			return FORMATACAO_INVALIDA;

	if (i == 0)
		return FORMATACAO_INVALIDA;

	return FORMATACAO_VALIDA;
}

int validar_sexo(char* sexo)
{
	if (sexo[0] == 'M' || sexo[0] == 'F')
		return FORMATACAO_VALIDA;
	else
		return FORMATACAO_INVALIDA;
}

void verificar_string (char* string_entrada, char* string_verificacao, int* verificacao)
{
	if (*(string_verificacao) == '\0')
		*verificacao = STRING_IGUAL;
	else if (*(string_entrada) == *(string_verificacao))
		verificar_string(string_entrada + 1, string_verificacao + 1, verificacao);
}

// IDENTIDADE 

// Identificadores incrementais
void novo_identificador (int* novo, int* incrementador)
{
	*novo = (++(*incrementador));
}

// Inicializa os incrementos
void inicializar_incrementador (int** identificador)
{
	*identificador = (int*) malloc(sizeof(int));
	*(*identificador) = 0;
}

	/*
	 *
	RASCUNHOS
	if (*num < 0) // número teve final negativo
		*num -= *(string) - 48;
    else if (*string == '-') // sinal negativo
	{
		string += 1;
        *num -= *(string) - 48;
    }
	else // número é positivo 
		*num += *(string) - 48;
	*/


/*
	if(qnt == 0)
	{
		string = (char*) malloc(2 * sizeof(char));
		*string = 0;
		*(string + 1) = '\0';
	}

	*/

/*

	// sinal negativo
	if (*string == '-')
	{
		string += 1;
		//(*num) ^= (1 << (sizeof(int) * CHAR_BIT - 1)); // troca bit mais significativo do int (determina sinal)
		*num += ((*string) - 48) * -1;
	}

	// sobe uma casa decimal para acompanhar as casas do número representado na string
	*num *= 10;

	// se número for positivo 
	// (expressão resultará em 0 caso AND bit a bit no bit mais significativo resulte em desigualdade entre o 1 movido para a casa mais significativa de um inteiro e casa mais significativa de *num, que determina o seu sinal)
	// soma com o equivalente numérico do char atual da string, senão, o número é negativo e deve ser subtraído pelo equivalente
	// numérico do chaN & (1 << (sizeof(int) * CHAR_BIT - 1));r
	*num += ((*num) & (1 << (sizeof(int) * CHAR_BIT - 1))) == 0 ? ((*string) - 48) : ((*string) - 48) * -1;	


// FUNCIONANDO
// Itera uma quantidade de vezes para preencher uma string sem poluir o buffer
void ler_string (char* string, int tam)
{
   	if (tam <= sizeof(char)) // caso tenha excedido o tamanho
	{
		if((getchar()) == 10) // descarta poluição do buffer stdin até encontrar 'enter'
		{
			*string = '\0'; // terminador nulo
			return; // fim recursividade
		}
	}
	else 
	{
    	*string = getchar(); // preenche string
		string++; // próximo char
		tam -= sizeof(char); // -1 char em razão do incremento
	}

	if (*(string - 1) == 10) // se o char preenchido foi 'enter'
	{
		*(string - 1) = '\0'; // terminador nulo
		return; // fim recursividade
	}

    ler_string(string, tam); // próximo da cadeia do ponteiro
}

void ler_int (int* int_num, int casas)
{
	if (casas <= 0)
	{
		if((getchar()) == 10)
		{
			return;
		}
	}
	else
	{
		{
			int temp = (getchar()) - 48;
			if (temp == -38)
				return;
			else
			{
				*int_num *= 10;
				*int_num += temp;
				casas--;
			}
		}
	}

	ler_int (int_num, casas);
}



	*/
