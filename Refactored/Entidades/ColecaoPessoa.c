#include "ColecaoPessoa.h"
#include "Pessoa.h"

///////////////////////////////////

#pragma region COLEÇÃO

///////////////////////////////////

#pragma region Estrutura

    // ponteiro para os métodos privados
    typedef void (*Red_Limite_ptr) (C_Pessoas* const colecao);
    typedef void (*Exp_Limite_ptr) (C_Pessoas* const colecao);
    typedef int (*Get_Limite_ptr) (const C_Pessoas* const colecao);
    typedef Pessoa** (*C_Realloc_ptr) (C_Pessoas* const colecao);
    typedef void (*Inicializador_Nulo_ptr) (C_Pessoas* const colecao);

    // Estrutura que representa os membros privados da coleção
    struct _c_pessoas
    {
        // métodos privados
        Red_Limite_ptr Red_Limite;
        Exp_Limite_ptr Exp_Limite;
        Get_Limite_ptr Get_Limite;
        C_Realloc_ptr C_Realloc;
        Inicializador_Nulo_ptr Inicializador_Nulo;

        // propriedades privadas
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
        // Público
        static char Get_Funcao(const C_Pessoas* const colecao);
        static int Get_Tamanho(const C_Pessoas* const colecao);
        // Privado
        // Limite só terá utilidade dentro do escopo da coleção
        static int Get_Limite(const C_Pessoas* const colecao);

    #pragma endregion
    
    ///////////////////////////////////

    #pragma region CRUD
        // Público
        static void Adc_Tamanho(C_Pessoas* const colecao);
        static void Dim_Tamanho(C_Pessoas* const colecao);
        static void Adc_Pessoa(C_Pessoas* const colecao, Pessoa* const pessoa);
        static void Alt_Pessoa(C_Pessoas* const colecao, Pessoa* const pessoa);
        static Pessoa* Busc_Pessoa(C_Pessoas* const colecao, char* const Matricula);
        static void Rem_Pessoa(C_Pessoas* const colecao, char* const Matricula);
        // Privado
        static void Exp_Limite(C_Pessoas* const colecao);
        static void Red_Limite(C_Pessoas* const colecao);
        static Pessoa** C_Realloc(C_Pessoas* const colecao);

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
        // caso tenha alcançado o limite, o expande, realoca o vetor de pessoas e
        // inicializa pessoas alocadas à frente
        if (colecao->Get_Tamanho(colecao) == colecao->_C_Pessoas->Get_Limite(colecao))
        {
            colecao->_C_Pessoas->Exp_Limite(colecao);
            colecao->_C_Pessoas->pessoas = colecao->_C_Pessoas->C_Realloc(colecao);
            colecao->_C_Pessoas->Inicializador_Nulo(colecao);
        }

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

    static void Exp_Limite(C_Pessoas* const colecao)
    {
        colecao->_C_Pessoas->Limite *= 2;
        //colecao->
    }

    static void Red_Limite(C_Pessoas* const colecao)
    {
        colecao->_C_Pessoas->Limite /= 2;
    }

    static Pessoa** C_Realloc(C_Pessoas* const colecao)
    {
        return realloc(colecao->_C_Pessoas->pessoas, 
            sizeof(Pessoa*) * colecao->_C_Pessoas->Get_Limite(colecao));
    }

    static void Inicializador_Nulo (C_Pessoas* const colecao)
    {
        for (int i = colecao->Get_Tamanho(colecao); i < colecao->_C_Pessoas->Get_Limite(colecao); i++)
            colecao->_C_Pessoas->pessoas[i] = NULL;
    }

    static void Limp_Pessoas(C_Pessoas* const colecao)
    {
        int i, j; // contadores
        Pessoa* p_atual; // apontará para o atual

        // 1° etapa: liberar pessoas inativas e tornar seus ponteiros nulos
        // itera a lista
        for (i = 0; i < colecao->Get_Tamanho(colecao); i++)
        {
            // indexa o atual
            p_atual = colecao->_C_Pessoas->pessoas[i];

            // se estiver inativo...
            if (p_atual->Get_Ativo(p_atual) == INATIVO)
            {
                // libera
                free(p_atual);
                // coleção naquela posição aponta para nulo
                colecao->_C_Pessoas->pessoas[i] = NULL; 
            }
        }
        
        // 2° etapa: atualiza o tamanho enviando todos os ponteiros liberados para o final
        // itera a lista
        for (i = 0; i < colecao->Get_Tamanho(colecao); i++)
        {
            // indexa o atual
            p_atual = colecao->_C_Pessoas->pessoas[i];
            
            // enquanto o atual for nulo...
            while (p_atual == NULL)
            {
                // unshift
                for (j = i; j < colecao->Get_Tamanho(colecao) - 1; j++)
                   colecao->_C_Pessoas->pessoas[j] = colecao->_C_Pessoas->pessoas[j + 1]; 
                
                // reduz o tamanho
                colecao->Dim_Tamanho(colecao);

                // se o tamanho for igual à posição indexadora, finalize
                if (colecao->Get_Tamanho(colecao) <= i)
                    break;
            }
        } 
        
        // 3° etapa: verifica o tamanho atual para realocar com base nele
        while (colecao->Get_Tamanho(colecao) < colecao->_C_Pessoas->Get_Limite(colecao) / 2)
            colecao->_C_Pessoas->Red_Limite(colecao);
        
        colecao->_C_Pessoas->C_Realloc(colecao);
        
        // coleção limpa dos inativos e realocada de acordo 
    }

#pragma endregion

///////////////////////////////////

#pragma region Base

    // Cria coleção de pessoa, atribui suas propriedades e retorna o seu ponteiro
    C_Pessoas* PC_Construtor(Pessoa* Pessoas, char Funcao)
    { 
        // mesma abordagem adotada para o C_Construtor, notas compartilhadas
        // modelos para a criação de uma coleção de pessoas
        static C_Pessoas stc_colecao = (C_Pessoas)
        {
            // Getters
            Get_Funcao,
            Get_Tamanho,
            // CRUD
            Adc_Tamanho,
            Dim_Tamanho,
            Adc_Pessoa,
            Alt_Pessoa,
            Busc_Pessoa,
            Rem_Pessoa,
            // desconstrutor
            PC_Desconstrutor,
        };

        // tentativa de implementar métodos privados...
        
        static _C_Pessoas stc_pv = (_C_Pessoas)
        {
            // propriedades privadas
            .Tamanho = 0,
            .Limite = MAX_INI,
            // métodos privados
            .Get_Limite = Get_Limite,
            .Exp_Limite = Exp_Limite,
            .Red_Limite = Red_Limite,
            .C_Realloc = C_Realloc,
            .Inicializador_Nulo = Inicializador_Nulo,
        };
        
        // copia endereço para novo membro privado
        _C_Pessoas* pv = (_C_Pessoas*) malloc(sizeof(_C_Pessoas));
        memcpy(pv, &stc_pv, sizeof(_C_Pessoas));
        
        // certifica-se de que o modelo estático irá prover o novo espaço alocado
        // para os membros privados - 'pv', neste caso
        *(_C_Pessoas**)&stc_colecao._C_Pessoas = NULL;
        if (!stc_colecao._C_Pessoas)
            *(_C_Pessoas**)&stc_colecao._C_Pessoas = pv;
        
        // aloca a nova coleção, copiando o conteúdo da coleção modelo,
        // que agora tem também o modelo dos membros privados
        C_Pessoas* colecao = (C_Pessoas*) malloc(sizeof(C_Pessoas));
        memcpy(colecao, &stc_colecao, sizeof(C_Pessoas));

        // designa o que resta
        colecao->_C_Pessoas->pessoas = (Pessoa**) malloc(sizeof(Pessoa*) * colecao->_C_Pessoas->Limite);
        colecao->_C_Pessoas->Funcao = Funcao;

        /*
        *(_C_Pessoas**)&stc_colecao._C_Pessoas = NULL;
        if (!stc_colecao._C_Pessoas)
            *(_C_Pessoas**)&stc_colecao._C_Pessoas = (_C_Pessoas*) malloc(sizeof(_C_Pessoas));        

        C_Pessoas* colecao = (C_Pessoas*) malloc(sizeof(C_Pessoas));
        memcpy(colecao, &stc_colecao, sizeof(C_Pessoas));

        colecao->_C_Pessoas->Funcao = Funcao;
        colecao->_C_Pessoas->Tamanho = 0;
        colecao->_C_Pessoas->Limite = MAX_INI;
        colecao->_C_Pessoas->pessoas = (Pessoa**) malloc(sizeof(Pessoa*) * colecao->_C_Pessoas->Limite);
        */

        // designa inicialmente como nulo todos os ponteiros de pessoa na coleção
        for (int i = 0; i < colecao->_C_Pessoas->Limite; i++)
            colecao->_C_Pessoas->pessoas[i] = NULL;
        
        return colecao;
    };

    // Libera a coleção desconstruindo todas as pessoas na base de dados dela, retornando nulo
    static C_Pessoas* PC_Desconstrutor(C_Pessoas* colecao)
    {
        // libera todas as pessoas na coleção
        for (int i = 0; i < colecao->_C_Pessoas->Tamanho; i++)
            //  ativa o desconstrutor de cada pessoa na coleção
            colecao->_C_Pessoas->pessoas[i]->Desconstrutor(colecao->_C_Pessoas->pessoas[i]);
        
        // libera a coleção
        free(colecao);
        return NULL;
    };

#pragma endregion

///////////////////////////////////

#pragma endregion