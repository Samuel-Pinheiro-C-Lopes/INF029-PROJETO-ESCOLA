
/*
#define Idade(_1, ...) _Generic((_1),                               \
                            Pessoa*: g_Idade,                       \
                            int: _Generic((FIRST(__VA_ARGS__,)),    \
                                Pessoa*: s_Idade))(_1, __VA_ARGS__)
*/

// isso funciona, entretanto ele não reconhece o tipo de retorno do "Get Idade"
/*
#define Idade(N, ...) _Generic((N), \
                Pessoa*: g_Idade,   \
                default: s_Idade)
*/

// Para o número variado de argumentos...
/*
#define Idade(...) SELECT(__VA_ARGS__)(__VA_ARGS__)

#define SELECT(...) CONCAT(SELECT_, NARG(__VA_ARGS__))(__VA_ARGS__)
#define CONCAT(X, Y) CONCAT_(X, Y)
#define CONCAT_(X, Y) X ## Y
*/

// Função para cada tipo de chamada
/*
#define GET_MACRO (_1, _2, NAME, ...) NAME 
#define Idade(...) GET_MACRO (__VA_ARGS__, s_Idade, g_Idade)(__VA_ARGS__)
*/
/*
#define Idade(N, ...) \
    _Generic((N),   \
        Pessoa*: g_Idade, \
        int: _Generic((FIRST(__VA_ARGS__,)), \
            Pessoa*: s_Idade)) (N, __VA_ARGS__) \
        

#define FIRST(A, ...) A
*/
/*

#define Idade(N, ...) \
                _Generic((N), \
                    Pessoa*: g_Idade \
                    int: _Generic((M), \
                        Pessoa*: s_Idade) ( (M) )) ( (N) )
*/
/*
#define Idade(_1) _Generic ((_1), \
                    Pessoa*: g_Idade)

#define Idade(_1, _2) _Generic((_1), \
                    int: _Generic((_2), \
                        Pessoa*: s_Idade))
                        */