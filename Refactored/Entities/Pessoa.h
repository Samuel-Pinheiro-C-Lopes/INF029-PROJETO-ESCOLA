#ifndef PESSOA_H
#define PESSOA_H

#include "../Utils/Dependecies.h"

#pragma region Estrutura

typedef struct pessoa Pessoa;

#pragma endregion

#pragma region Sobrecarga

/*
#define Idade(_1, ...) _Generic((_1),                               \
                            Pessoa*: g_Idade,                       \
                            int: _Generic((FIRST(__VA_ARGS__,)),    \
                                Pessoa*: s_Idade))(_1, __VA_ARGS__)
*/

// Para o número variado de argumentos...
/*
#define Idade(...) SELECT(__VA_ARGS__)(__VA_ARGS__)

#define SELECT(...) CONCAT(SELECT_, NARG(__VA_ARGS__))(__VA_ARGS__)
#define CONCAT(X, Y) CONCAT_(X, Y)
#define CONCAT_(X, Y) X ## Y
*/

// Função para cada tipo de chamada

#define Idade(N, ...) \
    _Generic((N),   \
        Pessoa*: g_Idade, \
        int: _Generic((FIRST(__VA_ARGS__,)), \
            Pessoa*: s_Idade)) (N, __VA_ARGS__) \
        

#define FIRST(A, ...) A

/*

#define Idade(N, ...) \
                _Generic((N), \
                    Pessoa*: g_Idade \
                    int: _Generic((M), \
                        Pessoa*: s_Idade) ( (M) )) ( (N) )
*/
/*
#define Idade(_1) _Generic ((_1), \
                    Pessoa*: g_Idade)

#define Idade(_1, _2) _Generic((_1), \
                    int: _Generic((_2), \
                        Pessoa*: s_Idade))
                        */

#pragma endregion

#pragma region Getters

int g_Idade(Pessoa* pessoa);
int* g_Matricula(Pessoa* pessoa);
int* g_Data_Nascimento(Pessoa* pessoa);
char g_Sexo(Pessoa* pessoa);
int* g_CPF(Pessoa* pessoa);

#pragma endregion

void s_Idade(Pessoa* pessoa, int Idade);
void s_Matricula(Pessoa* pessoa, int Idade[]);
void s_Data_Nascimento(Pessoa* pessoa, int Data_Nascimento[]);
void s_Sexo(Pessoa* pessoa, char Sexo);
void s_CPF(Pessoa* pessoa, int CPF[]);

#pragma region Setters

#pragma endregion

#pragma region Base

Pessoa* PConstructor(char Matricula[20], 
char Data_Nascimento[9], char CPF[12], int Idade, char Sexo);

Pessoa* PDeconstructor(Pessoa* Pessoa);

#pragma endregion

#endif