#ifndef HEAP_H
#define HEAP_H

// Estrutura para uma reserva na Heap
typedef struct Reserva {
    int codigoSala;   // Código identificador da sala
    int prioridade;   // Prioridade da reserva
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

#endif
