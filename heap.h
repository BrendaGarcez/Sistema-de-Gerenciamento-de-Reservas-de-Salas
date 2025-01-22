#ifndef HEAP_H
#define HEAP_H

// Estrutura para uma reserva na Heap
typedef struct Reserva {
    int codigoSala;   // Códigoda sala
    int prioridade;   // Prioridade da reserva
} Reserva;
// Estrutura da Heap
typedef struct MaxHeap {
    Reserva* itens;   // Vetor que armazena as reservas
    int tamanho;      // Número atual de elementos na heap
    int capacidade;   // Capacidade máxima da heap
} MaxHeap;

// Funções de Manipulação da Heap
void troca(Reserva *v1, Reserva *v2);
MaxHeap* criarMaxHeap(int capacidade, FILE *saida);

// Função para adicionar uma reserva na heap
void inserirReservaHeap(MaxHeap* heap, int codigoSala, int prioridade, FILE *saida);
void heapify(MaxHeap* heap, int i);

// Função para atualizar a prioridade de uma reserva
void atualizarPrioridadeHeap(MaxHeap* heap, int codigoSala, int prioridadeNova, FILE *saida);

// Função para listar as reservas em ordem de prioridade
void listarReservaHeap(MaxHeap* heap, FILE *saida);
Reserva liberarHeap(MaxHeap* heap, FILE *saida);
void cancelarReservaHeap(MaxHeap* heap, int codigo, FILE *saida);
void destruirHeap(MaxHeap** heap, FILE* saida);

#endif
