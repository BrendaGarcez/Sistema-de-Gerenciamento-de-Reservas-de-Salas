#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "heap.h"

No* criarNo(int codigoSala, int capacidade) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->codigoSala = codigoSala;
    novoNo->capacidade = capacidade;
    novoNo->altDireita = 0;
    novoNo->altEsquerda = 0;
    novoNo->direita = NULL;
    novoNo->esquerda = NULL;
    return novoNo;
}

No* inserirNoAVL(No* raiz, int codigoSala, int capacidade) {
    if (raiz == NULL) {
        return criarNo(codigoSala, capacidade); // Cria e retorna um novo nó se a raiz for NULL
    }

    // Inserção na subárvore esquerda
    if (codigoSala < raiz->codigoSala) {
        raiz->esquerda = inserirNoAVL(raiz->esquerda, codigoSala, capacidade);
        // Atualiza a altura da subárvore esquerda
        if (raiz->esquerda->altEsquerda > raiz->esquerda->altDireita) {
            raiz->altEsquerda = raiz->esquerda->altEsquerda + 1;
        } else {
            raiz->altEsquerda = raiz->esquerda->altDireita + 1;
        }
    }
    // Inserção na subárvore direita
    else if (codigoSala > raiz->codigoSala) {
        raiz->direita = inserirNoAVL(raiz->direita, codigoSala, capacidade);
        // Atualiza a altura da subárvore direita
        if (raiz->direita->altDireita > raiz->direita->altEsquerda) {
            raiz->altDireita = raiz->direita->altDireita + 1;
        } else {
            raiz->altDireita = raiz->direita->altEsquerda + 1;
        }
    }
    else {
        // Caso o código da sala já exista
        printf("Código de sala já existe: %d\n", codigoSala);
        return raiz;
    }

    // Balanceia a árvore se necessário
    return balanceamento(raiz);
}

// Função principal para inserir uma sala (pode ser chamada no programa principal)
No* inserirSalaAVL(No* raiz, int codigoSala, int capacidade) {
    printf("Digite o código da sala: ");
    scanf("%d", &codigoSala);
    printf("Digite a capacidade da sala: ");
    scanf("%d", &capacidade);

    raiz = inserirNoAVL(raiz, codigoSala, capacidade);
    printf("Sala %d com capacidade %d inserida com sucesso!\n", codigoSala, capacidade);
    return raiz;
}

// Função para remover uma sala da árvore AVL
No* removerSalaAVL(No* raiz, int codigoSala, HashTabela* hash, MaxHeap* heap) {
    if (raiz == NULL) {
        printf("Sala com código %d não encontrada.\n", codigoSala);
        return NULL;
    }

    if (codigoSala == raiz->codigoSala) {
        //  Remover da tabela hash
        if (removerEstadoHash(hash, codigoSala)) {
            printf("Sala %d removida da tabela hash.\n", codigoSala);
        } else {
            printf("Erro ao remover sala %d da tabela hash.\n", codigoSala);
        }

        //  Remover da heap de prioridades
        if (removerReservaHeap(heap, codigoSala)) {
            printf("Sala %d removida da heap de prioridades.\n", codigoSala);
        } else {
            printf("Sala %d não estava na heap de prioridades.\n", codigoSala);
        }

        //  Remoção na AVL
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        } else if (raiz->esquerda == NULL) {
            No* aux = raiz->direita;
            free(raiz);
            return aux;
        } else if (raiz->direita == NULL) {
            No* aux = raiz->esquerda;
            free(raiz);
            return aux;
        } else {
            // Encontrar o sucessor em ordem
            No* sucessor = raiz->direita;
            while (sucessor->esquerda != NULL) {
                sucessor = sucessor->esquerda;
            }
            raiz->codigoSala = sucessor->codigoSala;
            raiz->capacidade = sucessor->capacidade;

            raiz->direita = removerSalaAVL(raiz->direita, sucessor->codigoSala, hash, heap);
        }
    } else if (codigoSala < raiz->codigoSala) {
        raiz->esquerda = removerSalaAVL(raiz->esquerda, codigoSala, hash, heap);
    } else {
        raiz->direita = removerSalaAVL(raiz->direita, codigoSala, hash, heap);
    }

    // Organizar altura dos nós
    if (raiz->esquerda != NULL) {
        raiz->altEsquerda = (raiz->esquerda->altEsquerda > raiz->esquerda->altDireita
                                ? raiz->esquerda->altEsquerda
                                : raiz->esquerda->altDireita) +
                            1;
    } else {
        raiz->altEsquerda = 0;
    }

    if (raiz->direita != NULL) {
        raiz->altDireita = (raiz->direita->altDireita > raiz->direita->altEsquerda
                                ? raiz->direita->altDireita
                                : raiz->direita->altEsquerda) +
                            1;
    } else {
        raiz->altDireita = 0;
    }

    // Balancear a árvore
    return balanceamento(raiz);
}

