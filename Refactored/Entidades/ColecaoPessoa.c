#include "ColecaoPessoa.h"
#include <string.h>

///////////////////////////////////

#pragma region COLEÇÃO

///////////////////////////////////

#pragma region Estrutura

// Estrutura que representa a coleção
struct _c_pessoas
{
    Pessoa** pessoas;
    char Funcao;
    int Tamanho;
    int Limite;
};

#pragma endregion

///////////////////////////////////

#pragma region HEADER

    ///////////////////////////////////

    #pragma region Getters

        static char Get_Funcao(const C_Pessoas* const colecao);
        static int Get_Tamanho(const C_Pessoas* const colecao);
        static int Get_Limite(const C_Pessoas* const colecao);

    #pragma endregion
    
    ///////////////////////////////////

    #pragma region CRUD

        static void Adc_Tamanho(C_Pessoas* const colecao);
        static void Dim_Tamanho(C_Pessoas* const colecao);
        static void Adc_Pessoa(C_Pessoas* const colecao, Pessoa* const pessoa);
        static void Alt_Pessoa(C_Pessoas* const colecao, Pessoa* const pessoa);
        static Pessoa* Busc_Pessoa(C_Pessoas* const colecao, char* const Matricula);
        static void Rem_Pessoa(C_Pessoas* const colecao, char* const Matricula);

    #pragma endregion
    
    ///////////////////////////////////
    
    #pragma region Base 
        
        static C_Pessoas* PC_Desconstrutor(C_Pessoas* colecao);

    #pragma endregion
    
    ///////////////////////////////////

#pragma endregion

///////////////////////////////////

#pragma region Getters 

    // obtém o endereço do vetor de pessoas - elemento [0]
    // Não há porque obter a referência do início da base de dados da coleção
    /*
    Pessoa** Get_Pessoas(C_Pessoas* colecao)
    {
        return colecao->pessoas;
    }
    */

    // obtém função
    static char Get_Funcao(const C_Pessoas* const colecao)
    {
        return colecao->_C_Pessoas->Funcao;
    }

    // obtém tamanho
    static int Get_Tamanho(const C_Pessoas* const colecao)
    {
        return colecao->_C_Pessoas->Tamanho;
    }

    // obtém o limite atual
    static int Get_Limite(const C_Pessoas* const colecao)
    {
        return colecao->_C_Pessoas->Limite;
    }

#pragma endregion

#pragma region Setters 

    // Nenhum...

#pragma endregion

