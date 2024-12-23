#ifndef COLECAO_H 
#define COLECAO_H

///////////////////////////////////

#pragma region INCLUDE

    #include "../../Utils/Dependencias.h"
    #include "../../Utils/Geral.h"

#pragma endregion

///////////////////////////////////

#pragma region Definições

    #define LIM_INI (8)
    #define ATIVO ('O')
    #define INATIVO ('X')

#pragma endregion

///////////////////////////////////

#pragma region COLECAO

    ///////////////////////////////////

    #pragma region Tipo da estrutura

        typedef struct colecao Colecao; // público
        typedef struct _colecao _Colecao; // privado
        typedef struct item Item;

    #pragma endregion

    ///////////////////////////////////

    #pragma region Endereço dos métodos 

        // GETTERS
        typedef int (*__Get_Tamanho_ptr) (const Colecao* const colecao);
        typedef char* (*__Get_Tipo_ptr) (const Colecao* const colecao);
        //typedef int (*__Get_Limite_ptr) (const Colecao* const colecao);
        // CRUD
        typedef void (*__Adc_Item_ptr) (Colecao* const colecao, Item* item);
        typedef void* (*__Bus_Item_ptr) (const Colecao* const colecao, char* identificador);
        typedef void (*__Rem_Item_ptr) (Colecao* const colecao, char* identificador);
        typedef void (*__Atl_Item_ptr) (Colecao* const colecao, Item* item); 
        // // Auxiliares privados
        // typedef void (*__Aum_Tamanho_ptr) (Colecao* const colecao);
        // typedef void (*__Dim_Tamanho_ptr) (Colecao* const colecao);
        // typedef void (*__Aum_Limite_ptr) (Colecao* const colecao);
        // typedef void (*__Dim_Limite_ptr) (Colecao* const colecao);
        // typedef void (*__Realocar_Arr) (Colecao* const colecao);
        // typedef void (*__Limpar_Arr) (Colecao* const colecao);

    #pragma endregion

    ///////////////////////////////////

    #pragma region Estrutura
        
        struct colecao 
        {
            // getters
            __Get_Tamanho_ptr Get_Tamanho;
            __Get_Tipo_ptr Get_Tipo;
            
            // CRUD
            __Adc_Item_ptr Adc_Item;
            __Atl_Item_ptr Atl_Item;
            __Bus_Item_ptr Bus_Item;
            __Rem_Item_ptr Rem_Item;

            // privado
            _Colecao* _colecao;
        };

        struct item 
        {
            // genéricos
            char* identificador;
            char ativo;
            // conteúdo variável com a implementação
            void* conteudo;
        };

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

/////////////////////////////////// 

#pragma region Base 

    

#pragma endregion
        
/////////////////////////////////// 

#endif