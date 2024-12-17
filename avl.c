#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

// Função para inserir uma sala na árvore AVL
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
void inserirSalaAVL() {
    static No* raiz = NULL; // Raiz estática para manter o estado da árvore
    int codigoSala, capacidade;

    printf("Digite o código da sala: ");
    scanf("%d", &codigoSala);
    printf("Digite a capacidade da sala: ");
    scanf("%d", &capacidade);

    raiz = inserirNoAVL(raiz, codigoSala, capacidade);

    printf("Sala %d com capacidade %d inserida com sucesso!\n", codigoSala, capacidade);
}

// Função para remover uma sala da árvore AVL
void removerSalaAVL() {
    printf("Função para remover sala AVL ainda não implementada.\n");
}

// Função para buscar uma sala na árvore AVL
void buscarSalaAVL() {
    printf("Função para buscar sala AVL ainda não implementada.\n");
}

// Função para listar as salas em ordem crescente
void listarSalaAVL() {
    printf("Função para listar salas AVL ainda não implementada.\n");
}

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