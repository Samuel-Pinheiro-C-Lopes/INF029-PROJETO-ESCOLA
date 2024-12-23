#ifndef DISCIPLINA_H
#define DISCIPLINA_H

///////////////////////////////////

#include "../../Utils/Dependencias.h"
#include <string.h> // memcpy

///////////////////////////////////

#pragma region Disciplina

    ///////////////////////////////////

    #pragma region Tipo Estrutura

        typedef struct disciplina Disciplina; // público
        typedef struct _disciplina _Disciplina; // privado
        typedef struct _dc_professores _DC_Professores; // coleção de professores
                                            
    #pragma endregion
    
    ///////////////////////////////////
    
    #pragma region Endereços para os métodos
        
        ///////////////////////////////////
        
        #pragma region Getters
        
        typedef char* (*__D_Get_Codigo_ptr) (const Disciplina* const disciplina);
        typedef char* (*__D_Get_Nome_ptr) (const Disciplina* const disciplina);
        typedef char* (*__D_Get_Semestre_ptr) (const Disciplina* const disciplina);
        // typedef char** (*Get_Professores_ptr) (const Disciplina* const disciplina);

        #pragma endregion

        ///////////////////////////////////

        #pragma region Setters
        
        typedef void (*__D_Set_Nome_ptr) (Disciplina* const disciplina, char* nome);
        typedef void (*__D_Set_Semestre_ptr) (Disciplina* const disciplina, char* semestre);
        // Não faz sentido, visto que código será chave primária imutável de disciplina
        // typedef void (*Set_Codigo) (Disciplina* const disciplina, char* codigo);

        #pragma endregion
        
        ///////////////////////////////////

    #pragma endregion                                             

    ///////////////////////////////////
    
    #pragma region Estrutura 

    struct disciplina 
    {
        // PÚBLICO
        // Getters
        __D_Get_Codigo_ptr Get_Codigo;
        __D_Get_Nome_ptr Get_Nome;
        __D_Get_Semestre_ptr Get_Semestre;
        // Setters
        __D_Set_Semestre_ptr Set_Semestre;
        __D_Set_Nome_ptr Set_Nome;
        // PRIVADO
        _Disciplina* _Disciplina;
        // COLEÇÃO PROFESSORES
        _DC_Professores* _DC_Professores;
    };

    #pragma endregion

    ///////////////////////////////////
    
    #pragma region Base 

    Disciplina* D_Construtor (char* codigo, char* disciplina, char* nome);

    // static Disciplina* D_Desconstrutor (Disciplina* disciplina);

    #pragma endregion
    
#pragma endregion

///////////////////////////////////

#endif