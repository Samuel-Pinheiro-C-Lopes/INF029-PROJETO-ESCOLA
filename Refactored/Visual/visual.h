#ifndef VISUAL_H
#define VISUAL_H

#include "../Entidades/ColecaoPessoa.h"

///////////////////////////////////

#pragma region Estrutura

    // estrutura que irá manejar a interface do usuário e a sua comunicação 
    // com as entidades do programa
    typedef struct visual Visual; // público
    typedef struct _visual _Visual; // privado
    // módulos
    typedef struct _aluno _Aluno; 
    typedef struct _professor _Professor;
    typedef struct _disciplina _Disciplina;
    
    // Ponteiros para os métodos públicos de visual

    // público
    struct visual 
    {
        _Visual* _Visual; // privado
    };

#pragma endregion

///////////////////////////////////

#pragma region Getters

    // 

#pragma endregion

///////////////////////////////////

#pragma region Base 

    Visual* V_Construtor();

#pragma endregion
    
#endif