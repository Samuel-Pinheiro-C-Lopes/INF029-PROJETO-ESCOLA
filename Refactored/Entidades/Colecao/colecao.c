///////////////////////////////////

#pragma region Include

    #include "colecao.h"

#pragma endregion

///////////////////////////////////

#pragma region Colecao 

    ///////////////////////////////////

    #pragma region Endereço dos métodos

        // getters
        //typedef int (*__Get_Limite_ptr) (const Colecao* const colecao);
        // auxiliares
        // tamanho / limites
        typedef void (*__Aum_Tamanho_ptr) (Colecao* const colecao);
        typedef void (*__Dim_Tamanho_ptr) (Colecao* const colecao);
        typedef void (*__Aum_Limite_ptr) (Colecao* const colecao);
        typedef void (*__Dim_Limite_ptr) (Colecao* const colecao);
        // arr
        typedef void** (*__Realocar_Arr_ptr) (Colecao* const colecao);
        typedef void (*__Limpar_Arr_ptr) (Colecao* const colecao);
        typedef void (*__Inicializar_Novo_Espaco_Arr_ptr) (Colecao* const colecao);

    #pragma endregion

    ///////////////////////////////////
    
    #pragma region Estrutura 
        
        struct _colecao 
        {
            // MÉTODOS
            // getters
            //__Get_Limite_ptr Get_Limite; 
            // auxiliares
            __Aum_Limite_ptr Aum_Limite;
            __Dim_Limite_ptr Dim_Limite;
            __Aum_Tamanho_ptr Aum_Tamanho;
            __Dim_Tamanho_ptr Dim_Tamanho;
            __Limpar_Arr_ptr Limpar_Arr;
            __Realocar_Arr_ptr Realocar_Arr;
            __Inicializar_Novo_Espaco_Arr_ptr Inicializar_Novo_Espaco_Arr;

            // PROPRIEDADES
            int tamanho;
            int limite;
            Item** itens;
            char* tipo; // opt
        };

    #pragma endregion
    
    ///////////////////////////////////

#pragma endregion

///////////////////////////////////

#pragma region Getters 

    // Público
    // Sumário: retorna o tamanho atual da coleção
    // Parâmetros: <colecao: ponteiro da coleção>
    // Retorno: <int: tamanho atual>
    static int Get_Tamanho (const Colecao* const colecao)
    {
        return colecao->_colecao->tamanho;
    }

    // Público
    // Sumário: retorna o tipo da coleção
    // Parâmetros: <colecao: ponteiro da coleção>
    // Retorno: <char*: cadeia que representa o seu tipo>
    static char* Get_Tipo (const Colecao* const colecao)
    {
        return colecao->_colecao->tipo;
    }

    // Privado
    // Sumário: retorna o limite atual da coleção
    // Parâmetros: <colecao: ponteiro da coleção>
    // Retorno: <int: limite atual>
    static int Get_Limite (const Colecao* const colecao)
    {
        return colecao->_colecao->limite;
    }


#pragma endregion

///////////////////////////////////

#pragma region CRUD

    // Público
    // Sumário: adiciona um item já montado - conteúdo, identificador e ativo - à coleção,
    // verificando se há tamanho disponível e, caso não haja, realiza chamada de funções auxiliares
    // a fim de possibilitar a inserção do novo item
    // Parâmetros: <colecao: ponteiro para a coleção a ter um item adicionado> e
    // <item: item genêrico preenchido a ser inserido>
    // Retorno: <void>
    static void Adc_Item (Colecao* const colecao, Item* item)
    {
        if (colecao->_colecao->tamanho == colecao->_colecao->limite)
        {
            colecao->_colecao->Aum_Limite(colecao);
            colecao->_colecao->Realocar_Arr(colecao);
            colecao->_colecao->Inicializar_Novo_Espaco_Arr(colecao);
        }
        
        colecao->_colecao->itens[colecao->_colecao->tamanho] = item;
        colecao->_colecao->tamanho++;
    }

    // Público
    // Sumário: busca por um item da coleção que possua um certo identificador
    // Parâmetros: <colecao: ponteiro da coleção a ser realizada a busca> e
    // <identificador: identificador chave da busca>
    // Retorno: <Item*: ponteiro do primeiro item na coleção com o identificador, 
    // ou NULL caso não haja um na coleção>
    static Item* Bus_Item (const Colecao* const colecao, char* identificador)
    {
        for (int i = 0; i < colecao->_colecao->tamanho; i++)
            if (Comparar_Strs(colecao->_colecao->itens[i]->identificador, identificador))
                return colecao->_colecao->itens[i];
        return NULL;
    }

    // Público
    // Sumário: remove o primeiro item com certo identificador da coleção logicamente, 
    // trocando o seu campo "ativo". 
    // Não faz nada com a coleção caso não encontre um item com identificador igual.
    // Parâmetros: <colecao: ponteiro da coleção a ter um item removido> e 
    // <identificador: identificador do item a ser removido, caso haja>
    // Retorno: <void>
    static void Rem_Item (Colecao* const colecao, char* identificador)
    {
        Item* item_alvo = Bus_Item(colecao, identificador);

        if (item_alvo == NULL)
            return;

        item_alvo->ativo = INATIVO;
    }

    // Público
    // Sumário: altera o conteúdo do primeiro item da coleção com identificador
    // igual ao do item passado pelo conteúdo do próprio, buscando
    // pelo identificador deste item - não fazendo nada caso não encontre na busca
    // Parâmetros: <colecao: ponteiro da coleção a ter um item alterado> e
    // <item: item atualizado>
    // Retorno: <void>
    static void Alt_Item (Colecao* const colecao, Item* item)
    {
        Item* item_alvo = Bus_Item(colecao, item->identificador);

        if (item_alvo == NULL)
            return;

        item_alvo->conteudo = item->conteudo;
    }

