#include "ColecaoPessoa.h"

///////////////////////////////////

#pragma region COLEÇÃO

///////////////////////////////////

#pragma region Estrutura

// Estrutura que representa a coleção
struct c_pessoas
{
    Pessoa** pessoas;
    char Funcao;
    int Tamanho;
    int Limite;
};

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
    char Get_Funcao(C_Pessoas* colecao)
    {
        return colecao->Funcao;
    }

    // obtém tamanho
    int Get_Tamanho(C_Pessoas* colecao)
    {
        return colecao->Tamanho;
    }

#pragma endregion

#pragma region Setters 

    // Nenhum...

#pragma endregion

#pragma region CRUD em tempo de execução

    // Aumenta o tamanho atual da coleção
    // Parâmetros: coleção alvo do incremento
    void Adc_Tamanho(C_Pessoas* colecao)
    {
        colecao->Tamanho++;
    }

    // Diminui o tamanho atual da coleção
    // Parâmetros: coleção alvo do decremento
    void Dim_Tamanho(C_Pessoas* colecao)
    {
        colecao->Tamanho--;
    }

    // Adiciona uma pessoa no final da coleção, incrementando o seu tamanho atual
    // Parâmetros: coleção alvo da inserção e pessoa a ser adicionada nela
    // Retorno: vazio
    void Adc_Pessoa(C_Pessoas* colecao, Pessoa* pessoa)
    {
        colecao->pessoas[colecao->Tamanho] = pessoa;
        Adc_Tamanho(colecao);
    }

    // Altera uma das pessoas na coleção com base em uma versão atualizada
    // Parâmetros: coleção alvo da alteração e pessoa atualizada
    // Retorno: vazio
    void Alt_Pessoa(C_Pessoas* colecao, Pessoa* pessoa)
    {
        Pessoa* p_alvo = Busc_Pessoa(colecao, Get_Matricula(pessoa));

        if (p_alvo != NULL)
        {
            Set_Ativo(p_alvo, Get_Ativo(pessoa));
            Set_Nome(p_alvo, Get_Nome(pessoa));
            Set_Idade(p_alvo, Get_Idade(pessoa));
            Set_Sexo(p_alvo, Get_Sexo(pessoa));
        }
    }

    // Busca por uma pessoa e retorna o seu endereço se estiver na coleção, ou NULL caso contrário
    // Parâmetros: coleção alvo da busca e matrícula da pessoa a ser encontrada
    // Retorno: endereço da pessoa encontrada ou NULL caso não haja pessoa com matrícula específicada
    Pessoa* Busc_Pessoa(C_Pessoas* colecao, char* Matricula)
    {
        for (int i = 0; i < colecao->Tamanho; i++)
            if (Get_Matricula(colecao->pessoas[i]) == Matricula)
                return colecao->pessoas[i];

        return NULL;
    }

    // Remoção lógica da pessoa, buscando-a com função auxiliar, alterando seu parâmetro de "ativo" e colocando no final do vetor diminuindo o seu tamanho
    // Ao adicionar pessoa, a pessoa removida por último será sobrescrita...
    // Parâmetros: coleção alvo da remoção e matrícula da pessoa a ser removida dela
    // Retorno: vazio
    void Rem_Pessoa(C_Pessoas* colecao, char* Matricula)
    {
        Pessoa* p_alvo = Busc_Pessoa(colecao, Matricula);
        
        if (p_alvo == NULL)
            return;

        if (Get_Ativo(p_alvo) == INATIVO)
            return; 
        
        Set_Ativo(p_alvo, INATIVO);
    }

#pragma endregion

///////////////////////////////////

#pragma region Base

    // Cria coleção de pessoa, atribui suas propriedades e retorna o seu ponteiro
    C_Pessoas* PC_Construtor(Pessoa* Pessoas, char Funcao)
    {
        C_Pessoas* colecao = (C_Pessoas*) malloc(sizeof(C_Pessoas));

        colecao->Funcao = Funcao;
        colecao->Tamanho = 0;
        colecao->Limite = MAX_INI;
        colecao->pessoas = (Pessoa**) malloc(sizeof(Pessoa*) * colecao->Limite);
        
        for (int i = 0; i < colecao->Limite; i++)
            colecao->pessoas[i] = NULL;
        
        return colecao;
    };

    // Libera a coleção desconstruindo todas as pessoas na base de dados dela, retornando nulo
    C_Pessoas* PC_Desconstrutor(C_Pessoas* colecao)
    {
        for (int i = 0; i < colecao->Tamanho; i++)
            P_Desconstrutor(colecao->pessoas[i]);
        
        free(colecao);
        return NULL;
    };

#pragma endregion

///////////////////////////////////

#pragma endregion