#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void troca(Reserva *v1, Reserva *v2) {
    Reserva aux = *v1;
    *v1 = *v2;
    *v2 = aux;
}
Reserva* buscarReservaHeap(MaxHeap* heap, int codigoSala) {
    if (heap == NULL || heap->itens == NULL) {
        return NULL;  // Heap não inicializada
    }
    for (int i = 0; i < heap->tamanho; i++) {
        if (heap->itens[i].codigoSala == codigoSala) {
            return &heap->itens[i];  // Retorna o ponteiro para o item encontrado
        }
    }
    return NULL;  // Não encontrado
}

MaxHeap* criarMaxHeap(int capacidade, FILE *saida) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (heap == NULL) {
        printf("Erro ao alocar memoria para a heap.\n");
        fprintf(saida,"Erro ao alocar memoria para a heap.\n");
        return NULL;
    }
    heap->itens = (Reserva*)malloc(capacidade * sizeof(Reserva));
    if (heap->itens == NULL) {
        printf("Erro ao alocar memoria para os itens da heap.\n");
        fprintf(saida,"Erro ao alocar memoria para os itens da heap.\n");
        free(heap);
        return NULL;
    }
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    return heap;
}
// Função para adicionar uma reserva na heap
void inserirReservaHeap(MaxHeap* heap, int codigoSala, int prioridade, FILE *saida) {
    if (heap == NULL) {
        printf("\nErro: A heap nao foi inicializada.\n");
        fprintf(saida, "\nErro: A heap nao foi inicializada.\n");
        return;
    }

    if (heap->capacidade == 0) {
        fprintf(saida, "\nErro: A heap foi inicializada com capacidade 0.\n");
        return;
    }

    if (codigoSala <= 0 || prioridade < 0) {
        printf("\nErro: Codigo da sala ou prioridade invalidos. Codigo: %d, Prioridade: %d\n", codigoSala, prioridade);
        fprintf(saida, "\nErro: Codigo da sala ou prioridade invalidos. Codigo: %d, Prioridade: %d\n", codigoSala, prioridade);
        return;
    }

    // Verifica se há necessidade de aumentar a capacidade da heap
    if (heap->tamanho == heap->capacidade) {
        Reserva* novoItens = realloc(heap->itens, (heap->capacidade * 2) * sizeof(Reserva));
        if (novoItens == NULL) {
            printf("\nErro ao realocar memoria para a heap.\n");
            fprintf(saida, "\nErro ao realocar memoria para a heap.\n");
            return;
        }
        heap->itens = novoItens;
        heap->capacidade *= 2;
        fprintf(saida, "\nHeap redimensionada para capacidade %d.\n", heap->capacidade);
    }

    // Adicionar nova reserva na posição final da heap
    Reserva novaReserva = {codigoSala, prioridade};
    heap->itens[heap->tamanho] = novaReserva;
    int index = heap->tamanho;
    heap->tamanho++;

    // Subir o item até a posição correta na heap
    while (index > 0) {
        int pai = (index - 1) / 2;
        if (heap->itens[index].prioridade > heap->itens[pai].prioridade) {
            troca(&heap->itens[index], &heap->itens[pai]);
            index = pai;
        } else {
            break;
        }
    }

    printf("\nReserva adicionada com SUCESSO\n");
    fprintf(saida, "\nReserva adicionada com SUCESSO\n");
}

