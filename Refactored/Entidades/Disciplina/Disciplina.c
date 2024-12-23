#include "Disciplina.h"

///////////////////////////////////

#pragma region Disciplina

    ///////////////////////////////////

    #pragma region Endereço para métodos

    typedef int (*__D_Get_Tamanho_ptr) (const Disciplina* const disciplina);
    typedef int (*__D_Get_Limite_ptr) (const Disciplina* const disciplina);

    #pragma endregion

    ///////////////////////////////////
    
    #pragma region Estrutura

    struct _disciplina 
    {
        char* Nome;
        char* Codigo;
        char* Semestre;
    };

    struct _dc_professores 
    {
        // métodos
        __D_Get_Limite_ptr Get_Limite;
        __D_Get_Tamanho_ptr Get_Tamanho;
        // propriedades
        char** Mat_Professores;
        int Tamanho;
        int Limite;
    };

    #pragma endregion

    ///////////////////////////////////
    
#pragma endregion

///////////////////////////////////

#pragma region HEADER

    ///////////////////////////////////

    #pragma region Getters

        // PÚBLICOS
        // obtém o nome
        static char* Get_Nome (const Disciplina* const disciplina);
        // obtém o semestre
        static char* Get_Semestre (const Disciplina* const disciplina);
        // obtém o código
        static char* Get_Codigo (const Disciplina* const disciplina);
        // Não há porque obter professores, esses serão manejados por um CRUD de disciplina
        // static char** Get_Professores (const Disciplina* const disciplina);
        // PRIVADOS
        // obtém o tamanho
        static int Get_Tamanho (const Disciplina* const disciplina);
        // obtém o limite
        static int Get_Limite (const Disciplina* const disciplina);
            
    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters

    // define um semestre
    static char* Set_Semestre (Disciplina* const disciplina, char* Nome);
    // define um nome
    static char* Set_Nome (Disciplina* const disciplina, char* Nome);
    // Não faz sentido alterar o código, deverá ser a chave primária imutável de disciplina
    // static char* Set_Codigo (Disciplina* const disciplina, char* Codigo);
    
    #pragma endregion
    
    ///////////////////////////////////
    
    #pragma region CRUD 

    // Aumenta o tamanho atual da coleção
    // Parâmetros: disciplina alvo do incremento
    static void Adc_Tamanho(Disciplina* const disciplina)
    {
        disciplina->_DC_Professores->Tamanho++;
    }

    // Diminui o tamanho atual da coleção
    // Parâmetros: disciplina alvo do decremento
    static void Dim_Tamanho(Disciplina* const disciplina)
    {
        disciplina->_DC_Professores->Tamanho--;
    }

    #pragma endregion

    ///////////////////////////////////
    
    #pragma region Base
    
    static Disciplina* D_Desconstrutor (Disciplina* disciplina);

    #pragma endregion

    ///////////////////////////////////


#pragma endregion

///////////////////////////////////