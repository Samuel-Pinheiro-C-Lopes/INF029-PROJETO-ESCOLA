#ifndef ALUNO_H
#define ALUNO_H

///////////////////////////////////

#ifndef PESSOA_H
#include "Pessoa.h"
#endif

///////////////////////////////////

#pragma region Aluno

    ///////////////////////////////////

    #pragma region Estrutura

        typedef struct aluno Aluno;

    #pragma endregion
    
    ///////////////////////////////////

    #pragma region Getters

        Pessoa* Get_Pessoa (Aluno* aluno);

    #pragma endregion 

    ///////////////////////////////////

    #pragma region Setters

        void Set_Pessoa (Aluno* aluno, Pessoa* pessoa);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Base

        Aluno* AConstrutor(Pessoa* pessoa);

        Aluno* ADesconstrutor(Aluno* aluno);

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

///////////////////////////////////

#pragma region Coleção

    ///////////////////////////////////

    typedef struct alunoColecao Alunos;

    ///////////////////////////////////

    #pragma region Getters 

    Aluno* Get_Alunos(Alunos* colecao); 

    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters

    void Set_Alunos(Alunos* colecao, Aluno* alunos);

    #pragma endregion

    ///////////////////////////////////

    #pragma region CRUD em tempo de execução

    int AdicionarAluno(Alunos* colecao, Aluno* aluno);
    int RemoverAluno(Alunos* colecao, char Matricula[20]);
    int BuscarAluno(Alunos* colecao, char Matricula[20]);
    int AlterarAluno(Alunos* colecao, Aluno* aluno);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Base

        Alunos* AcConstrutor();

        Alunos* AcDesconstrutor(Alunos* colecao);

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

///////////////////////////////////

#endif