#pragma region CRUD em tempo de execução

    // Aumenta o tamanho atual da coleção
    // Parâmetros: coleção alvo do incremento
    static void Adc_Tamanho(C_Pessoas* const colecao)
    {
        colecao->_C_Pessoas->Tamanho++;
    }

    // Diminui o tamanho atual da coleção
    // Parâmetros: coleção alvo do decremento
    static void Dim_Tamanho(C_Pessoas* const colecao)
    {
        colecao->_C_Pessoas->Tamanho--;
    }

    // Adiciona uma pessoa no final da coleção, incrementando o seu tamanho atual
    // Parâmetros: coleção alvo da inserção e pessoa a ser adicionada nela
    // Retorno: vazio
    static void Adc_Pessoa(C_Pessoas* const colecao, Pessoa* const pessoa)
    {
        colecao->_C_Pessoas->pessoas[colecao->_C_Pessoas->Tamanho] = pessoa;
        Adc_Tamanho(colecao);
    }

    // Altera uma das pessoas na coleção com base em uma versão atualizada
    // Parâmetros: coleção alvo da alteração e pessoa atualizada
    // Retorno: vazio
    static void Alt_Pessoa(C_Pessoas* const colecao, Pessoa* const pessoa)
    {
        Pessoa* p_alvo = (Pessoa*) colecao->Busc_Pessoa(colecao, pessoa->Get_Matricula(pessoa));

        if (p_alvo != NULL)
        {
            p_alvo->Set_Ativo(p_alvo, p_alvo->Get_Ativo(pessoa));
            p_alvo->Set_Nome(p_alvo, p_alvo->Get_Nome(pessoa));
            p_alvo->Set_Idade(p_alvo, p_alvo->Get_Idade(pessoa));
            p_alvo->Set_Sexo(p_alvo, p_alvo->Get_Sexo(pessoa));
        }
    }

    // Busca por uma pessoa e retorna o seu endereço se estiver na coleção, ou NULL caso contrário
    // Parâmetros: coleção alvo da busca e matrícula da pessoa a ser encontrada
    // Retorno: endereço da pessoa encontrada ou NULL caso não haja pessoa com matrícula específicada
    static Pessoa* Busc_Pessoa(C_Pessoas* const colecao, char* const Matricula)
    {
        for (int i = 0; i < colecao->_C_Pessoas->Tamanho; i++)
            if (colecao->_C_Pessoas->pessoas[i]->Get_Matricula(colecao->_C_Pessoas->pessoas[i]) == Matricula)
                return colecao->_C_Pessoas->pessoas[i];

        return NULL;
    }

    // Remoção lógica da pessoa, buscando-a com função auxiliar, alterando seu parâmetro de "ativo" e colocando no final do vetor diminuindo o seu tamanho
    // Ao adicionar pessoa, a pessoa removida por último será sobrescrita...
    // Parâmetros: coleção alvo da remoção e matrícula da pessoa a ser removida dela
    // Retorno: vazio
    static void Rem_Pessoa(C_Pessoas* const colecao, char* const Matricula)
    {
        Pessoa* p_alvo = colecao->Busc_Pessoa(colecao, Matricula);
        
        if (p_alvo == NULL)
            return;

        if (p_alvo->Get_Ativo(p_alvo) == INATIVO)
            return; 
        
        p_alvo->Set_Ativo(p_alvo, INATIVO);
    }

#pragma endregion

///////////////////////////////////

#pragma region Base

    // Cria coleção de pessoa, atribui suas propriedades e retorna o seu ponteiro
    C_Pessoas* PC_Construtor(Pessoa* Pessoas, char Funcao)
    { 
        // mesma abordagem adotada para o C_Construtor, notas compartilhadas
        // modelos para a criação de uma coleção de pessoas
        static _C_Pessoas _colecao_stc;
        static C_Pessoas colecao_stc = (C_Pessoas)
        {
            // Getters
            Get_Funcao,
            Get_Tamanho,
            Get_Limite,
            // CRUD
            Adc_Tamanho,
            Dim_Tamanho,
            Adc_Pessoa,
            Alt_Pessoa,
            Busc_Pessoa,
            Rem_Pessoa,
            // desconstrutor
            PC_Desconstrutor,
            // membros privados
            &_colecao_stc
        };

        C_Pessoas* colecao = (C_Pessoas*) malloc(sizeof(C_Pessoas));
        memcpy(colecao, &colecao_stc, sizeof(C_Pessoas));

        colecao->_C_Pessoas->Funcao = Funcao;
        colecao->_C_Pessoas->Tamanho = 0;
        colecao->_C_Pessoas->Limite = MAX_INI;
        colecao->_C_Pessoas->pessoas = (Pessoa**) malloc(sizeof(Pessoa*) * colecao->_C_Pessoas->Limite);
        
        for (int i = 0; i < colecao->_C_Pessoas->Limite; i++)
            colecao->_C_Pessoas->pessoas[i] = NULL;
        
        return colecao;
    };

    // Libera a coleção desconstruindo todas as pessoas na base de dados dela, retornando nulo
    static C_Pessoas* PC_Desconstrutor(C_Pessoas* colecao)
    {
        // libera todas as pessoas na coleção
        for (int i = 0; i < colecao->_C_Pessoas->Tamanho; i++)
            colecao->_C_Pessoas->pessoas[i]->Desconstrutor(colecao->_C_Pessoas->pessoas[i]);
        
        // libera a coleção
        free(colecao);
        return NULL;
    };

#pragma endregion

///////////////////////////////////

#pragma endregion