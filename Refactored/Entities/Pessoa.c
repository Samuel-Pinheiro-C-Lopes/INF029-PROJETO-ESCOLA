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

///////////////////////////////////

#pragma region Getters
// Obtém propriedades encapsuladas de pessoa

int Get_Idade(Pessoa* pessoa)
{
    return pessoa->Idade;
}

char* Get_Matricula(Pessoa* pessoa)
{
    return pessoa->Matricula;
}

char* Get_Data_Nascimento(Pessoa* pessoa)
{
    return pessoa->Data_Nascimento;
}

char Get_Sexo(Pessoa* pessoa)
{
    return pessoa->Sexo;
}

char* Get_CPF(Pessoa* pessoa)
{
    return pessoa->CPF;
}

#pragma endregion

///////////////////////////////////

#pragma region Setters
// Definem propriedades encapsuladas de pessoa

void s_Idade(Pessoa *pessoa, int Idade)
{
    pessoa->Idade = Idade;
}

void Set_Matricula(Pessoa* pessoa, char Matricula[20])
{
    pessoa->Matricula = Matricula;
}

void Set_Data_Nascimento(Pessoa* pessoa, char Data_Nascimento[9])
{
    pessoa->Data_Nascimento = Data_Nascimento;
}

void Set_Sexo(Pessoa* pessoa, char Sexo)
{
    pessoa->Sexo = Sexo;
}

void Set_CPF(Pessoa* pessoa, char CPF[])
{
    pessoa->CPF = CPF;
}

#pragma endregion

///////////////////////////////////

#pragma region Base
// Construtor e desconstrutor

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