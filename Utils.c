#include "Utils.h"

// FUNCIONANDO
void qnt_algarismos_int (int* qnt, int num)
{
    if (num == 0)
        return;

    int novo_num;
    novo_num = num/10;
    *qnt = *qnt + 1;

    qnt_algarismos_int (qnt, novo_num);
}

// FUNCIONANDO
char* int_para_string (int num)
{
	char* string;
    int qnt = 0;
    qnt_algarismos_int(&qnt, num);
	printf("\nQnt algatismos: %d\n", qnt);

	if(qnt == 0)
	{
		string = (char*) malloc(2 * sizeof(char));
		*string = 0;
		*(string + 1) = '\0';
	}
	else if(num < 0)
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
    if (*string == '\0')
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
// Itera uma quantidade de vezes para preencher uma string
void ler_string (char* string, int tam)
{
    if (tam <= 1)
    {
        *string = '\0';
        return;
    }

    *string = getchar();

    if (*string == 10)
    {
        *string = '\0';
        return;
    }

    ler_string(string + 1, --tam);
}