#pragma endregion

///////////////////////////////////

#pragma region Auxiliares

    // Privado
    // Sumário: aumenta o campo do tamanho da coleção em 1
    // Parâmetros: <colecao: ponteiro da coleção a ter seu tamanho aumentado>
    // Retorno: <void>
    static void Aum_Tamanho (Colecao* const colecao)
    {
        colecao->_colecao->tamanho++;
    }

    // Privado
    // Sumário: diminui o campo do tamanho da coleção em 1
    // Parâmetros: <colecao: ponteiro da coleção a ter seu tamanho diminuído>
    // Retorno: <void>
    static void Dim_Tamanho (Colecao* const colecao)
    {
        colecao->_colecao->tamanho--;
    }

    // Privado
    // Sumário: aumenta o campo do limite da coleção em 2x
    // Parâmetros: <colecao: ponteiro da coleção a ter seu limite aumentado>
    // Retorno: <void>
    static void Aum_Limite (Colecao* const colecao)
    {
        colecao->_colecao->limite *= 2;
    }

    // Privado
    // Sumário: diminui o campo do limite da coleção em x0.5
    // Parâmetros: <colecao: ponteiro da coleção a ter seu limite diminuído>
    // Retorno: <void>   
    static void Dim_Limite (Colecao* const colecao)
    {
        colecao->_colecao->limite /= 2;
    }

    // Privado
    // Sumário: limpa todos os itens do vetor da coleção, designando seus ponteiros de item 
    // para NULL e definindo seu tamanho e limite de acordo - 0 e LIM_INI respectivamente
    // Parâmetros: <colecao: ponteiro da coleção a ser limpa>
    // Retorno: <void>
    static void Limpar_Arr (Colecao* const colecao)
    {
        int i, j; // contadores
        void* p_atual; // apontará para o atual

        // 1° etapa: liberar itens e tornar ponteiros nulos
        // itera a lista
        for (i = 0; i < colecao->_colecao->tamanho; i++)
        {
            // indexa o atual
            p_atual = colecao->_colecao->itens[i];

            if (p_atual != NULL)
            {
                // libera
                free(p_atual);
                // coleção naquela posição aponta para nulo
                colecao->_colecao->itens[i] = NULL; 
            }
        }
        
        // 2° etapa: atualizar limite
        colecao->_colecao->limite = LIM_INI;
        
        // 3° etapa: atualizar tamanho
        colecao->_colecao->tamanho = 0;
        
        // coleção limpa dos inativos e realocada de acordo 

    }

    // Privado
    // Sumário: realoca a memória do vetor de ponteiros de itens da coleção de acordo com o
    // seu limite
    // Parâmetros: <colecao: ponteiro da coleção a ter seu vetor de ponteiros de itens realocado>
    // Retorno: <Item**: endereço de memória do vetor resultante da realocação>
    static Item** Realocar_Arr (Colecao* const colecao)
    {
        return (Item**) realloc(colecao->_colecao->itens, sizeof(Item*) * colecao->_colecao->limite);
    }

    // Privado
    // Sumário: inicializa o vetor de ponteiros de itens com NULL baseado em seu tamanho e limite.
    // itens já inseridos não são alterados, apenas designando espaços alocados mas não inicializados.
    // Parâmetros: <colecao: ponteiro da colecao a ter seu espaço não inicializado designado>
    // Retorno: <void>
    static void Inicializar_Novo_Espaco_Arr (Colecao* const colecao)
    {
        for (int i = colecao->_colecao->tamanho; i < colecao->_colecao->limite; i++)
        {
            colecao->_colecao->itens[i] = NULL;
        }
    }

#pragma endregion

///////////////////////////////////

#pragma region Base 

#pragma endregion

///////////////////////////////////
