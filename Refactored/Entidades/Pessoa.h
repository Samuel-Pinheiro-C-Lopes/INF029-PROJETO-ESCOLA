#ifndef PESSOA_H
#define PESSOA_H

///////////////////////////////////

#include "../Utils/Dependencias.h"

///////////////////////////////////

#pragma region PESSOA

    ///////////////////////////////////

    #pragma region Estrutura

        // Condição de atividade da pessoa cadastrada
        #define ATIVO ('o')
        #define INATIVO ('x')

        // Sexo da pessoa cadatrada
        #define MASC ('M')
        #define FEMI ('F')

        // Estrutura opaca implementada em 'Pessoa.c'
        typedef struct Pessoa Pessoa;

    #pragma endregion

    ///////////////////////////////////

    #pragma region Getters

        int Get_Idade(Pessoa* pessoa);
        char* Get_Nome(Pessoa* pessoa);
        char* Get_Matricula(Pessoa* pessoa);
        char* Get_Data_Nascimento(Pessoa* pessoa);
        char Get_Sexo(Pessoa* pessoa);
        char* Get_CPF(Pessoa* pessoa);
        char Get_Ativo(Pessoa* pessoa);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters

        void Set_Idade(Pessoa* pessoa, int Idade);
        void Set_Nome(Pessoa* pessoa, char* Nome);
        // void Set_Matricula(Pessoa* pessoa, char Matricula[20]);
        // void Set_Data_Nascimento(Pessoa* pessoa, char Data_Nascimento[9]);
        void Set_Sexo(Pessoa* pessoa, char Sexo);
        //void Set_CPF(Pessoa* pessoa, char CPF[12]);
        void Set_Ativo(Pessoa* pessoa, char Ativo);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Base

        Pessoa* P_Construtor (char Matricula[20], char CPF[12], char Data_Nascimento[9], char* Nome, int Idade, char Sexo);

        Pessoa* P_Desconstrutor(Pessoa* Pessoa);

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

#endif