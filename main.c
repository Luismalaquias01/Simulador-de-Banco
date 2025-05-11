#include <stdio.h>
#include "banco.h"
#include "banco.c"


void menu() {
    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Cadastrar conta\n");
        printf("2. Realizar saque\n");
        printf("3. Gerar relatório\n");
        printf("4. Salvar e sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

       switch (opcao) {
            case 1: cadastrarConta(); break;
            case 2: realizarSaque(); break;
            case 3: depositar(); break;
            case 4: verSaldo(); break;
            case 5: gerarRelatorio(); break;
            case 6: salvarArquivo(); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 6);
}

int main() {
    carregarArquivo();
    menu();
    return 0;
}