// Função para buscar uma sala na árvore AVL
No *buscarSalaAVL(No *raiz, int codigoSala) {
    if (raiz == NULL) {
        return raiz;
    }
    if(raiz->codigoSala == codigoSala){
        return raiz;
    }
    if (codigoSala < raiz->codigoSala) {
        return buscarSalaAVL(raiz->esquerda, codigoSala);
    } else {
        return buscarSalaAVL(raiz->direita, codigoSala);
    }
}

// Função para listar as salas em ordem crescente
void listarSalaAVL() {
    printf("Função para listar salas AVL ainda não implementada.\n");
}

No* rotacaoEsquerda(No* no) {
    No *aux1, *aux2;
    aux1 = no->direita;
    aux2 = aux1->esquerda;
    no->direita = aux2;
    aux1->esquerda = no;

    if (no->direita == NULL) {
        no->altDireita = 0;
    } else if (no->direita->altEsquerda > no->direita->altDireita) {
        no->altDireita = no->direita->altEsquerda + 1;
    } else {
        no->altDireita = no->direita->altDireita + 1;
    }

    if (aux1->esquerda->altEsquerda > aux1->esquerda->altDireita) {
        aux1->altEsquerda = aux1->esquerda->altEsquerda + 1;
    } else {
        aux1->altEsquerda = aux1->esquerda->altDireita + 1;
    }

    return aux1;
}

No* rotacaoDireita(No* no) {
    No *aux1, *aux2;
    aux1 = no->esquerda;
    aux2 = aux1->direita;
    no->esquerda = aux2;
    aux1->direita = no;

    if (no->esquerda == NULL) {
        no->altEsquerda = 0;
    } else if (no->esquerda->altEsquerda > no->esquerda->altDireita) {
        no->altEsquerda = no->esquerda->altEsquerda + 1;
    } else {
        no->altEsquerda = no->esquerda->altDireita + 1;
    }

    if (aux1->direita->altDireita > aux1->direita->altEsquerda) {
        aux1->altDireita = aux1->direita->altDireita + 1;
    } else {
        aux1->altDireita = aux1->direita->altEsquerda + 1;
    }

    return aux1;
}
// Função para balancear a árvore AVL
No* balanceamento(No* no) {
    if(no == NULL){
        return NULL;
    }
    else{
        int fdX = no->altDireita - no->altEsquerda;
        if(fdX == 2){
            int dfY = no->direita->altDireita - no->direita->altEsquerda;
            if(dfY >= 0){
                no = rotacaoEsquerda(no);
            }
            else{
                no->direita = rotacaoDireita(no->direita);
                no = rotacaoEsquerda(no);
            }
        }
        else if(fdX == -2){
            int dfY = no->esquerda->altDireita - no->esquerda->altEsquerda;
            if(dfY <= 0){
                no = rotacaoDireita(no);
            }else{
                no->esquerda = rotacaoEsquerda(no->esquerda);
                no = rotacaoDireita(no);
            }
        }
        return no;
    }
}
void liberarAVL(No* raiz) {
    if (raiz != NULL) {
        liberarAVL(raiz->esquerda);
        liberarAVL(raiz->direita);
        free(raiz);
    }
}