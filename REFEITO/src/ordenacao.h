// ordenacao.h
#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "banco.h"

// Critérios possíveis de ordenação
typedef enum {
    POR_NUMERO_CONTA,
    POR_TOTAL_SACADO
} CriterioOrdenacao;

// Função para ordenar e exibir contas conforme critério
void ordenarContas(CriterioOrdenacao criterio);

#endif
