#include <stdio.h>
#include <stdlib.h>

// Estrutura para uma reserva
typedef struct {
    int codigoSala;   // Código identificador da sala
    int prioridade;   // Prioridade da reserva
} Reserva;

// Estrutura da Heap
typedef struct {
    Reserva* itens;   // Vetor para armazenar as reservas
    int tamanho;      // Número atual de elementos na heap
    int capacidade;   // Capacidade máxima da heap
} MaxHeap;

// Função para criar uma heap
MaxHeap* criarMaxHeap(int capacidade) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->itens = (Reserva*)malloc(capacidade * sizeof(Reserva));
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    return heap;
}

// Função para trocar dois elementos
void trocar(Reserva* a, Reserva* b) {
    Reserva temp = *a;
    *a = *b;
    *b = temp;
}

// Função para "subir" um elemento na heap
void subir(MaxHeap* heap, int indice) {
    int pai = (indice - 1) / 2; // Índice do pai
    while (indice > 0 && heap->itens[indice].prioridade > heap->itens[pai].prioridade) {
        trocar(&heap->itens[indice], &heap->itens[pai]);
        indice = pai;
        pai = (indice - 1) / 2;
    }
}

// Função para adicionar uma reserva na heap
void adicionarReserva(MaxHeap* heap, int codigoSala, int prioridade) {
    if (heap->tamanho == heap->capacidade) {
        printf("Erro: Heap cheia! Não é possível adicionar mais elementos.\n");
        return;
    }

    // Adiciona o novo elemento no final
    heap->itens[heap->tamanho].codigoSala = codigoSala;
    heap->itens[heap->tamanho].prioridade = prioridade;

    // Sobe o elemento para a posição correta
    subir(heap, heap->tamanho);
    heap->tamanho++;

    printf("Reserva adicionada: Sala %d, Prioridade %d\n", codigoSala, prioridade);
}

// Função para "descer" um elemento na heap
void descer(MaxHeap* heap, int indice) {
    int maior = indice; // Assume que o elemento atual é o maior
    int esquerda = 2 * indice + 1; // Filho esquerdo
    int direita = 2 * indice + 2;  // Filho direito

    // Verifica o filho esquerdo
    if (esquerda < heap->tamanho && heap->itens[esquerda].prioridade > heap->itens[maior].prioridade) {
        maior = esquerda;
    }

    // Verifica o filho direito
    if (direita < heap->tamanho && heap->itens[direita].prioridade > heap->itens[maior].prioridade) {
        maior = direita;
    }

    // Se o maior não é o elemento atual, troca e continua
    if (maior != indice) {
        trocar(&heap->itens[indice], &heap->itens[maior]);
        descer(heap, maior);
    }
}

// Função para remover a reserva com a maior prioridade
void removerReserva(MaxHeap* heap) {
    if (heap->tamanho == 0) {
        printf("Erro: Heap vazia! Não há elementos para remover.\n");
        return;
    }

    // Remove o elemento de maior prioridade (raiz)
    printf("Reserva removida: Sala %d, Prioridade %d\n", heap->itens[0].codigoSala, heap->itens[0].prioridade);

    // Substitui a raiz pelo último elemento
    heap->itens[0] = heap->itens[heap->tamanho - 1];
    heap->tamanho--;

    // Desce o novo elemento na posição correta
    descer(heap, 0);
}

// Função para listar as reservas em ordem
void listarReservas(MaxHeap* heap) {
    if (heap->tamanho == 0) {
        printf("Heap vazia! Não há reservas.\n");
        return;
    }

    printf("Reservas na Heap:\n");
    for (int i = 0; i < heap->tamanho; i++) {
        printf("Sala %d, Prioridade %d\n", heap->itens[i].codigoSala, heap->itens[i].prioridade);
    }
}

int main() {
    int capacidade = 10;
    MaxHeap* heap = criarMaxHeap(capacidade);

    printf("Teste da Heap de Reservas\n");

    // Adiciona algumas reservas
    adicionarReserva(heap, 101, 5);
    adicionarReserva(heap, 102, 8);
    adicionarReserva(heap, 103, 3);
    adicionarReserva(heap, 104, 10);
    adicionarReserva(heap, 105, 7);

    // Lista as reservas
    listarReservas(heap);

    // Remove a reserva de maior prioridade
    removerReserva(heap);

    // Lista novamente
    listarReservas(heap);

    // Libera memória
    free(heap->itens);
    free(heap);

    return 0;
}
