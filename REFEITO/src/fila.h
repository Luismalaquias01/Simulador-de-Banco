#ifndef FILA_H
#define FILA_H

// estrutura para cliente na fila
typedef struct Cliente {
    int numeroConta;
    int numeroAgencia;
    struct Cliente *prox;
} Cliente;

// estrutura da fila
typedef struct {
    Cliente *inicio;
    Cliente *fim;
} Fila;

void inicializarFila(Fila *f);
void enfileirar(Fila *f, int conta, int agencia);
void desenfileirar(Fila *f);
void mostrarFila(Fila *f);

#endif