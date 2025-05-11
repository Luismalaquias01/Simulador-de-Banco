// banco.c
#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

Conta *inicio = NULL;

Conta* buscarConta(int numero, int agencia) {
    Conta *atual = inicio;
    while (atual != NULL) {
        if (atual->numero == numero && atual->agencia == agencia)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

void cadastrarConta() {
    Conta *nova = (Conta*)malloc(sizeof(Conta));
    nova->saques = NULL;
    nova->total_sacado = 0;
    nova->total_saques = 0;
    nova->prox = NULL;

    printf("Número da conta: ");
    scanf("%d", &nova->numero);
    printf("Número da agência: ");
    scanf("%d", &nova->agencia);

    if (buscarConta(nova->numero, nova->agencia)) {
        printf("Conta já existe!\n");
        free(nova);
        return;
    }

    nova->prox = inicio;
    inicio = nova;
    printf("Conta cadastrada com sucesso!\n");
}

void realizarSaque() {
    int numero, agencia;
    float valor;

    printf("Número da conta: ");
    scanf("%d", &numero);
    printf("Número da agência: ");
    scanf("%d", &agencia);

    Conta *conta = buscarConta(numero, agencia);
    if (!conta) {
        printf("Conta não encontrada!\n");
        return;
    }

    printf("Valor do saque: R$ ");
    scanf("%f", &valor);

    Saque *novo = (Saque*)malloc(sizeof(Saque));
    novo->valor = valor;
    novo->prox = conta->saques;
    conta->saques = novo;

    conta->total_saques += 1;
    conta->total_sacado += valor;

    printf("Saque realizado com sucesso!\n");
}

void gerarRelatorio() {
    Conta *atual = inicio;
    while (atual != NULL) {
        printf("\nConta: %d | Agência: %d\n", atual->numero, atual->agencia);
        printf("Total de saques: %d | Total sacado: R$ %.2f\n", atual->total_saques, atual->total_sacado);
        Saque *s = atual->saques;
        int count = 1;
        while (s != NULL) {
            printf("  Saque %d: R$ %.2f\n", count++, s->valor);
            s = s->prox;
        }
        atual = atual->prox;
    }
}

void salvarArquivo() {
    FILE *f = fopen("contas.txt", "w");
    if (!f) {
        printf("Erro ao salvar.\n");
        return;
    }

    Conta *c = inicio;
    while (c != NULL) {
        fprintf(f, "%d %d %d %.2f\n", c->numero, c->agencia, c->total_saques, c->total_sacado);
        Saque *s = c->saques;
        while (s != NULL) {
            fprintf(f, "%.2f ", s->valor);
            s = s->prox;
        }
        fprintf(f, "\n");
        c = c->prox;
    }
    fclose(f);
    printf("Arquivo salvo com sucesso!\n");
}

void carregarArquivo() {
    FILE *f = fopen("contas.txt", "r");
    if (!f) return;

    while (!feof(f)) {
        Conta *nova = (Conta*)malloc(sizeof(Conta));
        nova->saques = NULL;
        nova->prox = NULL;

        if (fscanf(f, "%d %d %d %f", &nova->numero, &nova->agencia, &nova->total_saques, &nova->total_sacado) != 4) {
            free(nova);
            break;
        }

        float valor;
        for (int i = 0; i < nova->total_saques; i++) {
            if (fscanf(f, "%f", &valor) != 1) break;
            Saque *novoSaque = (Saque*)malloc(sizeof(Saque));
            novoSaque->valor = valor;
            novoSaque->prox = nova->saques;
            nova->saques = novoSaque;
        }

        nova->prox = inicio;
        inicio = nova;
    }

void carregarArquivo() {
        FILE *f = fopen("contas.txt", "r");
        if (!f) return;
    
        while (!feof(f)) {
            Conta *nova = (Conta*)malloc(sizeof(Conta));
            nova->saques = NULL;
            nova->prox = NULL;
    
            if (fscanf(f, "%d %d %d %f", &nova->numero, &nova->agencia, &nova->total_saques, &nova->total_sacado) != 4) {
                free(nova);
                break;
            }
    
            nova->saldo = 0; // Inicializa saldo, caso queira atualizar isso no arquivo futuramente
    
            float valor;
            for (int i = 0; i < nova->total_saques; i++) {
                if (fscanf(f, "%f", &valor) != 1) break;
                Saque *novoSaque = (Saque*)malloc(sizeof(Saque));
                novoSaque->valor = valor;
                novoSaque->prox = nova->saques;
                nova->saques = novoSaque;
            }
    
            nova->prox = inicio;
            inicio = nova;
        }
    
        fclose(f);
    }
    
void depositar() {
        int numero, agencia;
        float valor;
    
        printf("Número da conta: ");
        scanf("%d", &numero);
        printf("Número da agência: ");
        scanf("%d", &agencia);
    
        Conta *conta = buscarConta(numero, agencia);
        if (!conta) {
            printf("Conta não encontrada!\n");
            return;
        }
    
        printf("Valor do depósito: R$ ");
        scanf("%f", &valor);
        conta->saldo += valor;
        printf("Depósito realizado com sucesso! Saldo atual: R$ %.2f\n", conta->saldo);
    }
    
void verSaldo() {
        int numero, agencia;
    
        printf("Número da conta: ");
        scanf("%d", &numero);
        printf("Número da agência: ");
        scanf("%d", &agencia);
    
        Conta *conta = buscarConta(numero, agencia);
        if (!conta) {
            printf("Conta não encontrada!\n");
            return;
        }
    
        printf("Saldo atual da conta %d (Agência %d): R$ %.2f\n", conta->numero, conta->agencia, conta->saldo);
    }
        

    fclose(f);
}
