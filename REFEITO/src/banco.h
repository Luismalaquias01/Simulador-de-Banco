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

// Funções principais do sistema bancário
void cadastrarConta();        // Cria nova conta
void realizarSaque();         // Realiza saque após verificar saldo
void depositar();             // Realiza depósito
void verSaldo();              // Exibe saldo atual da conta
void gerarRelatorio();        // Exibe relatório completo de contas e saques
void salvarArquivo();         // Salva dados em arquivo
void carregarArquivo();       // Carrega dados do arquivo
void liberarContas();         // Libera memória alocada das contas e saques

Conta* buscarConta(int numero, int agencia); // 🔹 Declaração adicionada

extern Conta *inicio;

#endif
