// fila.c
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void inicializarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void enfileirar(Fila *f, int conta, int agencia) {
    Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
    novo->numeroConta = conta;
    novo->numeroAgencia = agencia;
    novo->prox = NULL;

    if (f->fim == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }

    printf("Cliente da conta %d (Agência %d) entrou na fila.\n", conta, agencia);
}

void desenfileirar(Fila *f) {
    if (f->inicio == NULL) {
        printf("Fila vazia. Nenhum cliente para atender.\n");
        return;
    }

    Cliente *removido = f->inicio;
    printf("Atendendo cliente da conta %d (Agência %d).\n", removido->numeroConta, removido->numeroAgencia);

    f->inicio = f->inicio->prox;
    if (f->inicio == NULL)
        f->fim = NULL;

    free(removido);
}

void mostrarFila(Fila *f) {
    Cliente *atual = f->inicio;
    if (!atual) {
        printf("Fila está vazia.\n");
        return;
    }

    printf("Clientes na fila:\n");
    while (atual != NULL) {
        printf("Conta %d | Agência %d\n", atual->numeroConta, atual->numeroAgencia);
        atual = atual->prox;
    }
}
