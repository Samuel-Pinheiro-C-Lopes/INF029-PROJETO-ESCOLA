#include "Utils.h"
#include "Aluno.h"
#include "Escola.h"

// projeto escola true

int main (void)
{	
    Lst_Aluno* inicio_aluno = NULL;
    int opcao;
    do {
        menu_Main(&opcao);
        switch (opcao * -1)
        {
          case (OPCAO_MODULO_ALUNO):
          {
            mainAluno(&inicio_aluno, &opcao);
            break;   
          }
          case (OPCAO_MODULO_PROFESSOR):
          {
            printf("OPCAO UTILIDADES TESTAR\n");
            printf("entre com a string: \n");
            int num;
			scanf(" %d", &num);
			char* string = int_para_string(num);
            printf("\nString produto da conversão: %s\n\n", string);
            break;   
          }
          case (OPCAO_MODULO_DISCIPLINAS):
          {
            printf("OPCAO_REMOVER");
            break;   
          }
        }
    } while (opcao != OPCAO_SAIR);

    return 1;
}

    void menu_Main (int* opcao)
    {
      printf("\n###PROJETO ESCOLA###\n\n");
      printf("Opções:\n");
      printf("0 - Sair\n");
      printf("1 - Módulo Aluno\n");
      printf("2 - Módulo Professor\n");
      printf("3 - Módulo Disciplinas\n");
      printf("\nEntre com a opção desejada: ");
      scanf(" %d", opcao);
      getchar();
    }
