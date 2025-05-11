#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "banco.h"

void inicializarPilha(Pilha *p) {
    p->topo = NULL;
}

void registrarOperacao(Pilha *p, TipoOperacao tipo, int conta, int agencia, float valor) {
    Operacao *nova = (Operacao*)malloc(sizeof(Operacao));
    if (!nova) return;

    nova->tipo = tipo;
    nova->numeroConta = conta;
    nova->numeroAgencia = agencia;
    nova->valor = valor;
    nova->prox = p->topo;
    p->topo = nova;
}

void desfazerOperacao(Pilha *p) {
    if (!p->topo) {
        printf("Nenhuma operação para desfazer.\n");
        return;
    }

    Operacao *op = p->topo;
    p->topo = op->prox;

    Conta *conta = buscarConta(op->numeroConta, op->numeroAgencia);
    if (!conta) {
        printf("Conta da operação não encontrada.\n");
        free(op);
        return;
    }

    if (op->tipo == OPERACAO_DEPOSITO) {
        if (conta->saldo >= op->valor) {
            conta->saldo -= op->valor;
            printf("Desfeito depósito de R$ %.2f na conta %d (Agência %d).\n", op->valor, op->numeroConta, op->numeroAgencia);
        } else {
            printf("Não foi possível desfazer o depósito: saldo insuficiente.\n");
        }
    } else if (op->tipo == OPERACAO_SAQUE) {
        conta->saldo += op->valor;
        conta->total_saques--;
        conta->total_sacado -= op->valor;
        if (conta->saques) {
            Saque *temp = conta->saques;
            conta->saques = temp->prox;
            free(temp);
        }
        printf("Desfeito saque de R$ %.2f da conta %d (Agência %d).\n", op->valor, op->numeroConta, op->numeroAgencia);
    }

    free(op);
}

void liberarPilha(Pilha *p) {
    Operacao *atual = p->topo;
    while (atual) {
        Operacao *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    p->topo = NULL;
}
