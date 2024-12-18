#include "Pessoa.h"

#pragma region Pessoa

    ///////////////////////////////////

    #pragma region Estrutura

        // estrutura que representará uma pessoa
        struct Pessoa 
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

