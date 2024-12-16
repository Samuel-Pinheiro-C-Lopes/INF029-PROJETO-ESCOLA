#include "Pessoa.h"
#include <stdlib.h>

#pragma region Estrutura

struct pessoa 
{
    char* Matricula;
    int Idade;
    char Sexo;
    char* Data_Nascimento;
    char* CPF;
};

#pragma endregion

#pragma region Getters / Setters

int g_Idade(Pessoa* pessoa)
{
    return pessoa->Idade;
}

void s_Idade(Pessoa *pessoa, int Idade)
{
    pessoa->Idade = Idade;
}

#pragma endregion

#pragma region Base

// Cria pessoa e retorna o seu ponteiro
Pessoa* PConstructor (char Matricula[20], 
char Data_Nascimento[9], char CPF[12], int Idade, char Sexo)
{
    Pessoa* P = (Pessoa*) malloc(sizeof(Pessoa));

    P->Matricula = Matricula;
    P->Data_Nascimento = Data_Nascimento;
    P->CPF = CPF;
    P->Idade = Idade;
    P->Sexo = Sexo;

    return P;
}

// Libera pessoa
Pessoa* PDeconstructor (Pessoa* pessoa)
{
    free(pessoa);
    return NULL;
}

#pragma endregion