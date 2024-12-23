#ifndef PESSOA_H
#define PESSOA_H

///////////////////////////////////

#include "../../Utils/Dependencias.h"
#include <string.h> // por conta da função memcpy (construtores)

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
        typedef struct pessoa Pessoa; // público
        typedef struct _pessoa _Pessoa; // privado

        // Ponteiros para os getters de Pessoa
        typedef int (*__Get_Idade_ptr) (const Pessoa* const pessoa);
        typedef char* (*__Get_Nome_ptr) (const Pessoa* const pessoa);
        typedef char* (*__Get_Matricula_ptr) (const Pessoa* const pessoa);
        typedef char* (*__Get_Data_Nascimento_ptr) (const Pessoa* const pessoa);
        typedef char (*__Get_Sexo_ptr) (const Pessoa* const pessoa);
        typedef char* (*__Get_CPF_ptr) (const Pessoa* const pessoa);
        typedef char (*__Get_Ativo_ptr) (const Pessoa* const pessoa);
        
        // Ponteiros para os setters de Pessoa
        typedef void (*__Set_Idade_ptr) (Pessoa* const pessoa, int const idade);
        typedef void (*__Set_Nome_ptr) (Pessoa* const pessoa, char* const nome);
        typedef void (*__Set_Sexo_ptr) (Pessoa* const pessoa, char const sexo);
        typedef void (*__Set_Ativo_ptr) (Pessoa* const pessoa, char const ativo);
        
        // Ponteiro para o seu desconstrutor
        typedef Pessoa* (*__P_Desconstrutor_ptr) (Pessoa* pessoa);

        // implementação pública de Pessoa
        struct pessoa 
        {
            // getters
            __Get_Idade_ptr const Get_Idade;
            __Get_Nome_ptr const Get_Nome;
            __Get_Matricula_ptr const Get_Matricula;
            __Get_Data_Nascimento_ptr const Get_Data_Nascimento;
            __Get_Sexo_ptr const Get_Sexo;
            __Get_CPF_ptr const Get_CPF;
            __Get_Ativo_ptr const Get_Ativo;
            
            // setters
            __Set_Idade_ptr const Set_Idade;
            __Set_Nome_ptr const Set_Nome;
            __Set_Sexo_ptr const Set_Sexo;
            __Set_Ativo_ptr const Set_Ativo;
            
            // desconstrutor
            __P_Desconstrutor_ptr Desconstrutor;

            // privado
            _Pessoa* const _Pessoa; 
        };
        // nota: uso de const para não permitir alteração nos ponteiros
        // uma vez que sejam designados pelo construtor

    #pragma endregion
        
    #pragma region Métodos
        

    #pragma endregion

    ///////////////////////////////////

    #pragma region Getters

        // Funções fonte
        // static int Get_Idade(const Pessoa* const pessoa);
        // static char* Get_Nome(const Pessoa* const pessoa);
        // static char* Get_Matricula(const Pessoa* const pessoa);
        // static char* Get_Data_Nascimento(const Pessoa* const pessoa);
        // static char Get_Sexo(const Pessoa* const pessoa);
        // static char* Get_CPF(const Pessoa* const pessoa);
        // static char Get_Ativo(const Pessoa* const pessoa);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters
        
        // Funções fonte
        // static void Set_Idade(Pessoa* const pessoa, int const idade);
        // static void Set_Nome(Pessoa* const pessoa, char* const nome);
        // // void Set_Matricula(Pessoa* pessoa, char Matricula[20]);
        // // void Set_Data_Nascimento(Pessoa* pessoa, char Data_Nascimento[9]);
        // static void Set_Sexo(Pessoa* const pessoa, char const sexo);
        // //void Set_CPF(Pessoa* pessoa, char CPF[12]);
        // static void Set_Ativo(Pessoa* const pessoa, char const ativo);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Base

        Pessoa* P_Construtor (char Matricula[20], char CPF[12], char Data_Nascimento[9], char* Nome, int Idade, char Sexo);

        //Pessoa* P_Desconstrutor(Pessoa* Pessoa);

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

#endif