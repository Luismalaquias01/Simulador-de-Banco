#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "banco.c"
#include "fila.c"
#include "pilha.c"
#include "ordenacao.c"

// #include "banco.h"
// #include "fila.h"
// #include "pilha.h"
// #include "ordenacao.h"


void menu() {
    int opcao;
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    do {
        printf("\n===== MENU =====\n");
        printf("1. Cadastrar conta\n");
        printf("2. Realizar saque\n");
        printf("3. Depositar\n");
        printf("4. Ver saldo\n");
        printf("5. Gerar relatório\n");
        printf("6. Salvar e sair\n");
        printf("7. Adicionar cliente à fila\n");
        printf("8. Atender próximo cliente\n");
        printf("9. Ver fila de atendimento\n");
        printf("10. Desfazer última operação\n");
        printf("11. Ordenar por número da conta\n");
        printf("12. Ordenar por total sacado\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        int conta, agencia;
        float valor;

        switch (opcao) {
            case 1:
                cadastrarConta(); break;
            case 2:
                printf("Número da conta: ");
                scanf("%d", &conta);
                printf("Número da agência: ");
                scanf("%d", &agencia);
                Conta *c_saque = buscarConta(conta, agencia);
                if (!c_saque) {
                    printf("Conta não encontrada!\n");
                    break;
                }
                printf("Valor do saque: R$ ");
                scanf("%f", &valor);
                if (c_saque->saldo >= valor) {
                    c_saque->saldo -= valor;
                    Saque *novo = (Saque*)malloc(sizeof(Saque));
                    novo->valor = valor;
                    novo->prox = c_saque->saques;
                    c_saque->saques = novo;
                    c_saque->total_saques++;
                    c_saque->total_sacado += valor;
                    printf("Saque realizado com sucesso!\n");
                    printf("Saldo restante: R$ %.2f\n", c_saque->saldo);
                    registrarOperacao(&pilha, OPERACAO_SAQUE, conta, agencia, valor);
                } else {
                    printf("Saldo insuficiente!\n");
                }
                break;
            case 3:
                printf("Número da conta: ");
                scanf("%d", &conta);
                printf("Número da agência: ");
                scanf("%d", &agencia);
                Conta *c_dep = buscarConta(conta, agencia);
                if (!c_dep) {
                    printf("Conta não encontrada!\n");
                    break;
                }
                printf("Valor do depósito: R$ ");
                scanf("%f", &valor);
                c_dep->saldo += valor;
                printf("Depósito realizado com sucesso! Saldo atual: R$ %.2f\n", c_dep->saldo);
                registrarOperacao(&pilha, OPERACAO_DEPOSITO, conta, agencia, valor);
                break;
            case 4:
                verSaldo(); break;
            case 5:
                gerarRelatorio(); break;
            case 6:
                #include <sys/stat.h>
#include <sys/types.h>

// cria pasta se necessário
mkdir("dados", 0777);
salvarArquivo();
                liberarContas();
                liberarPilha(&pilha);
                break;
            case 7:
                printf("Número da conta: ");
                scanf("%d", &conta);
                printf("Número da agência: ");
                scanf("%d", &agencia);
                enfileirar(&fila, conta, agencia);
                break;
            case 8:
                desenfileirar(&fila);
                break;
            case 9:
                mostrarFila(&fila);
                break;
            case 10:
                desfazerOperacao(&pilha);
                break;
            case 11:
                ordenarContas(POR_NUMERO_CONTA);
                break;
            case 12:
                ordenarContas(POR_TOTAL_SACADO);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);
}

int main() {
    carregarArquivo();
    menu();
    return 0;
}
