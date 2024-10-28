#include "Utils.h"

// FUNCIONANDO
void qnt_algarismos_int (int* qnt, int num)
{
	num /= 10;
    *qnt = *qnt + 1;

    if (num == 0)
        return;

    qnt_algarismos_int (qnt, num);
}

// FUNCIONANDO
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

// FUNCIONANDO 
// Transfere o equivalente numérico dos caracteres de uma string para um número
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

// FUNCIONANDO
// Multiplica um número qualquer por outro número uma determinada quantidade de vezes
void multiplicacao_sucessiva (int* num, int mult, int count)
{
    if (count == 0)
		return;

	*num *= mult;

  	multiplicacao_sucessiva(num, mult, count - 1);
}

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
	}

	if (*(string - 1) == 10) // se o char preenchido foi 'enter'
	{
		*(string - 1) = '\0'; // terminador nulo
		return; // fim recursividade
	}

	tam -= sizeof(char); // -1 char em qualquer um dos casos
    ler_string(string, tam); // próximo da cadeia do ponteiro
}

void ler_int (int* num)
{
	scanf(" %d", num);
	while ((getchar()) != '\n');
}

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

void imprimir_campo (char* campo, char* valor)
{
	printf("%s: %s\n", campo, valor);
}

void aviso_usuario (char* string)
{
	printf("%s\n", string);
	printf("Entre com qualquer tecla para continuar...");
	getchar();
}

void receber_matricula (int* num)
{
	printf("Entre com o número de matrícula: ");
	scanf(" %d", num);
	limpar();
}

void limpar (void)
{
	while (getchar() != '\n');
	system("clear");
}


void flush_stdin ()
{
	int c = 'a';
	ungetc(c, stdin);
	while ((c = getchar()) != '\n' && c != EOF);
}

void receber_string (char* string, int tam)
{
	size_t ln;
	fgets(string, tam, stdin);
	ln = strlen(string) - 1;
	if (*(string + ln) == '\n')
		*(string + ln) = '\0';
}

	/*
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


	*/
