#include "Pessoa.h"

#pragma region Pessoa

    ///////////////////////////////////

    #pragma region Estrutura

        // estrutura que representará uma pessoa
        struct pessoa 
        {
            char* Nome;
            char* Matricula;
            int Idade;
            char Sexo;
            char* Data_Nascimento;
            char* CPF;
            char Ativo;
        };

    #pragma endregion

    ///////////////////////////////////

    #pragma region Getters

        // Obtém propriedades encapsuladas de pessoa
        // Parâmetros: endereço da pessoa alvo da obtenção
        // Retorno: tipo de dado requerido

        // obtém a propriedade "idade"
        int Get_Idade(Pessoa* pessoa)
        {
            return pessoa->Idade;
        }

        // obtém a propriedade "nome"
        char* Get_Nome(Pessoa* pessoa)
        {
            return pessoa->Nome;
        }

        // obtém a propriedade "matrícula"
        char* Get_Matricula(Pessoa* pessoa)
        {
            return pessoa->Matricula;
        }

        // obtém a propriedade "data de nascimento"
        char* Get_Data_Nascimento(Pessoa* pessoa)
        {
            return pessoa->Data_Nascimento;
        }

        // obtém a propriedade "sexo"
        char Get_Sexo(Pessoa* pessoa)
        {
            return pessoa->Sexo;
        }

        // obtém a propriedade "cpf"
        char* Get_CPF(Pessoa* pessoa)
        {
            return pessoa->CPF;
        }

        // obtém a propriedade "ativo"
        char Get_Ativo(Pessoa *pessoa)
        {
            return pessoa->Ativo;
        }

    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters

        // Definem propriedades encapsuladas de pessoa
        // Parâmetros: endereço da pessoa alvo da definição e novo valor para a propriedade
        // Retorno: vazio

        // define a propriedade "nome"
        void Set_Nome(Pessoa* pessoa, char* Nome)
        {
            pessoa->Nome = Nome;
        }

        // define a propriedade "idade"
        void Set_Idade(Pessoa *pessoa, int Idade)
        {
            pessoa->Idade = Idade;
        }

        // define a propriedade "sexo"
        void Set_Sexo(Pessoa* pessoa, char Sexo)
        {
            pessoa->Sexo = Sexo;
        }

        // define a propriedade "ativo"
        void Set_Ativo(Pessoa *pessoa, char Ativo)
        {
            pessoa->Ativo = Ativo;
        }

        /*
        // Contabilizar que não há como uma pessoa mudar de matrícula
        // Entender matrícula como chave primária
        void Set_Matricula(Pessoa* pessoa, char Matricula[20])
        {
            pessoa->Matricula = Matricula;
        }
        */

        /*
        // Contabilizar que não há como a data de nascimento de uma pessoa mudar
        void Set_Data_Nascimento(Pessoa* pessoa, char Data_Nascimento[9])
        {
            pessoa->Data_Nascimento = Data_Nascimento;
        }
        */

        /*
        // Contabilizar que não há como o cpf de uma pessoa mudar
        void Set_CPF(Pessoa* pessoa, char CPF[12])
        {
            pessoa->CPF = CPF;
        }
        */

    #pragma endregion

    ///////////////////////////////////

    #pragma region Base
        // Construtor e desconstrutor

        // Cria pessoa, atribui suas propriedades e retorna o seu ponteiro
        Pessoa* P_Constructor (char Matricula[20], char CPF[12], char Data_Nascimento[9], char Funcao, char* Nome, int Idade, char Sexo)
        {
            Pessoa* P = (Pessoa*) malloc(sizeof(Pessoa));

            P->Matricula = Matricula;
            P->Data_Nascimento = Data_Nascimento;
            P->CPF = CPF;
            P->Nome = Nome;
            P->Idade = Idade;
            P->Sexo = Sexo;

            return P;
        }

        // Libera pessoa, desalocando espaço de memória especificado
        Pessoa* P_Deconstructor (Pessoa* pessoa)
        {
            free(pessoa);
            return NULL;
        }

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

#pragma region COLEÇÃO

///////////////////////////////////

#pragma region Estrutura

// Estrutura que representa a coleção
struct c_pessoas
{
    Pessoa* pessoas;
    char Funcao;
    int Tamanho;
    int Limite;
};

#pragma endregion

///////////////////////////////////

#pragma region Getters 

    // obtém o endereço do vetor de pessoas - elemento [0]
    Pessoa* Get_Pessoas(C_Pessoas* colecao)
    {
        return colecao->pessoas;
    }

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
    void Adc_Pessoa(C_Pessoas* colecao, Pessoa pessoa)
    {

        colecao->pessoas[colecao->Tamanho] = pessoa;
        Adc_Tamanho(colecao);
    }

    // Altera uma das pessoas na coleção com base em uma versão atualizada
    // Parâmetros: coleção alvo da alteração e pessoa atualizada
    // Retorno: vazio
    void Alt_Pessoa(C_Pessoas* colecao, Pessoa pessoa)
    {
        Pessoa* p_alvo = Busc_Pessoa(colecao, pessoa.Matricula);

        if (p_alvo != NULL)
            *p_alvo = pessoa;
    }

    // Busca por uma pessoa e retorna o seu endereço se estiver na coleção, ou NULL caso contrário
    // Parâmetros: coleção alvo da busca e matrícula da pessoa a ser encontrada
    // Retorno: endereço da pessoa encontrada ou NULL caso não haja pessoa com matrícula específicada
    Pessoa* Busc_Pessoa(C_Pessoas* colecao, char* Matricula)
    {
        for (int i = 0; i < colecao->Tamanho; i++)
            if (colecao->pessoas[i].Matricula == Matricula)
                return &colecao->pessoas[i];

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

        int Tamanho = Get_Tamanho(colecao);

        Pessoa temp = colecao->pessoas[Tamanho];
        colecao->pessoas[Tamanho] = *p_alvo;
        *p_alvo = temp;

        Dim_Tamanho(colecao);
    }

#pragma endregion

///////////////////////////////////

#pragma endregion