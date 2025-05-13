#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"
#include "banco.h"

extern Conta *inicio;

void ordenarContas(CriterioOrdenacao criterio) {
    // numero de contas
    int n = 0;
    Conta *ptr = inicio;
    while (ptr) {
        n++;
        ptr = ptr->prox;
    }
    if (n < 2) {
        printf("Poucas contas para ordenar.\n");
        return;
    }

    // criação de um vetor auxiliar de ponteiros
    Conta **lista = (Conta **)malloc(n * sizeof(Conta *));
    if (!lista) return;

    ptr = inicio;
    for (int i = 0; i < n; i++) {
        lista[i] = ptr;
        ptr = ptr->prox;
    }

    // por bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int precisaTrocar = 0;

            if (criterio == POR_NUMERO_CONTA && lista[j]->numero > lista[j + 1]->numero)
                precisaTrocar = 1;
            else if (criterio == POR_TOTAL_SACADO && lista[j]->total_sacado < lista[j + 1]->total_sacado)
                precisaTrocar = 1;

            if (precisaTrocar) {
                Conta *temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }

    printf("\n==== CONTAS ORDENADAS ====");
    for (int i = 0; i < n; i++) {
        printf("\nConta: %d | Agência: %d\n", lista[i]->numero, lista[i]->agencia);
        printf("Saldo: R$ %.2f | Total Sacado: R$ %.2f\n",
               lista[i]->saldo, lista[i]->total_sacado);
    }

    free(lista);
}
