#include "Pessoa.h"

#pragma region Pessoa

    ///////////////////////////////////

    #pragma region Estrutura

        // estrutura que representará os membros privados de uma pessoa
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
    
    #pragma region HEADER

        ///////////////////////////////////

        #pragma region Getters 

            static int Get_Idade(const Pessoa* const pessoa);
            static char* Get_Nome(const Pessoa* const pessoa);
            static char* Get_Matricula(const Pessoa* const pessoa);
            static char* Get_Data_Nascimento(const Pessoa* const pessoa);
            static char Get_Sexo(const Pessoa* const pessoa);
            static char* Get_CPF(const Pessoa* const pessoa);
            static char Get_Ativo(const Pessoa* const pessoa);

        #pragma endregion

        ///////////////////////////////////

        #pragma region Setters

            static void Set_Idade(Pessoa* const pessoa, int const idade);
            static void Set_Nome(Pessoa* const pessoa, char* const nome);
            // void Set_Matricula(Pessoa* pessoa, char Matricula[20]);
            // void Set_Data_Nascimento(Pessoa* pessoa, char Data_Nascimento[9]);
            static void Set_Sexo(Pessoa* const pessoa, char const sexo);
            //void Set_CPF(Pessoa* pessoa, char CPF[12]);
            static void Set_Ativo(Pessoa* const pessoa, char const ativo);

        #pragma endregion

        ///////////////////////////////////
        
        #pragma region Base

            static Pessoa* P_Desconstrutor(Pessoa* Pessoa);

        #pragma endregion
        
        ///////////////////////////////////

    #pragma endregion


    ///////////////////////////////////

    #pragma region Getters

        // Obtém propriedades encapsuladas de pessoa
        // Parâmetros: endereço da pessoa alvo da obtenção
        // Retorno: tipo de dado requerido
        // Const: tanto o ponteiro quanto estrutura devem permanecer iguais
        // durante o tempo de execução dos getters

        // obtém a propriedade "idade"
        static int Get_Idade(const Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Idade;
        }

        // obtém a propriedade "nome"
        static char* Get_Nome(const Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Nome;
        }

        // obtém a propriedade "matrícula"
        static char* Get_Matricula(const Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Matricula;
        }

        // obtém a propriedade "data de nascimento"
        static char* Get_Data_Nascimento(const Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Data_Nascimento;
        }

        // obtém a propriedade "sexo"
        static char Get_Sexo(const Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Sexo;
        }

        // obtém a propriedade "cpf"
        static char* Get_CPF(const Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->CPF;
        }

        // obtém a propriedade "ativo"
        static char Get_Ativo(const Pessoa* const pessoa)
        {
            return pessoa->_Pessoa->Ativo;
        }

    #pragma endregion

    ///////////////////////////////////

    #pragma region Setters

        // Definem propriedades encapsuladas de pessoa
        // Parâmetros: endereço da pessoa alvo da definição e novo valor para a propriedade
        // Retorno: vazio
        // Const: A estrutura mudará dentro de seu escopo, entretanto o ponteiro e valor de entrada
        // devem persistir durante seu tempo de execução

        // define a propriedade "nome"
        static void Set_Nome(Pessoa* const pessoa, char* const nome)
        {
            pessoa->_Pessoa->Nome = nome;
        }

        // define a propriedade "idade"
        static void Set_Idade(Pessoa* const pessoa, int const idade)
        {
            pessoa->_Pessoa->Idade = idade;
        }

        // define a propriedade "sexo"
        static void Set_Sexo(Pessoa* const pessoa, char const sexo)
        {
            pessoa->_Pessoa->Sexo = sexo;
        }

        // define a propriedade "ativo"
        static void Set_Ativo(Pessoa* const pessoa, char const ativo)
        {
            pessoa->_Pessoa->Ativo = ativo;
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
        Pessoa* P_Construtor (char Matricula[20], char CPF[12], char Data_Nascimento[9], char* Nome, int Idade, char Sexo)
        {
            // Notas sobre esta abordagem no final deste documento...
            
            // membros estáticos que servem como modelo para novas instâncias
            // ATUALMENTE TODAS AS PESSOAS TEM _PESSOA APONTANDO PARA STC_P
            // separar métodos em outra struct 

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
                // desconstrutor
                P_Desconstrutor,
            };       

            // membro privado
            *(_Pessoa**)&stc_P._Pessoa = NULL; // cast 'const aside' para tornar nulo 
            if (!stc_P._Pessoa)
            {
                // cast 'const aside' para alocar
                *(_Pessoa**)&stc_P._Pessoa = (_Pessoa*) malloc(sizeof(_Pessoa));
            }

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
        static Pessoa* P_Desconstrutor (Pessoa* pessoa)
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

     Nota: 
        acabei optando por uma junção dos dois métodos pela seguinte premissa:
        seria custoso declarar e atribuir toda vez com o construtor, entretanto
        o ponteiro de _Pessoa faz necessária a alocação de memória para cada construção.
        se verifica o tipo atual para realizar alteração e, depois disso, ignora-se
        temporariamente o tipo qualificado constante de _Pessoa a fim de alocar 
        um espaço diferente para esse tipo estático
        Não parece ser uma forma muito limpa e concisa de obter o resultado, mas funciona
        e os membros possuem mutabilidade e encapsulamento esperado no cliente, sendo
        computacionalmente melhor do que declarar e atribuir toda vez que construir pessoa,
        uma vez que a maior parte dos campos e a própria estrutura é declarada de forma estática



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