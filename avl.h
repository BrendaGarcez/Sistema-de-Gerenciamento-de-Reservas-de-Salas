#ifndef AVL_H
#define AVL_H

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
void inserirSalaAVL();
void removerSalaAVL();
void buscarSalaAVL();
void listarSalaAVL();
No* rotacaoEsquerda(No* no);
No* rotacaoDireita(No* no);
No* balanceamento(No* no);
void liberarAVL(No* raiz);


#endif
