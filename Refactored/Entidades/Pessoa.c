#include "Pessoa.h"

#pragma region Pessoa

    ///////////////////////////////////

    #pragma region Estrutura

        // estrutura que representará uma pessoa
        struct _pessoa 
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
        static int Get_Idade(Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Idade;
        }

        // obtém a propriedade "nome"
        static char* Get_Nome(Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Nome;
        }

        // obtém a propriedade "matrícula"
        char* Get_Matricula(Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Matricula;
        }

        // obtém a propriedade "data de nascimento"
        char* Get_Data_Nascimento(Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Data_Nascimento;
        }

        // obtém a propriedade "sexo"
        char Get_Sexo(Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Sexo;
        }

        // obtém a propriedade "cpf"
        char* Get_CPF(Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->CPF;
        }

        // obtém a propriedade "ativo"
        static char Get_Ativo(Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Ativo;
        }

    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters

        // Definem propriedades encapsuladas de pessoa
        // Parâmetros: endereço da pessoa alvo da definição e novo valor para a propriedade
        // Retorno: vazio

        // define a propriedade "nome"
        static void Set_Nome(Pessoa* pessoa, char* Nome)
        {
            pessoa->_Pessoa->Nome = Nome;
        }

        // define a propriedade "idade"
        static void Set_Idade(Pessoa* pessoa, int Idade)
        {
            pessoa->_Pessoa->Idade = Idade;
        }

        // define a propriedade "sexo"
        void Set_Sexo(Pessoa* pessoa, char Sexo)
        {
            pessoa->_Pessoa->Sexo = Sexo;
        }

        // define a propriedade "ativo"
        static void Set_Ativo(Pessoa *pessoa, char Ativo)
        {
            pessoa->_Pessoa->Ativo = Ativo;
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
        Pessoa* P_Constructor (char Matricula[20], char CPF[12], char Data_Nascimento[9], char* Nome, int Idade, char Sexo)
        {
            // Notas sobre esta abordagem no final deste documento...
            
            // membros estáticos que servem como modelo para novas instâncias
            static _Pessoa stc_p;
            static Pessoa stc_P = (Pessoa)
            {
                // getters
                Get_Idade,
                Get_Nome,
                Get_Matricula,
                Get_Data_Nascimento,
                Get_Sexo,
                Get_CPF,
                Get_Ativo,
                // setters
                Set_Idade,
                Set_Nome,
                Set_Sexo,
                Set_Ativo,
                // membro privado
                &stc_p
            };            
            
            // alocação
            Pessoa* P = (Pessoa*) malloc(sizeof(Pessoa));
            // passa modelo para nova Pessoa alocada
            memcpy(P, &stc_P, sizeof(Pessoa));
            
            // atribuir propriedades privadas
            P->_Pessoa->Matricula = Matricula;
            P->_Pessoa->CPF = CPF;
            P->_Pessoa->Data_Nascimento = Data_Nascimento;
            P->_Pessoa->Nome = Nome;
            P->_Pessoa->Sexo = Sexo;
            P->_Pessoa->Idade = Idade;

            // retornar endereço alocado dinamicamente
            return P;
        }

        // Libera pessoa, desalocando espaço de memória especificado
        Pessoa* P_Deconstructor (Pessoa* pessoa)
        {
            free(pessoa->_Pessoa); // libera ponteiro para membros privados
            free(pessoa); // libera membros públicos
            return NULL;
        }

    #pragma endregion

    ///////////////////////////////////

#pragma endregion


// Notas sobre abordagem do construtor de pessoa:
//
    /*

    Essas são duas formas de definir os campos constantes uma vez que malloc tecnicamente
    já o faz, apesar de com lixo - assim não tendo como inicializar apropriadamente.
    Creio que não recaia em "comportamento indeterminado" de pela referência padrão C11 
    pela explicação de Marco Bonelli no stackoverflow, que diz, traduzido:
    Escrito entre ( ) estão notas da minha parte sobre meu entendimento do tópico

    1 - Este código não viola 6.7.3/6 pois o espaço retornado por 'malloc' não é 
    "um objeto definido com um tipo qualificado como constante".
    A expressão P->[...] não é um objeto, mas sim uma expressão.
    Apesar de ter tipo qualificado como constante, denota um objeto que não foi
    definido por um tipo qualificado como constante - na verdade, não foi definido
    com nenhum tipo.
    (Ou seja, apesar do tipo ser const, a memória alocada por malloc não é const - na verdade,
    não tem tipo associado a princípio visto que tem lixo armazenado)
    2 - A regra de "strict aliasing" não é violada por escrever em um espaço
    alocado por malloc, pois seu tipo específico é atualizado a cada escrita (6.5/6)
    (não é feito um acesso com tipo incompatível, mas sim alteração do seu tipo com cast, 
    visto que a alocação dinâmica acaba tendo maior flexibilidade: tipo atualizado a cada 
    escrita)

    comentário original: <https://stackoverflow.com/questions/9691404/how-to-initialize-const-in-a-struct-in-c-with-malloc>
    
    A parte que aborda o comportamento indefinido dessas resoluções se encontra abaixo, 
    em idioma original:

    "This code does not violate 6.7.3/6 because the space returned by malloc 
    is not "an object defined with a const-qualified type". 
    The expression mydeneme->a is not an object, it is an expression. 
    Although it has const-qualified type, it denotes an object which was 
    not defined with a const-qualified type (in fact, not defined with any type at all).
    The strict aliasing rule is never violated by writing into space 
    allocated by malloc, because the effective type (6.5/6) is u
    pdated by each write".
    */
    // Com memcpy:
    /*
    Explicação: se é criado estaticamente a forma com que uma Pessoa deve
    ser inicializada e, após alocar no HEAP espaço para uma Pessoa, se copia
    a pessoa estática para o espaço alocado

    static _Pessoa stc_p;
    static Pessoa stc_P = (Pessoa)
    {
        // getters
        Get_Idade,
        Get_Nome,
        Get_Matricula,
        Get_Data_Nascimento,
        Get_Sexo,
        Get_CPF,
        Get_Ativo,
        // setters
        Set_Idade,
        Set_Nome,
        Set_Sexo,
        Set_Ativo,
        &stc_p
    };            
    
    Pessoa* P = (Pessoa*) malloc(sizeof(Pessoa));
    memcpy(P, &stc_P, sizeof(Pessoa));

    */

    //Com 'cast away'

    /*

    Explicação: se utiliza cast para que o compilador entenda
    os campos constantes de ponteiro como ponteiro, assim permitindo que haja
    designação de seu valor apesar da sua definição como constante
    (já que malloc apenas atribui lixo não me pareceu inconsistente, visto que não
    achei forma de incializar apropriadamente)
    Pessoa* P = (Pessoa*) malloc(sizeof(Pessoa));
    // getters
    *(int (**) (Pessoa*))&P->Get_Idade = Get_Idade;
    *(char* (**) (Pessoa*))&P->Get_Matricula = Get_Matricula;
    *(char* (**) (Pessoa*))&P->Get_Data_Nascimento = Get_Data_Nascimento;
    *(char* (**) (Pessoa*))&P->Get_CPF = Get_CPF;
    *(char (**) (Pessoa*))&P->Get_Sexo = Get_Sexo;
    *(char* (**) (Pessoa*))&P->Get_Nome = Get_Nome;
    *(char (**) (Pessoa*))&P->Get_Ativo = Get_Ativo;
    // setters
    *(void (**) (Pessoa*, int))&P->Set_Idade = Set_Idade;
    *(void (**) (Pessoa*, char))&P->Set_Ativo = Set_Ativo;
    *(void (**) (Pessoa*, char*))&P->Set_Nome = Set_Nome;
    *(void (**) (Pessoa*, char))&P->Set_Sexo = Set_Sexo;
    // membro privado _Pessoa
    *(_Pessoa**)&P->_Pessoa = (_Pessoa*) malloc(sizeof(_Pessoa));
    //
    A abordagem com memcpy foi optada pois acredito que trabalhar com um 
    tipo estático seja melhor em termos de custo computacional, visto que
    a construção de uma pessoa será algo rotineiro no programa e esses endereços, a princípio,
    */