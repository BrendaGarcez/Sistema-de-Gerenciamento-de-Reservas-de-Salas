#include <stdio.h>
#include "heap.h"

// Função para adicionar uma reserva na heap
void adicionarReservaHeap() {
    printf("Função para adicionar reserva na heap ainda não implementada.\n");
}

// Função para atualizar a prioridade de uma reserva
void atualizarPrioridadeHeap() {
    printf("Função para atualizar prioridade na heap ainda não implementada.\n");
}

// Função para listar as reservas em ordem de prioridade
void listarReservaHeap() {
    printf("Função para listar reservas na heap ainda não implementada.\n");
}

MaxHeap* criarMaxHeap(int capacidade) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->itens = (Reserva*)malloc(capacidade * sizeof(Reserva));
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    return heap;
}