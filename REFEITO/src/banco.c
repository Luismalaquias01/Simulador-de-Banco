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
    if (!nova) return;

    nova->saques = NULL;
    nova->total_sacado = 0;
    nova->total_saques = 0;
    nova->saldo = 0;
    nova->prox = NULL;

    printf("Número da conta: ");
    if (scanf("%d", &nova->numero) != 1) return;
    printf("Número da agência: ");
    if (scanf("%d", &nova->agencia) != 1) return;
    printf("Nome do titular: ");
    scanf(" %[^\n]", nova->nome);  // lê até o final da linha

    printf("Telefone: ");
    scanf(" %[^\n]", nova->telefone);

    printf("CPF: ");
    scanf(" %[^\n]", nova->cpf);

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
    if (scanf("%d", &numero) != 1) return;
    printf("Número da agência: ");
    if (scanf("%d", &agencia) != 1) return;

    Conta *conta = buscarConta(numero, agencia);
    if (!conta) {
        printf("Conta não encontrada!\n");
        return;
    }

    printf("Valor do saque: R$ ");
    if (scanf("%f", &valor) != 1) return;

    if (conta->saldo < valor) {
        printf("Saldo insuficiente!\n");
        return;
    }

    Saque *novo = (Saque*)malloc(sizeof(Saque));
    if (!novo) return;
    novo->valor = valor;
    novo->prox = conta->saques;
    conta->saques = novo;

    conta->saldo -= valor;
    conta->total_saques++;
    conta->total_sacado += valor;

    printf("Saque realizado com sucesso!");
    printf("Saldo restante: R$ %.2f", conta->saldo);
}

void depositar() {
    int numero, agencia;
    float valor;

    printf("Número da conta: ");
    if (scanf("%d", &numero) != 1) return;
    printf("Número da agência: ");
    if (scanf("%d", &agencia) != 1) return;

    Conta *conta = buscarConta(numero, agencia);
    if (!conta) {
        printf("Conta não encontrada!\n");
        return;
    }

    printf("Valor do depósito: R$ ");
    if (scanf("%f", &valor) != 1) return;
    conta->saldo += valor;
    printf("Depósito realizado com sucesso! Saldo atual: R$ %.2f\n", conta->saldo);
}

void verSaldo() {
    int numero, agencia;

    printf("Número da conta: ");
    if (scanf("%d", &numero) != 1) return;
    printf("Número da agência: ");
    if (scanf("%d", &agencia) != 1) return;

    Conta *conta = buscarConta(numero, agencia);
    if (!conta) {
        printf("Conta não encontrada!\n");
        return;
    }

    printf("Saldo atual da conta %d (Agência %d): R$ %.2f\n", conta->numero, conta->agencia, conta->saldo);
}

void gerarRelatorio() {
    Conta *atual = inicio;
    while (atual != NULL) {
        printf("\nConta: %d | Agência: %d\n", atual->numero, atual->agencia);
        printf("Titular: %s | CPF: %s | Telefone: %s\n", atual->nome, atual->cpf, atual->telefone);
        printf("Saldo: R$ %.2f\n", atual->saldo);
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

    // Cabeçalho da tabela (visual)
    fprintf(f, "Conta     Agencia   Nome                CPF             Telefone        Saldo     Saques  TotalSacado\n");
    fprintf(f, "------------------------------------------------------------------------------------------------------\n");

    Conta *c = inicio;
    while (c != NULL) {
        fprintf(f, "%-10d%-10d%-20s%-16s%-16s%-10.2f%-8d%-12.2f\n",
                c->numero, c->agencia, c->nome, c->cpf, c->telefone,
                c->saldo, c->total_saques, c->total_sacado);

        fprintf(f, "Saques: ");
        Saque *s = c->saques;
        while (s != NULL) {
            fprintf(f, "%.2f ", s->valor);
            s = s->prox;
        }
        fprintf(f, "\n\n");
        c = c->prox;
    }

    fclose(f);
    printf("Arquivo salvo com sucesso em contas.txt!\n");

    // Também salva em formato técnico reutilizável
    FILE *fr = fopen("contas_raw.txt", "w");
    if (!fr) {
        printf("Erro ao salvar o arquivo técnico.\n");
        return;
    }

    c = inicio;
    while (c != NULL) {
        fprintf(fr, "%d|%d|%s|%s|%s|%.2f|%d|%.2f\n",
                c->numero, c->agencia, c->nome, c->cpf, c->telefone,
                c->saldo, c->total_saques, c->total_sacado);

        Saque *s = c->saques;
        while (s != NULL) {
            fprintf(fr, "%.2f ", s->valor);
            s = s->prox;
        }
        fprintf(fr, "\n");
        c = c->prox;
    }

    fclose(fr);
    printf("Arquivo técnico salvo em contas_raw.txt!\n");
}

void carregarArquivo() {
    FILE *f = fopen("contas_raw.txt", "r");
    if (!f) {
        printf("Arquivo técnico não encontrado.\n");
        return;
    }

    char linha[512];

    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '\n') continue;

        Conta *nova = (Conta *)malloc(sizeof(Conta));
        if (!nova) break;

        nova->saques = NULL;
        nova->prox = NULL;

        // Lê os dados da conta com delimitador '|'
        if (sscanf(linha, "%d|%d|%99[^|]|%19[^|]|%19[^|]|%f|%d|%f",
                   &nova->numero, &nova->agencia, nova->nome,
                   nova->cpf, nova->telefone,
                   &nova->saldo, &nova->total_saques, &nova->total_sacado) != 8) {
            free(nova);
            continue;
        }

        // Lê a próxima linha com os saques
        if (!fgets(linha, sizeof(linha), f)) {
            free(nova);
            break;
        }

        float valor;
        char *p = linha;
        while (sscanf(p, "%f", &valor) == 1) {
            Saque *s = (Saque *)malloc(sizeof(Saque));
            s->valor = valor;
            s->prox = nova->saques;
            nova->saques = s;

            // Avança o ponteiro para o próximo valor
            while (*p && *p != ' ') p++;
            while (*p == ' ') p++;
        }

        nova->prox = inicio;
        inicio = nova;
    }

    fclose(f);
    printf("Arquivo técnico carregado com sucesso!\n");
}


void liberarContas() {
    Conta *atual = inicio;
    while (atual) {
        Saque *s = atual->saques;
        while (s) {
            Saque *tempS = s;
            s = s->prox;
            free(tempS);
        }
        Conta *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    inicio = NULL;
}
