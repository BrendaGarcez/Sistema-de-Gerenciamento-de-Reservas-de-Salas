#ifndef HASH_H
#define HASH_H

#include "avl.h"
#include "heap.h"

typedef struct Sala {
    int codigoSala;          // Código identificador da sala
    char estado[20];
    No* referenciaAVL;         // Estado da sala: "bloqueada" ou "disponivel"
    struct Sala* prox;       // Ponteiro para a próxima sala (para tratar colisões)
} Sala;

// Estrutura para a Tabela Hash
typedef struct HashTabela {
    int tamanho;             // Tamanho da tabela hash
    Sala** entradas;         // Vetor de ponteiros para as entradas da tabela
} HashTabela;

void bloquearSalaHash();
void desbloquearSalaHash();
void consultarEstadoHash();
HashTabela* criarTabelaHash(int tamanho);
void liberarHash(HashTabela* tabela);

#endif
