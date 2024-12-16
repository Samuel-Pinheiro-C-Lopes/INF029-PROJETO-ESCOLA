#ifndef PESSOA_H
#define PESSOA_H

///////////////////////////////////

#include "../Utils/Dependencias.h"

///////////////////////////////////

#pragma region PESSOA

    ///////////////////////////////////

    #pragma region Estrutura

        #define ATIVO ('o')
        #define INATIVO ('x')

        typedef struct pessoa Pessoa;

    #pragma endregion

    ///////////////////////////////////

    #pragma region Getters

        int Get_Idade(Pessoa* pessoa);
        char* Get_Matricula(Pessoa* pessoa);
        char* Get_Data_Nascimento(Pessoa* pessoa);
        char Get_Sexo(Pessoa* pessoa);
        char* Get_CPF(Pessoa* pessoa);
        char Get_Ativo(Pessoa* pessoa);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters

        void Set_Idade(Pessoa* pessoa, int Idade);
        void Set_Matricula(Pessoa* pessoa, char Matricula[20]);
        void Set_Data_Nascimento(Pessoa* pessoa, char Data_Nascimento[9]);
        void Set_Sexo(Pessoa* pessoa, char Sexo);
        void Set_CPF(Pessoa* pessoa, char CPF[12]);
        void Set_Ativo(Pessoa* pessoa, char Ativo);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Base

        Pessoa* P_Constructor (char Matricula[20], char CPF[12], char Data_Nascimento[9], char Funcao, char* Nome, int Idade, char Sexo);

        Pessoa* P_Deconstructor(Pessoa* Pessoa);

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

#pragma region COLECAO DE PESSOAS

    ///////////////////////////////////

    #pragma region Estrutura

        #define ALUNO ('A')
        #define PROFESSOR ('P')

        typedef struct c_pessoas C_Pessoas;

    #pragma endregion

    ///////////////////////////////////

    #pragma region Getters 

    Pessoa* Get_Pessoas(C_Pessoas* colecao); 
    char Get_Funcao(C_Pessoas* colecao);
    int Get_Tamanho(C_Pessoas* colecao);
    int Get_Limite(C_Pessoas* colecao);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters

    // Não há porque definir setters para esta coleção...

    #pragma endregion

    ///////////////////////////////////

    #pragma region CRUD em tempo de execução

    void Adc_Tamanho(C_Pessoas* colecao);
    void Dim_Tamanho(C_Pessoas* colecao);
    void Adc_Pessoa(C_Pessoas* colecao, Pessoa pessoa);
    void Alt_Pessoa(C_Pessoas* colecao, Pessoa pessoa);
    Pessoa* Busc_Pessoa(C_Pessoas* colecao, char* Matricula);
    void Rem_Pessoa(C_Pessoas* colecao, char* Matricula);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Base

        C_Pessoas* PC_Construtor(Pessoa* Pessoas, char Funcao);

        C_Pessoas* PC_Desconstrutor(C_Pessoas* colecao);

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

#endif