#ifndef HEAP_H
#define HEAP_H

#include "avl.h"
#include "hash.h"

// Estrutura para uma reserva na Heap
typedef struct Reserva {
    int codigoSala;   // Código identificador da sala
    int prioridade;   // Prioridade da reserva
    No* referenciaAVL;
} Reserva;
// Estrutura da Heap
typedef struct MaxHeap {
    Reserva* itens;   // Vetor que armazena as reservas
    int tamanho;      // Número atual de elementos na heap
    int capacidade;   // Capacidade máxima da heap
} MaxHeap;

void adicionarReservaHeap();
void atualizarPrioridadeHeap();
void listarReservaHeap();
MaxHeap* criarMaxHeap(int capacidade);
void liberarHeap(MaxHeap* heap);

#endif
