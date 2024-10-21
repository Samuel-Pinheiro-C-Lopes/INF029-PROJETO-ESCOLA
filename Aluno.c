#include "Aluno.h"
#include "Utils.h"


void mainAluno (Lst_Aluno **inicio_aluno, int* opcao)
{
  do 
  {
    menu_Aluno(opcao);
    switch (*opcao * -1)
    {
      case (OPCAO_CADASTRAR):
      {
        printf("OPCAO_CADASTRAR");
        break;   
      }
      case (OPCAO_LISTAR):
      {
        printf("OPCAO_LISTAR");
        break;   
      }
      case (OPCAO_REMOVER):
      {
        printf("OPCAO_REMOVER");
        break;   
      }
      case (OPCAO_ALTERAR):
      {
        printf("OPCAO_ALTERAR");
        break;   
      }
    }
  } while (*opcao != OPCAO_SAIR);
  *opcao = 1;
}

void menu_Aluno (int* opcao)
{
  printf("\n###MÓDULO ALUNO###\n\n");
  printf("Opções:\n");
  printf("0 - Sair\n");
  printf("1 - Cadastrar aluno\n");
  printf("2 - Listar alunos\n");
  printf("3 - Remover aluno\n");
  printf("4 - Alterar aluno\n");
  printf("\nEntre com a opção desejada: ");
  scanf(" %d", opcao);
}
