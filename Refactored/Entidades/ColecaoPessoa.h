#ifndef COLECAO_P_H
#define COLECAO_P_H

///////////////////////////////////

#include "Pessoa.h"

///////////////////////////////////

#pragma region COLECAO DE PESSOAS

    ///////////////////////////////////

    #pragma region Estrutura

        #define ALUNO ('A')
        #define PROFESSOR ('P')

        #define MAX_INI (8)

        typedef struct c_pessoas C_Pessoas;

    #pragma endregion

    ///////////////////////////////////

    #pragma region Getters 

    //Pessoa** Get_Pessoas(C_Pessoas* colecao); 
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
    void Adc_Pessoa(C_Pessoas* colecao, Pessoa* pessoa);
    void Alt_Pessoa(C_Pessoas* colecao, Pessoa* pessoa);
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