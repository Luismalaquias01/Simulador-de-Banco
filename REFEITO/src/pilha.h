#ifndef PILHA_H
#define PILHA_H

typedef enum {
    OPERACAO_SAQUE,
    OPERACAO_DEPOSITO
} TipoOperacao;

typedef struct Operacao {
    TipoOperacao tipo;
    int numeroConta;
    int numeroAgencia;
    float valor;
    struct Operacao *prox;
} Operacao;

typedef struct {
    Operacao *topo;
} Pilha;

void inicializarPilha(Pilha *p);
void registrarOperacao(Pilha *p, TipoOperacao tipo, int conta, int agencia, float valor);
void desfazerOperacao(Pilha *p);
void liberarPilha(Pilha *p);

#endif