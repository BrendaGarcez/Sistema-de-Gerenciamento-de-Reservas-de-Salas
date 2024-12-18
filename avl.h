#ifndef AVL_H
#define AVL_H
#include "hash.h"
#include "heap.h"

typedef struct No {
    int codigoSala;
    int capacidade;
    int altDireita;
    int altEsquerda;
    struct No* direita;
    struct No* esquerda;
} No;

No* criarNo(int codigoSala, int capacidade);
No* inserirNoAVL(No* raiz, int codigoSala, int capacidade);
No* inserirSalaAVL(No* raiz, int codigoSala, int capacidade);
No* removerSalaAVL(No* raiz, int codigoSala, HashTabela* hash, MaxHeap* heap);
No *buscarSalaAVL(No *raiz, int codigoSala);
///////void listarSalaAVL();
No* rotacaoEsquerda(No* no);
No* rotacaoDireita(No* no);
No* balanceamento(No* no);
void liberarAVL(No* raiz);


#endif
