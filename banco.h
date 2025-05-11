// banco.h
#ifndef BANCO_H
#define BANCO_H

typedef struct Saque {
    float valor;
    struct Saque *prox;
} Saque;

typedef struct Conta {
    int numero;
    int agencia;
    float saldo;
    int total_saques;
    float total_sacado;
    Saque *saques;
    struct Conta *prox;
} Conta;

void cadastrarConta();
void realizarSaque();
void gerarRelatorio();
void salvarArquivo();
void carregarArquivo();
void depositar();
void verSaldo();

#endif