void heapify(MaxHeap* heap, int i) {
    int maior = i;
    int filhoEsquerda = 2 * i + 1;
    int filhoDireita = 2 * i + 2;

    // Verifica o filho esquerdo
    if (filhoEsquerda < heap->tamanho &&
        heap->itens[filhoEsquerda].prioridade > heap->itens[maior].prioridade)
    {
        maior = filhoEsquerda;
    }
    // Verifica o filho direito
    if (filhoDireita < heap->tamanho &&
        heap->itens[filhoDireita].prioridade > heap->itens[maior].prioridade) {
        maior = filhoDireita;
    }
    // Se o maior não for o pai
    if (maior != i) {
        troca(&heap->itens[i], &heap->itens[maior]);
        heapify(heap, maior);
    }
}
// Função para atualizar a prioridade de uma reserva
void atualizarPrioridadeHeap(MaxHeap* heap, int codigoSala, int prioridadeNova, FILE *saida) {
    if (heap == NULL || heap->itens == NULL) {
        printf("\nErro: Heap nao inicializada corretamente.\n");
        fprintf(saida,"\nErro: Heap nao inicializada corretamente.\n");
        return;
    }

    if (heap->tamanho == 0) {
        printf("\nA heap esta vazia, nao e possivel atualizar prioridades.\n");
        fprintf(saida,"\nA heap esta vazia, nao e possivel atualizar prioridades.\n");
        return;
    }

    int index = -1;  // Inicializa corretamente o índice como -1
    for (int i = 0; i < heap->tamanho; i++) {
        if (heap->itens[i].codigoSala == codigoSala) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\nErro: Sala com codigo %d nao encontrada na heap.\n", codigoSala);
        fprintf(saida,"\nErro: Sala com codigo %d nao encontrada na heap.\n", codigoSala);
        return;
    }

    // Atualizar a prioridade
    int prioridadeAntiga = heap->itens[index].prioridade;
    heap->itens[index].prioridade = prioridadeNova;

    // Restabelecer a propriedade da heap
    if (prioridadeNova > prioridadeAntiga) {
        // Se a nova prioridade for maior, sobe o elemento
        while (index > 0) {
            int pai = (index - 1) / 2;
            if (heap->itens[index].prioridade > heap->itens[pai].prioridade) {
                // Trocar com o pai
                troca(&heap->itens[index], &heap->itens[pai]);
                index = pai;  // Atualiza o índice para continuar subindo
            } else {
                break;
            }
        }
    } else if (prioridadeNova < prioridadeAntiga) {
        // Se a nova prioridade for menor, desce o elemento
        heapify(heap, index);
    }
    printf("Prioridade da sala %d atualizada para %d.\n", heap->itens[index].codigoSala, heap->itens[index].prioridade);
    fprintf(saida,"\nPrioridade da sala %d atualizada para %d.\n", heap->itens[index].codigoSala, heap->itens[index].prioridade);
}

// Função para listar as reservas em ordem de prioridade
void listarReservaHeap(MaxHeap* heap, FILE *saida) {
    if (heap == NULL || heap->itens == NULL) {
        printf("Erro: Heap nao inicializada.\n");
        if (saida != NULL){
            fprintf(saida, "Erro: Heap nao inicializada.\n");
        }
        return;
    }
    if (heap->tamanho == 0) {
        printf("A heap esta vazia!\n");
        fprintf(saida,"\nA heap esta vazia!\n");
        return;
    }

    for (int i = 0; i < heap->tamanho; i++) {
        printf("\nSala %d - Prioridade: %d", (heap->itens[i].codigoSala), (heap->itens[i].prioridade));
        fprintf(saida,"\nSala %d - Prioridade: %d", (heap->itens[i].codigoSala), (heap->itens[i].prioridade));
    }
}

Reserva liberarHeap(MaxHeap* heap, FILE *saida) {
    if (heap == NULL || heap->itens == NULL) {
        printf("Erro: Heap nao inicializada corretamente.\n");
        fprintf(saida,"Erro: Heap nao inicializada corretamente.\n");
        return (Reserva){-1, -1};
    }

    if (heap->tamanho == 0) {
        printf("Heap vazio!\n");
        fprintf(saida,"Heap vazio!\n");
        return (Reserva){-1, -1};
    }
    Reserva raiz = heap->itens[0];
    heap->itens[0] = heap->itens[heap->tamanho - 1];
    heap->tamanho--;
    heapify(heap, 0);
    printf("Reserva removida: Sala %d com prioridade %d.\n", raiz.codigoSala, raiz.prioridade);
    fprintf(saida,"Reserva removida: Sala %d com prioridade %d.\n", raiz.codigoSala, raiz.prioridade);
    return raiz;
}
void cancelarReservaHeap(MaxHeap* heap, int codigo, FILE *saida) {
    if (heap == NULL || heap->itens == NULL || heap->tamanho == 0) {
        fprintf(saida, "\nErro: Heap vazia ou nao inicializada.\n");
        return;
    }
    if (heap->tamanho == 0) {
        printf("\nHeap vazio!\n");
        fprintf(saida, "\nHeap vazio!\n");
        return;
    }

    int index = -1;
    for (int i = 0; i < heap->tamanho; i++) {
        if (heap->itens[i].codigoSala == codigo) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\nCodigo da sala nao encontrado!\n");
        fprintf(saida, "\nCodigo da sala nao encontrado!\n");
        return;
    }

    heap->itens[index] = heap->itens[heap->tamanho - 1];
    heap->tamanho--;

    heapify(heap, index);

    printf("\nReserva com codigo %d cancelada.\n", codigo);
    fprintf(saida, "\nReserva com codigo %d cancelada.\n", codigo);
}

void destruirHeap(MaxHeap** heap, FILE* saida) {
    if (heap == NULL || *heap == NULL) {
        fprintf(saida, "\nErro: Heap já está liberada ou não foi inicializada.\n");
        return;
    }
    free((*heap)->itens);
    free(*heap);
    *heap = NULL;
}


