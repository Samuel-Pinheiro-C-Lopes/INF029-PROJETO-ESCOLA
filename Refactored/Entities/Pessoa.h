#ifndef PESSOA_H
#define PESSOA_H

#include "../Utils/Dependencias.h"

#pragma region Estrutura

typedef struct pessoa Pessoa;

#pragma endregion

#pragma region Getters

int Get_Idade(Pessoa* pessoa);
char* Get_Matricula(Pessoa* pessoa);
char* Get_Data_Nascimento(Pessoa* pessoa);
char Get_Sexo(Pessoa* pessoa);
char* Get_CPF(Pessoa* pessoa);

#pragma endregion

#pragma region Setters

void Set_Idade(Pessoa* pessoa, int Idade);
void Set_Matricula(Pessoa* pessoa, char Matricula[]);
void Set_Data_Nascimento(Pessoa* pessoa, char Data_Nascimento[]);
void Set_Sexo(Pessoa* pessoa, char Sexo);
void Set_CPF(Pessoa* pessoa, char CPF[]);

#pragma endregion

#pragma region Base

Pessoa* PConstructor(char Matricula[20], 
char Data_Nascimento[9], char CPF[12], int Idade, char Sexo);

Pessoa* PDeconstructor(Pessoa* Pessoa);

#pragma endregion

#endif