#ifndef BANCO_H
#define BANCO_H

// Estrutura de um saque realizado
typedef struct Saque {
    float valor;
    struct Saque *prox;
} Saque;

// Estrutura de uma conta bancária
typedef struct Conta {
    char nome[100];
    char telefone[20];
    char cpf[20];
    int numero;
    int agencia;
    float saldo;
    int total_saques;
    float total_sacado;
    Saque *saques;
    struct Conta *prox;
} Conta;

// principais funcionalidades do sistema bancário
void cadastrarConta();        // cria nova conta
void realizarSaque();         // realiza saque após verificar saldo
void depositar();             // realiza depósito
void verSaldo();              // exibe saldo atual da conta
void gerarRelatorio();        // exibe relatório completo de contas e saques
void salvarArquivo();         // salva dados em arquivo
void carregarArquivo();       // carrega dados do arquivo
void liberarContas();         // libera memória alocada das contas e saques

Conta* buscarConta(int numero, int agencia); 

extern Conta *inicio; // variavel declarada em outro codigo, no caso o banco.c

#endif
