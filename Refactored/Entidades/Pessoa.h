#ifndef PESSOA_H
#define PESSOA_H

///////////////////////////////////

#include "../Utils/Dependencias.h"
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
        typedef int (*Get_Idade_ptr) (Pessoa* pessoa);
        typedef char* (*Get_Nome_ptr) (Pessoa* pessoa);
        typedef char* (*Get_Matricula_ptr) (Pessoa* pessoa);
        typedef char* (*Get_Data_Nascimento_ptr) (Pessoa* pessoa);
        typedef char (*Get_Sexo_ptr) (Pessoa* pessoa);
        typedef char* (*Get_CPF_ptr) (Pessoa* pessoa);
        typedef char (*Get_Ativo_ptr) (Pessoa* pessoa);
        
        // Ponteiros para os setters de Pessoa
        typedef void (*Set_Idade_ptr) (Pessoa* pessoa, int idade);
        typedef void (*Set_Nome_ptr) (Pessoa* pessoa, char* nome);
        typedef void (*Set_Sexo_ptr) (Pessoa* pessoa, char sexo);
        typedef void (*Set_Ativo_ptr) (Pessoa* pessoa, char ativo);

        // implementação pública de Pessoa
        struct pessoa 
        {
            // getters
            Get_Idade_ptr const Get_Idade;
            Get_Nome_ptr const Get_Nome;
            Get_Matricula_ptr const Get_Matricula;
            Get_Data_Nascimento_ptr const Get_Data_Nascimento;
            Get_Sexo_ptr const Get_Sexo;
            Get_CPF_ptr const Get_CPF;
            Get_Ativo_ptr const Get_Ativo;
            
            // setters
            Set_Idade_ptr const Set_Idade;
            Set_Nome_ptr const Set_Nome;
            Set_Sexo_ptr const Set_Sexo;
            Set_Ativo_ptr const Set_Ativo;

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

        // Métodos
        typedef int (*Get_Idade_ptr) (Pessoa* pessoa);
        typedef char* (*Get_Nome_ptr) (Pessoa* pessoa);
        typedef char* (*Get_Matricula_ptr) (Pessoa* pessoa);
        typedef char* (*Get_Data_Nascimento_ptr) (Pessoa* pessoa);
        typedef char (*Get_Sexo_ptr) (Pessoa* pessoa);
        typedef char* (*Get_CPF_ptr) (Pessoa* pessoa);
        typedef char (*Get_Ativo_ptr) (Pessoa* pessoa);

        // Funções fonte
        static int Get_Idade(Pessoa* const pessoa);
        static char* Get_Nome(Pessoa* pessoa);
        static char* Get_Matricula(Pessoa* pessoa);
        static char* Get_Data_Nascimento(Pessoa* pessoa);
        static char Get_Sexo(Pessoa* pessoa);
        static char* Get_CPF(Pessoa* pessoa);
        static char Get_Ativo(Pessoa* const pessoa);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters
        
        // Funções fonte
        static void Set_Idade(Pessoa* pessoa, int idade);
        static void Set_Nome(Pessoa* pessoa, char* nome);
        // void Set_Matricula(Pessoa* pessoa, char Matricula[20]);
        // void Set_Data_Nascimento(Pessoa* pessoa, char Data_Nascimento[9]);
        static void Set_Sexo(Pessoa* pessoa, char sexo);
        //void Set_CPF(Pessoa* pessoa, char CPF[12]);
        static void Set_Ativo(Pessoa* pessoa, char ativo);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Base

        Pessoa* __P_Construtor (char Matricula[20], char CPF[12], char Data_Nascimento[9], char* Nome, int Idade, char Sexo);

        Pessoa* __P_Desconstrutor(Pessoa* Pessoa);

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

#endif