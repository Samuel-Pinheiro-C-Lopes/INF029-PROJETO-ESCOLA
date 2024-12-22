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

        typedef struct c_pessoas C_Pessoas; // membros públicos
        typedef struct _c_pessoas _C_Pessoas; // membros privados

        // Ponteiros para os métodos da estrutura
        
        // getters
        typedef char (*__Get_Funcao_ptr) (const C_Pessoas* const colecao);
        typedef int (*__Get_Tamanho_ptr) (const C_Pessoas* const colecao);
        typedef int (*__Get_Limite_ptr) (const C_Pessoas* const colecao);

        // CRUD
        typedef void (*__Adc_Tamanho_ptr) (C_Pessoas* const colecao);
        typedef void (*__Dim_Tamanho_ptr) (C_Pessoas* const colecao);
        typedef void (*__Adc_Pessoa_ptr) (C_Pessoas* const colecao, Pessoa* const pessoa);
        typedef void (*__Alt_Pessoa_ptr) (C_Pessoas* const colecao, Pessoa* const pessoa);
        typedef Pessoa* (*__Busc_Pessoa_ptr) (C_Pessoas* const colecao, char* const Matricula);
        typedef void (*__Rem_Pessoa_ptr) (C_Pessoas* const colecao, char* const Matricula);
        
        // desconstrutor
        typedef C_Pessoas* (*__PC_Desconstrutor_ptr) (C_Pessoas* colecao);

        // membros públicos
        struct c_pessoas
        {
            // getters
            __Get_Funcao_ptr const Get_Funcao;
            __Get_Tamanho_ptr const Get_Tamanho;
            __Get_Limite_ptr const Get_Limite;
            
            // CRUD
            __Adc_Tamanho_ptr const  Adc_Tamanho;
            __Dim_Tamanho_ptr const  Dim_Tamanho;
            __Adc_Pessoa_ptr const  Adc_Pessoa;
            __Alt_Pessoa_ptr const  Alt_Pessoa;
            __Busc_Pessoa_ptr const  Busc_Pessoa;
            __Rem_Pessoa_ptr const  Rem_Pessoa; 
            
            // desconstrutor
            __PC_Desconstrutor_ptr Desconstrutor;

            // privado
            _C_Pessoas* const _C_Pessoas;
        };
                                    
        // ponteiros para os getters

    #pragma endregion

    ///////////////////////////////////

    #pragma region Getters 
        

    // ponteiros e struturas passadas não devem mudar no escopo de execução das funções
    //Pessoa** Get_Pessoas(C_Pessoas* colecao); 
    // static char Get_Funcao(const C_Pessoas* const colecao);
    // static int Get_Tamanho(const C_Pessoas* const colecao);
    // static int Get_Limite(const C_Pessoas* const colecao);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters

    // Não há porque definir setters para esta coleção...

    #pragma endregion

    ///////////////////////////////////

    #pragma region CRUD em tempo de execução
    

    // ponteiros não devem mudar no escopo de execução das funções, tampouco as entradas
    // para inserção, alteração, busca e remoção
    //static void Adc_Tamanho(C_Pessoas* const colecao);
    //static void Dim_Tamanho(C_Pessoas* const colecao);
    //static void Adc_Pessoa(C_Pessoas* const colecao, Pessoa* const pessoa);
    //static void Alt_Pessoa(C_Pessoas* const colecao, Pessoa* const pessoa);
    //static Pessoa* Busc_Pessoa(C_Pessoas* const colecao, char* const Matricula);
    //static void Rem_Pessoa(C_Pessoas* const colecao, char* const Matricula);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Base

        C_Pessoas* PC_Construtor(Pessoa* const Pessoas, const char Funcao);

        //static C_Pessoas* PC_Desconstrutor(C_Pessoas* colecao);

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

#endif